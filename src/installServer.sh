#/bin/sh
echo "::sysinit:/etc/init.d/rcS S boot
::shutdown:/etc/init.d/rcS K shutdown
#ttyATH0::askfirst:/bin/ash --login
" > /etc/inittab

git clone https://github.com/Saint-Francis-Robotics-Team2367/yunServerSoftware.git

echo "# Put your custom commands here that should be executed once
# the system init finished. By default this file does nothing.
wifi-live-or-reset
boot-complete-notify
# Uncomment the following line in order to reset the microntroller
# right after linux becomes ready
#reset-mcu
# Uncomment the following line in order to disable kernel console
# debug messages, thus having a silent and clean serial communication
# with the microcontroller
#echo 0 > /proc/sys/kernel/printk
python /home/pi/yunServerSoftware/src/pi/server.py
exit 0" > /etc/rc.local
