

all:	
	cc main.c filcopy.c double_slas.c slas_star.c top.c remove_spa.c -o preProcessor
stages:
	cc -E main.c -o main.i 
	cc -E filcopy.c -o filcopy.i
	cc -E double_slas.c -o double_slas.i
	cc -E slas_star.c -o slas_star.i
	cc -E top.c -o top.i
	cc -E remove_spa.c -o remove_spa.i
	
	cc -S main.i -o main.s
	cc -S filcopy.i -o filcopy.s
	cc -S double_slas.i -o double_slas.s
	cc -S slas_star.i -o slas_star.s
	cc -S top.i -o top.s
	cc -S remove_spa.i -o remove_spa.s
	
	cc -c main.s -o main.o
	cc -c filcopy.s -o filcopy.o
	cc -c double_slas.s -o double_slas.o
	cc -c slas_star.s -o slas_star.o
	cc -c top.s -o top.o
	cc -c remove_spa.s -o remove_spa.o
	
	cc main.o filcopy.o double_slas.o slas_star.o top.o remove_spa.o -o preProcessor
clean:
	rm preProcessor 1111 2222 3333 hddr hddr1 hddr2

pre:
	rm main.i main.o main.s
	rm filcopy.i filcopy.s filcopy.o
	rm double_slas.i double_slas.s double_slas.o
	rm slas_star.i slas_star.s slas_star.o
	rm top.i top.s top.o
	rm remove_spa.i remove_spa.s remove_spa.o

