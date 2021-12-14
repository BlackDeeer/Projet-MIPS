BIN = Executable
OBJ = ADD.o 
CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

all: $(OBJ)
	mkdir -p exe
	$(CC) obj/*.o -o exe/$(BIN) -lm

ADD.o: ADD.c 
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o obj/$@

run: all
	./exe/$(BIN)

clean:
	rm -r exe
	rm -r obj

debug:
	ddd exe/$(BIN)
