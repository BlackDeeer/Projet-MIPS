FLAGS = -Wall -pedantic -ansi
CC = gcc
OBJDIR = ../fonctions/obj/

OBJ = main.o $(OBJDIR)lecture_fichier.o

all: $(OBJ)
	$(CC) $(OBJ) $(FLAGS) -o exec

main.o: main.c ../fonctions/header/lecture_fichier.h
	$(CC) $(FLAGS) -c $< -o $@

lecture_fichier.o: ../fonctions/sources/lecture_fichier.c ../fonctions/header/lecture_fichier.h
	$(CC) $(FLAGS) -c $< -o $(OBJDIR)$@

clean:
	rm *.o