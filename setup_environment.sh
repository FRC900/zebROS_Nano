#!/bin/bash
# Script to setup Jetson TX2 environment. Probably would also work
# with slight modifications on other Jetson hardware

#install basic dependencies
sudo apt update
sudo apt -y upgrade

# These are listed 1 package per line to hopefully make git merging easier
# They're also sorted alphabetically to keep packages from being listed multiple times
sudo apt install -y \
	build-essential \
	can-utils \
	ccache \
	chromium-browser \
	cmake \
	cowsay \
	exfat-fuse \
	exfat-utils \
	gdb \
	gfortran \
	git \
	gstreamer1.0-plugins-* \
	htop \
	libatlas-base-dev \
	libboost-all-dev \
	libeigen3-dev \
	libflann-dev \
	libgflags-dev \
	libgoogle-glog-dev \
	libgtk2.0-dev \
	libhdf5-dev \
	libhdf5-serial-dev \
	libleveldb-dev \
	liblmdb-dev \
	liblua5.3-dev \
	libpcl-dev \
	libproj-dev \
	libprotobuf-dev \
	libsnappy-dev \
	libsuitesparse-dev \
	libtinyxml2-dev \
	net-tools \
	ninja-build \
	nmap \
	ntp \
	ntpdate \
	openssh-client \
	pkg-config \
	protobuf-compiler \
	python-dev \
	python-matplotlib \
	python-numpy \
	python-opencv \
	python-pip \
	python-scipy \
	rsync \
	software-properties-common \
	terminator \
	unzip \
	v4l-conf \
	v4l-utils \
	vim-gtk \
	wget \
	xfonts-scalable

#install caffe
# cd
# git clone https://github.com/BVLC/caffe.git
# cd caffe
# mkdir build
# cd build

# if [ "$gpu" == "false" ] ; then
	# cmake -DCPU_ONLY=ON ..
# else
	# cmake -DCUDA_USE_STATIC_CUDA_RUNTIME=OFF ..
# fi

# make -j4 all
#make test
#make runtest
# make -j4 install

# Install tinyxml2
cd
git clone https://github.com/leethomason/tinyxml2.git
cd tinyxml2
mkdir build
cd build
cmake ..
make -j4
sudo make install
cd ../..
rm -rf tinyxml2

#install zed sdk
zed_fn="jetson_jp42"
wget --no-check-certificate https://www.stereolabs.com/download/$zed_fn
chmod 755 $zed_fn
./$zed_fn
rm ./$zed_fn

#mount and setup autostart script
sudo mkdir /mnt/900_2
cd ~/zebROS_Nano

# edit /etc/init.d/ntp to contain the line: <ntpd -gq> before all content already there.
sudo cp ntp-client.conf /etc/ntp.conf  # edit /etc/ntp.conf to be a copy of ntp-client.conf in zebROS_Nano

# Set up can0 network interface
cd
echo "auto can0" > can0
echo "iface can0 inet manual" >> can0
echo "  pre-up /sbin/ip link set can0 type can bitrate 1000000" >> can0
echo "  up /sbin/ifconfig can0 up" >> can0
echo "  down /sbin/ifconfig can0 down" >> can0
sudo mv can0 /etc/network/interfaces.d

sudo bash -c "echo \"# Modules for CAN interface\" >> /etc/modules"
sudo bash -c "echo can >> /etc/modules"
sudo bash -c "echo can_raw >> /etc/modules"
sudo bash -c "echo can_dev >> /etc/modules"
sudo bash -c "echo gs_can >> /etc/modules"
#sudo bash -c "echo mttcan >> /etc/modules"

# This shouldn't be the least bit dangerous
#sudo rm /etc/modprobe.d/blacklist-mttcan.conf 

# Disable l4tbridge - https://devtalk.nvidia.com/default/topic/1042511/is-it-safe-to-remove-l4tbr0-bridge-network-on-jetson-xavier-/
# sudo rm /etc/systemd/system/nv-l4t-usb-device-mode.sh /etc/systemd/system/multi-user.target.wants/nv-l4t-usb-device-mode.service
sudo systemctl disable nv-l4t-usb-device-mode.service
sudo systemctl stop nv-l4t-usb-device-mode.service

# Set up ssh host config (add port 5801) 
sudo sed "s/#Port 22/Port 22\nPort 5801/g" /etc/ssh/sshd_config > sshd_config && sudo mv sshd_config /etc/ssh
	
# and keys for connections to Rio
mkdir -p ~/.ssh
cd ~/.ssh
tar -xjf ~/zebROS_Nano/jetson_setup/jetson_dot_ssh.tar.bz2 
chmod 640 authorized_keys
cd ~
chmod 700 .ssh

