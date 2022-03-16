
CC=gcc
DEL=rm -rf
CFLAGS = -Wall

OBJDIR = objs
OBJDIR_ENCODE = $(OBJDIR)/Encode
OBJDIR_DECODE = $(OBJDIR)/Decode
EXE_ENCODE=encHuff
EXE_DECODE=decHuff
DEL_TMP_FILE=*.bin *_Tmp


.PHONY: all clean cleanall

all: encode decode

ENCODE_SRC= $(addprefix $(OBJDIR_ENCODE)/,  greek.o encode.o common.o )
DECODE_SRC= $(addprefix $(OBJDIR_DECODE)/,  decode.o common.o )

$(OBJDIR_ENCODE)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_DECODE)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@


encode: $(ENCODE_SRC)
	$(CC) $(ENCODE_SRC) -o $(EXE_ENCODE)

decode:	$(DECODE_SRC)
	$(CC) $(DECODE_SRC) -o $(EXE_DECODE)


clean:
	$(DEL) $(EXE_ENCODE) $(EXE_DECODE) $(DEL_TMP_FILE) a.out

cleanall:
	$(DEL) $(OBJDIR) $(EXE_ENCODE) $(EXE_DECODE) 	
	$(DEL) $(DEL_TMP_FILE) a.out
