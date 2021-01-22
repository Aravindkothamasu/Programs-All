obj-m= mouse.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o App display.c application.c tracks.c -I /usr/include/X11 -L /usr/X11/lib  /usr/lib/x86_64-linux-gnu/libSDL.a /usr/lib/x86_64-linux-gnu/libXext.a   -lX11 -lXrandr -lGLU
        

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f App

load:
	sudo insmod mouse.ko
	
un:
	sudo rmmod mouse

app:
	sudo ./App