sudo mkdir -p /root/.ssh
sudo tar -xjf /home/ubuntu/zebROS_Nano/jetson_setup/jetson_dot_ssh.tar.bz2 -C /root/.ssh
sudo chmod 640 /root/.ssh/authorized_keys
sudo chmod 700 /root/.ssh

cd ~/zebROS_Nano
sudo cp ./jetson_setup/10-local.rules /etc/udev/rules.d/
sudo service udev reload
sleep 2
sudo service udev restart

if /bin/false; then
	# Kernel module build steps for TX2 : https://gist.github.com/sauhaardac/9d7a82c23e4b283a1e79009903095655
	# Not needed unless Jetpack is updated with a new kernel version and modules
	# for a given kernel version aren't already built
	#
	# This is a PR into the jetsonhacks repo of the same name, will likely be
	# gone the next time anyone looks for it
	# Also, this says Xavier but it really seems to mean Jetpack 4.x, in the
	# case of this particular PR, 4.2. Which is what we're using for the TX2
	# systems as well.
	cd
	git clone https://github.com/klapstoelpiloot/buildLibrealsense2Xavier.git 
	# Note - need to switch back to the default linker to build the kernel image
	cd
	wget https://developer.nvidia.com/embedded/dlc/l4t-sources-32-1-JAX-TX2 -O l4t-sources-32-1-JAX-TX2.tbz2
	tar -xf l4t-sources-32-1-JAX-TX2.tbz2 public_sources/kernel_src.tbz2
	tar -xf public_sources/kernel_src.tbz2
	cd ..
	cd ~/kernel/kernel-4.4

	## Apply realsense patches to modules
	patch -p1 < ~/buildLibrealsense2Xavier/patches/realsense-camera-formats_ubuntu-bionic-Xavier-4.9.140.patch 
	patch -p1 < ~/buildLibrealsense2Xavier/patches/realsense-metadata-ubuntu-bionic-Xavier-4.9.140.patch
	patch -p1 < ~/buildLibrealsense2Xavier/patches/realsense-hid-ubuntu-bionic-Xavier-4.9.140.patch
	patch -p1 < ~/librealsense-2.21.0/scripts/realsense-powerlinefrequency-control-fix.patch
	# These are for the librealsense code, but don't actually seem to be used
	#patch -p1 < ~/buildLibrealsense2Xavier/patches/model-views.patch
	#patch -p1 < ~/buildLibrealsense2Xavier/patches/incomplete-frame.patch
	rm -rf ~/buildLibrealsense2Xavier

	# turn on various config settings needed for USB tty, realsense, nvme, etc
	zcat /proc/config.gz > .config
	bash scripts/config --file .config \
	   	--set-str LOCALVERSION -tegra \
		--enable IIO_BUFFER \
		--enable IIO_KFIFO_BUF  \
		--module IIO_TRIGGERED_BUFFER  \
		--enable IIO_TRIGGER  \
		--set-val IIO_CONSUMERS_PER_TRIGGER 2  \
		--module HID_SENSOR_IIO_COMMON  \
		--module HID_SENSOR_IIO_TRIGGER  \
		--module HID_SENSOR_HUB  \
		--module HID_SENSOR_ACCEL_3D  \
		--module HID_SENSOR_GYRO_3D  \
		--module USB_ACM  \
		--module CAN_GS_USB  \
		--module JOYSTICK_XPAD  \
		--enable CONFIG_BLK_DEV_NVME

	make -j6 clean
	make -j6 prepare
	make -j6 modules_prepare
    make -j6 Image zImage
    make -j6 modules
	sudo make -j6 modules_install

	sudo depmod -a

	# make -j6 M=drivers/usb/class
	# make -j6 M=drivers/usb/serial
	# make -j6 M=drivers/net/can
	# make -j6 M=net/can
	# sudo mkdir -p /lib/modules/`uname -r`/kernel/drivers/usb/serial
	# sudo cp drivers/usb/class/cp210x-acm.ko /lib/modules/`uname -r`/kernel/drivers/usb/serial/cp210x-acm.ko
	# sudo mkdir -p /lib/modules/`uname -r`/kernel/drivers/usb/class
	# sudo cp drivers/usb/serial/cdc-acm.ko /lib/modules/`uname -r`/kernel/drivers/usb/class/cdc-acm.ko
	# sudo mkdir -p /lib/modules/`uname -r`/kernel/drivers/usb/class
	# sudo cp drivers/net/can/usb/gs_usb.ko /lib/modules/`uname -r`/kernel/drivers/net/can/usb

	# sudo mkdir -p /lib/modules/`uname -r`/kernel/drivers/joystick
	# sudo cp xpad.ko /lib/modules/`uname -r`/kernel/drivers/joystick/xpad.ko
	# sudo depmod -a
fi

# Clean up Jetson
sudo rm -rf /home/nvidia/cudnn /home/nvidia/OpenCV /home/nvidia/TensorRT /home/nvidia/libvisionworkd*
# Save ~400MB
sudo apt remove --purge -y thunderbird libreoffice-*

