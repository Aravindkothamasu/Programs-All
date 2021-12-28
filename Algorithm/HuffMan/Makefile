
CC=gcc
DEL=rm -f

ENCODE_SRC=greek.o encode.o common.o 
DECODE_SRC=decode.o common.o
DEST_ENCODE=encHuff
DEST_DECODE=decHuff
DEL_TMP_FILE=*.bin *_Tmp


all: $(ENCODE_SRC) $(DECODE_SRC)
	$(CC) $(ENCODE_SRC) -o $(DEST_ENCODE)
	$(CC) $(DECODE_SRC) -o $(DEST_DECODE)


encode: $(ENCODE_SRC)
	$(CC) $(ENCODE_SRC) -o $(DEST_ENCODE)

decode:	$(DECODE_SRC)
	$(CC) $(DECODE_SRC) -o $(DEST_DECODE)


clean:
	$(DEL) $(DEST_ENCODE) $(DEST_DECODE) $(DEL_TMP_FILE) a.out

cleanall:
	$(DEL) $(DEST_ENCODE) $(DEST_DECODE) $(ENCODE_SRC) $(DECODE_SRC) 	
	$(DEL) $(DEL_TMP_FILE) a.out
