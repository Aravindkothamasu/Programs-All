
SOURCES = main.o Hash.o
EXE 	= hashExe
REMOVE 	= rm -rf
BUILD 	= gcc
FLAGS   = -Wunused-variable
FLAGS  += -Werror

all: $(SOURCES)
	$(BUILD) $(SOURCES) $(FLAGS) -o $(EXE)
	$(REMOVE) $(SOURCES)

clean:
	$(REMOVE) $(SOURCES) $(EXE)

