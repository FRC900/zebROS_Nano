#!/bin/bash

# Reload IPv6 networking blocks
sudo sysctl -p

sudo rfkill block wifi  
sudo rfkill block bluetooth

source /home/ubuntu/zebROS_Nano/zebROS_ws/ROSJetsonNano.sh
#echo 1100-1200,443,80,554,1735 > /proc/sys/net/ipv4/ip_local_reserved_ports

#echo 5800 5810 > /proc/sys/net/ipv4/ip_local_port_range
#systemctl restart networking

sudo chmod a+rw /dev/ttyACM0
sudo umount /mnt/900_2 --lazy

export CUDA_CACHE_MAXSIZE=104857600
export CUDA_CACHE_PATH=/home/ubuntu/.nv/ComputeCache

cd /home/ubuntu/zebROS_Nano/build
python3 -m http.server 5805 &
cd /home/ubuntu/zebROS_Nano/jetson_setup/

if sudo mount /dev/nvme0n1p1 /mnt/900_2; then
		date >> /home/ubuntu/mounted.txt
		echo worked >> /home/ubuntu/mounted.txt
		sudo chmod a+rw /mnt/900_2/
		roslaunch controller_node teleop.launch record:=true
else
		date >> /home/ubuntu/mounted.txt
		echo did not mount >> /home/ubuntu/mounted.txt
		roslaunch controller_node teleop.launch
fi

top -b > /mnt/900_2/$(date +%Y%m%d%H%M%S)_top_log.txt

v4l2-ctl -d `find /dev/v4l/by-id/ -name \*Webcam_C9\*` -c exposure_auto=1,exposure_absolute=20,brightness=5

/home/ubuntu/zebROS_Nano/jetson_setup/clocks.sh &
