# mouse-device-driver
Simple mouse device driver that increases brightness on right click and decreases the same on left click

Install the prerequistis to be required for run the Project.

$  sudo apt install libxxf86vm-dev \
    libsdl1.2-dev \
    libsdl-image1.2-dev \
    libsdl-mixer1.2-dev \
    libsdl-ttf2.0-dev \
    x11-xserver-utils \
    libxrandr-dev 



Steps for running Mouse Driver(needs root access):

 $ make 
 
 $ sudo insmod mouse.ko

 $ dmesg 
    Check regsiter no.
 
 $ sudo mknod /dev/MOUSE c NO 0 
 
 $ sudo chmod a+r+w /dev/MOUSE

 $ sudo ./App

