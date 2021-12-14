FLAGS = -Wall -pedantic -ansi
CC = gcc
OBJDIR = ../fonctions/obj/
SRCDIR = ../fonctions/sources/
HDRDIR = ../fonctions/header/

OBJ = main.o lecture_fichier.o conversion.o
OBJFCT = main.o $(OBJDIR)lecture_fichier.o $(OBJDIR)conversion.o

all: $(OBJ)
	$(CC) $(OBJFCT) $(FLAGS) -o exec

main.o: main.c $(HDRDIR)lecture_fichier.h
	$(CC) $(FLAGS) -c $< -o $@

lecture_fichier.o: $(SRCDIR)lecture_fichier.c $(HDRDIR)lecture_fichier.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

conversion.o: $(SRCDIR)conversion.c $(HDRDIR)conversion.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

clean:
	rm $(OBJDIR)*.o