# Install CTRE & navX libs
mkdir -p /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/include 
mkdir -p /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/lib/ctre 
cd /home/ubuntu 
wget -e robots=off -U mozilla -r -np http://devsite.ctr-electronics.com/maven/release/com/ctre/phoenix/ -A "*5.14.1*,firmware-sim*zip" -R "md5,sha1,pom,jar,*windows*"
cd /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/include 
find /home/ubuntu/devsite.ctr-electronics.com -name \*headers\*zip | xargs -n 1 unzip -o 
cd /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/lib/ctre 
find /home/ubuntu/devsite.ctr-electronics.com -name \*linux\*zip | xargs -n 1 unzip -o 
rm -rf /home/ubuntu/devsite.ctr-electronics.com 

cd /home/ubuntu 
wget http://www.kauailabs.com/maven2/com/kauailabs/navx/frc/navx-cpp/3.1.366/navx-cpp-3.1.366-headers.zip 
mkdir -p /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/include/navx 
cd /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/include/navx 
unzip -o /home/ubuntu/navx-cpp-3.1.366-headers.zip 
rm /home/ubuntu/navx-cpp-3.1.366-headers.zip 
cd /home/ubuntu 
wget http://www.kauailabs.com/maven2/com/kauailabs/navx/frc/navx-cpp/3.1.366/navx-cpp-3.1.366-linuxathena.zip 
mkdir -p /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/lib/navx 
cd /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/lib/navx 
unzip -o /home/ubuntu/navx-cpp-3.1.366-linuxathena.zip 
rm /home/ubuntu/navx-cpp-3.1.366-linuxathena.zip 
cd /home/ubuntu 
wget http://www.kauailabs.com/maven2/com/kauailabs/navx/frc/navx-cpp/3.1.366/navx-cpp-3.1.366-linuxathenastatic.zip 
cd /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/lib/navx 
unzip -o /home/ubuntu/navx-cpp-3.1.366-linuxathenastatic.zip 
rm /home/ubuntu/navx-cpp-3.1.366-linuxathenastatic.zip 

# Install wpilib headers by copying them from the local maven dir
cd /home/ubuntu 
wget https://github.com/wpilibsuite/allwpilib/releases/download/v2019.4.1/WPILib_Linux-2019.4.1.tar.gz 
mkdir -p /home/ubuntu/frc2019 
cd /home/ubuntu/frc2019 
tar -xzf /home/ubuntu/WPILib_Linux-2019.4.1.tar.gz 
rm /home/ubuntu/WPILib_Linux-2019.4.1.tar.gz 
cd /home/ubuntu/frc2019/tools 
python ToolsUpdater.py 
mkdir -p /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/lib/wpilib 
cd /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/lib/wpilib 
find ../../../.. -name \*athena\*zip | xargs -n1 unzip -o 
mkdir -p /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/include/wpilib 
cd /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/include/wpilib 
find ../../../.. -name \*headers\*zip | xargs -n1 unzip -o 
rm -rf /home/ubuntu/frc2019/maven /home/ubuntu/frc2019/jdk
sed -i -e 's/   || defined(__thumb__) \\/   || defined(__thumb__) \\\n   || defined(__aarch64__) \\/' /home/ubuntu/frc2019/roborio/arm-frc2019-linux-gnueabi/include/wpilib/FRC_FPGA_ChipObject/fpgainterfacecapi/NiFpga.h

# Set up prereqs for deploy script
mv ~/zebROS_Nano ~/zebROS_Nano.orig
ln -s ~/zebROS_Nano.orig ~/zebROS_Nano
mkdir -p ~/zebROS_Nano.prod/zebROS_ws
mkdir -p ~/zebROS_Nano.dev/zebROS_ws

sudo mkdir -p /usr/local/zed/settings
sudo chmod 755 /usr/local/zed/settings
sudo cp ~/zebROS_Nano/calibration_files/*.conf /usr/local/zed/settings
sudo chmod 644 /usr/local/zed/settings/*

cp ~/zebROS_Nano/.vimrc ~/zebROS_Nano/.gvimrc ~
sudo cp ~/zebROS_Nano/kjaget.vim /usr/share/vim/vim80/colors

git config --global user.email "progammers@team900.org"
git config --global user.name "Team900 Jetson TX2"

# Set up Gold linker - speed up libPCL links
sudo update-alternatives --install "/usr/bin/ld" "ld" "/usr/bin/ld.gold" 20
sudo update-alternatives --install "/usr/bin/ld" "ld" "/usr/bin/ld.bfd" 10

echo | sudo update-alternatives --config ld

echo "source /home/ubuntu/zebROS_Nano/zebROS_ws/command_aliases.sh" >> /home/ubuntu/.bashrc

