// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2015 Intel Corporation. All Rights Reserved.

#if (_MSC_FULL_VER < 180031101)
    #error At least Visual Studio 2013 Update 4 is required to compile this backend
#endif

#include "win7-backend.h"
#include "win7-uvc.h"
#include "win7-usb.h"
#include "win7-hid.h"
#include "../types.h"
#include "usb/usb-enumerator.h"
#include <mfapi.h>
#include <ks.h>
#include <chrono>
#include <Windows.h>
#include <dbt.h>
#include <cctype> // std::tolower

#ifndef KSCATEGORY_SENSOR_CAMERA
DEFINE_GUIDSTRUCT("24E552D7-6523-47F7-A647-D3465BF1F5CA", KSCATEGORY_SENSOR_CAMERA);
#define KSCATEGORY_SENSOR_CAMERA DEFINE_GUIDNAMED(KSCATEGORY_SENSOR_CAMERA)
#endif // !KSCATEGORY_SENSOR_CAMERA

namespace librealsense
{
    namespace platform
    {
        win7_backend::win7_backend()
        {
        }

        win7_backend::~win7_backend()
        {
            try {

            }
            catch(...)
            {
                // TODO: Write to log
            }
        }

        std::shared_ptr<uvc_device> win7_backend::create_uvc_device(uvc_device_info info) const
        {
            return std::make_shared<retry_controls_work_around>(std::make_shared<win7_uvc_device>(info, shared_from_this()));
        }

        std::shared_ptr<backend> create_backend()
        {
            return std::make_shared<win7_backend>();
        }

        std::vector<uvc_device_info> win7_backend::query_uvc_devices() const
        {
            std::vector<uvc_device_info> devices;

            auto action = [&devices](const uvc_device_info& info)
            {
                devices.push_back(info);
            };

            win7_uvc_device::foreach_uvc_device(action);

            return devices;
        }

        std::shared_ptr<command_transfer> win7_backend::create_usb_device(usb_device_info info) const
        {
            return std::make_shared<winusb_bulk_transfer>(info);
        }

        std::vector<usb_device_info> win7_backend::query_usb_devices() const
        {
            return usb_enumerator::query_devices_info();
        }

        std::shared_ptr<hid_device> win7_backend::create_hid_device(hid_device_info info) const
        {
            throw std::runtime_error("create_hid_device Not supported");
        }

        std::vector<hid_device_info> win7_backend::query_hid_devices() const
        {
            std::vector<hid_device_info> devices;
            // Not supported 
            return devices;
        }

        std::shared_ptr<time_service> win7_backend::create_time_service() const
        {
            return std::make_shared<os_time_service>();
        }

        class win_event_device_watcher : public device_watcher
        {
        public:
            win_event_device_watcher(const backend * backend)
            {
                _data._backend = backend;
                _data._stopped = false;
                _data._last = backend_device_group(backend->query_uvc_devices(), backend->query_usb_devices(), backend->query_hid_devices());
            }
            ~win_event_device_watcher() { stop(); }

            void start(device_changed_callback callback) override
            {
                std::lock_guard<std::mutex> lock(_m);
                if (!_data._stopped) throw wrong_api_call_sequence_exception("Cannot start a running device_watcher");
                _data._stopped = false;
                _data._callback = std::move(callback);
                _thread = std::thread([this]() { run(); });
            }

            void stop() override
            {
                std::lock_guard<std::mutex> lock(_m);
                if (!_data._stopped)
                {
                    _data._stopped = true;
                    if (_thread.joinable()) _thread.join();
                }
            }
        private:
            std::thread _thread;
            std::mutex _m;

            struct extra_data {
                const backend * _backend;
                backend_device_group _last;
                device_changed_callback _callback;

                bool _stopped;
                HWND hWnd;
                HDEVNOTIFY hdevnotifyHW, hdevnotifyUVC, hdevnotify_sensor;
            } _data;

            void run()
            {
                WNDCLASS windowClass = {};
                LPCWSTR SzWndClass = TEXT("MINWINAPP");
                windowClass.lpfnWndProc = &on_win_event;
                windowClass.lpszClassName = SzWndClass;
                UnregisterClass(SzWndClass, nullptr);

                if (!RegisterClass(&windowClass))
                    LOG_WARNING("RegisterClass failed.");

                _data.hWnd = CreateWindow(SzWndClass, nullptr, 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, nullptr, &_data);
                if (!_data.hWnd)
                    throw winapi_error("CreateWindow failed");

                MSG msg;

                while (!_data._stopped)
                {
                    if (PeekMessage(&msg, _data.hWnd, 0, 0, PM_REMOVE))
                    {
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                    }
                    else  // Yield CPU resources, as this is required for connect/disconnect events only
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }

                UnregisterDeviceNotification(_data.hdevnotifyHW);
                UnregisterDeviceNotification(_data.hdevnotifyUVC);
                UnregisterDeviceNotification(_data.hdevnotify_sensor);
                DestroyWindow(_data.hWnd);
            }

