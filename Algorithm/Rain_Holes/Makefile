
CC=gcc
DEL=rm -f
DEL_TMP_FILE=*.ra
SRC=extra.o new.o support.o
EXECUTABLE=rainHolesExe
CFLAGS = -static -Wall
TIME=time


all: $(SRC)
	$(DEL) $(DEL_TMP_FILE) a.out
	$(CC) $(CFLAGS) $(SRC) -o $(EXECUTABLE) 
clean:
	$(DEL) $(DEL_TMP_FILE) a.out $(EXECUTABLE) $(SRC)
