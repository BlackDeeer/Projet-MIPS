FLAGS = -g -Wall -pedantic -ansi -lm
CC = gcc
OBJDIR = ../fonctions/obj/
SRCDIR = ../fonctions/sources/
HDRDIR = ../fonctions/header/

OBJ = registres.o memoire.o affichage.o conversion.o
OBJFCT = $(OBJDIR)registres.o $(OBJDIR)memoire.o $(OBJDIR)affichage.o $(OBJDIR)conversion.o 

all: main.o $(OBJ)
	$(CC) -g main.o $(OBJFCT) $(FLAGS) -o exec -lm -lncurses

main.o: main.c $(HDRDIR)registres.h $(HDRDIR)memoire.h $(HDRDIR)affichage.h $(HDRDIR)conversion.h
	$(CC) $(FLAGS) -c $< -o $@


# TODO #3 Automatisation du makefile

registres.o: $(SRCDIR)registres.c $(HDRDIR)registres.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

memoire.o: $(SRCDIR)memoire.c $(HDRDIR)memoire.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

affichage.o: $(SRCDIR)affichage.c $(HDRDIR)affichage.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

conversion.o: $(SRCDIR)conversion.c $(HDRDIR)conversion.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

clean:
	rm $(OBJDIR)*.o