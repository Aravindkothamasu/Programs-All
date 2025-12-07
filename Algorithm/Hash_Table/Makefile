
SOURCES = main.o Hash.o
EXE 	= hashExe
REMOVE 	= rm -rf
BUILD 	= gcc

all: $(SOURCES)
	$(BUILD) $(SOURCES) -o $(EXE)
	$(REMOVE) $(SOURCES)

clean:
	$(REMOVE) $(SOURCES) $(EXE)

