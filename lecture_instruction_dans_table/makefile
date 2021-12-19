FLAGS = -g -Wall -pedantic -ansi -lm
CC = gcc
OBJDIR = ../fonctions/obj/
SRCDIR = ../fonctions/sources/
HDRDIR = ../fonctions/header/

OBJ = fichier.o conversion.o
OBJFCT = $(OBJDIR)fichier.o $(OBJDIR)conversion.o 

all: main.o $(OBJ)
	$(CC) -g main.o $(OBJFCT) $(FLAGS) -o exec -lm

main.o: main.c $(HDRDIR)fichier.h
	$(CC) $(FLAGS) -c $< -o $@


# TODO #3 Automatisation du makefile

fichier.o: $(SRCDIR)fichier.c $(HDRDIR)fichier.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

conversion.o: $(SRCDIR)conversion.c $(HDRDIR)conversion.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@ -lm

clean:
	rm $(OBJDIR)*.o