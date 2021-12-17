FLAGS = -g -Wall -pedantic -ansi -lm
CC = gcc
OBJDIR = ../fonctions/obj/
SRCDIR = ../fonctions/sources/
HDRDIR = ../fonctions/header/

OBJ = lecture_fichier.o conversion.o
OBJFCT = $(OBJDIR)lecture_fichier.o $(OBJDIR)conversion.o

all: main.o $(OBJ)
	$(CC) -g main.o $(OBJFCT) $(FLAGS) -o exec

main.o: main.c $(HDRDIR)lecture_fichier.h
	$(CC) $(FLAGS) -c $< -o $@


# TODO #3 Automatisation du makefile

lecture_fichier.o: $(SRCDIR)lecture_fichier.c $(HDRDIR)lecture_fichier.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

conversion.o: $(SRCDIR)conversion.c $(HDRDIR)conversion.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

clean:
	rm $(OBJDIR)*.o