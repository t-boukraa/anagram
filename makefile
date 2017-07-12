CC=gcc
EXEC=goAnagram
OPT=-O2
CFLAGS=-Wall -std=c99 -o

all: $(EXEC)

$(EXEC): $(EXEC).o string.o array.o dictionary.o joker.o
	$(CC) $(OPT) $(CFLAGS) $@ $^

$(EXEC).o: $(EXEC).c string.h
	$(CC) $(OPT) -c -g $(CFLAGS) $@ $<

string.o: string.c string.h
	$(CC) $(OPT) -c -g $(CFLAGS) $@ $<

array.o: array.c string.h array.h
	$(CC) $(OPT) -c -g $(CFLAGS) $@ $<

dictionary.o: dictionary.c dictionary.h
	$(CC) $(OPT) -c -g $(CFLAGS) $@ $<
	
joker.o: joker.c joker.h string.h
	$(CC) $(OPT) -c -g $(CFLAGS) $@ $<
	
clean:
	rm -r -f *.o

mrproper: clean
	rm -f $(EXEC)
