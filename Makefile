CC=gcc
CFLAGS=-W -Wall -g
EXEC=openfleetsim
OBJECTS=simulate.o player.o random.o main.o constant.o

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