            static LRESULT CALLBACK on_win_event(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
            {
                LRESULT lRet = 1;

                switch (message)
                {
                case WM_CREATE:
                    SetWindowLongPtr(hWnd, GWLP_USERDATA, LONG_PTR(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams));
                    if (!DoRegisterDeviceInterfaceToHwnd(hWnd))
                case WM_QUIT:
                {
                    auto data = reinterpret_cast<extra_data*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
                    data->_stopped = true;
                    break;
                }
                case WM_DEVICECHANGE:
                {
                    //PDEV_BROADCAST_DEVICEINTERFACE b = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;
                    // Output some messages to the window.
                    switch (wParam)
                    {
                    case DBT_DEVICEARRIVAL:
                    {
                        auto data = reinterpret_cast<extra_data*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
                        backend_device_group next(data->_backend->query_uvc_devices(), data->_backend->query_usb_devices(), data->_backend->query_hid_devices());
                        /*if (data->_last != next)*/ data->_callback(data->_last, next);
                        data->_last = next;
                    }
                        break;

                    case DBT_DEVICEREMOVECOMPLETE:
                    {
                        auto data = reinterpret_cast<extra_data*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
                        auto next = data->_last;
                        std::wstring temp = reinterpret_cast<DEV_BROADCAST_DEVICEINTERFACE*>(lParam)->dbcc_name;
                        std::string path;
                        path.reserve(temp.length());
                        for (wchar_t ch : temp) {
                            if (ch != L'{') path.push_back(std::tolower(((char*)&ch)[0]));
                            else break;
                        }

                        next.uvc_devices.erase(std::remove_if(next.uvc_devices.begin(), next.uvc_devices.end(), [&path](const uvc_device_info& info)
                        { return info.device_path.substr(0, info.device_path.find_first_of("{")) == path; }), next.uvc_devices.end());
                        //                            next.usb_devices.erase(std::remove_if(next.usb_devices.begin(), next.usb_devices.end(), [&path](const usb_device_info& info)
                        //                            { return info.device_path.substr(0, info.device_path.find_first_of("{")) == path; }), next.usb_devices.end());
                        next.usb_devices = data->_backend->query_usb_devices();
                        next.hid_devices.erase(std::remove_if(next.hid_devices.begin(), next.hid_devices.end(), [&path](const hid_device_info& info)
                        { return info.device_path.substr(0, info.device_path.find_first_of("{")) == path; }), next.hid_devices.end());

                        /*if (data->_last != next)*/ data->_callback(data->_last, next);
                        data->_last = next;
                    }
                        break;
                    }
                    break;
                }

                default:
                    // Send all other messages on to the default windows handler.
                    lRet = DefWindowProc(hWnd, message, wParam, lParam);
                    break;
                }

                return lRet;
            }

            static BOOL DoRegisterDeviceInterfaceToHwnd(HWND hWnd)
            {
                auto data = reinterpret_cast<extra_data*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

                //===========================register HWmonitor events==============================
                const GUID classGuid = { 0x175695cd, 0x30d9, 0x4f87, 0x8b, 0xe3, 0x5a, 0x82, 0x70, 0xf4, 0x9a, 0x31 };
                DEV_BROADCAST_DEVICEINTERFACE devBroadcastDeviceInterface;
                devBroadcastDeviceInterface.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
                devBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
                devBroadcastDeviceInterface.dbcc_classguid = classGuid;
                devBroadcastDeviceInterface.dbcc_reserved = 0;

                data->hdevnotifyHW = RegisterDeviceNotification(hWnd,
                    &devBroadcastDeviceInterface,
                    DEVICE_NOTIFY_WINDOW_HANDLE);
                if (data->hdevnotifyHW == NULL)
                {
                    LOG_WARNING("Register HW events Failed!\n");
                    return FALSE;
                }

                ////===========================register UVC events==============================
                DEV_BROADCAST_DEVICEINTERFACE di = { 0 };
                di.dbcc_size = sizeof(di);
                di.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
                di.dbcc_classguid = KSCATEGORY_CAPTURE;

                data->hdevnotifyUVC = RegisterDeviceNotification(hWnd,
                    &di,
                    DEVICE_NOTIFY_WINDOW_HANDLE);
                if (data->hdevnotifyUVC == nullptr)
                {
                    LOG_WARNING("Register UVC events Failed!\n");
                    return FALSE;
                }

                ////===========================register UVC sensor camera events==============================
                DEV_BROADCAST_DEVICEINTERFACE di_sensor = { 0 };
                di_sensor.dbcc_size = sizeof(di_sensor);
                di_sensor.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
                di_sensor.dbcc_classguid = KSCATEGORY_SENSOR_CAMERA;

                data->hdevnotify_sensor = RegisterDeviceNotification(hWnd,
                    &di_sensor,
                    DEVICE_NOTIFY_WINDOW_HANDLE);
                if (data->hdevnotify_sensor == nullptr)
                {
                    LOG_WARNING("Register UVC events Failed!\n");
                    return FALSE;
                }
                return TRUE;
            }
        };

        std::shared_ptr<device_watcher> win7_backend::create_device_watcher() const
        {
            return std::make_shared<polling_device_watcher>(this);
        }
    }
}
