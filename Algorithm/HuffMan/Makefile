
CC=gcc
DEL=rm -rf
CFLAGS = -Wall

OBJDIR = objs
OBJDIR_ENCODE = $(OBJDIR)/Encode
OBJDIR_DECODE = $(OBJDIR)/Decode

LOGDIR = logs
LOGDIR_ENCODE = $(LOGDIR)/Encode
LOGDIR_DECODE = $(LOGDIR)/Decode

EXE_ENCODE=encHuff
EXE_DECODE=decHuff
DEL_TMP_FILE=*.bin *_cpy


.PHONY: all clean cleanall

all: encode decode

ENCODE_SRC= $(addprefix $(OBJDIR_ENCODE)/,  src/greek.o src/encode.o src/common.o )
DECODE_SRC= $(addprefix $(OBJDIR_DECODE)/,  src/decode.o src/common.o )

$(OBJDIR_ENCODE)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_DECODE)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@


encode: $(ENCODE_SRC)
	@mkdir -p $(LOGDIR_ENCODE)
	$(CC) $(ENCODE_SRC) -o $(EXE_ENCODE)

decode:	$(DECODE_SRC)
	@mkdir -p $(LOGDIR_DECODE)
	$(CC) $(DECODE_SRC) -o $(EXE_DECODE)


clean:
	$(DEL) $(EXE_ENCODE) $(EXE_DECODE) $(OBJDIR) a.out

cleanall:
	$(DEL) $(OBJDIR) $(EXE_ENCODE) $(EXE_DECODE) 	
	$(DEL) $(DEL_TMP_FILE) $(LOGDIR) a.out
