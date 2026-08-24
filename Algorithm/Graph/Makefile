
SOURCES = ./graph.o ./algo.o ./main.o
EXE 	= graphExe
REMOVE 	= rm -rf
BUILD 	= gcc
FLAGS   = -Wunused-variable
FLAGS  += -Werror

all: $(SOURCES)
	$(BUILD) $(SOURCES) $(FLAGS) -o $(EXE)
	$(REMOVE) $(SOURCES)

clean:
	$(REMOVE) $(SOURCES) $(EXE)

