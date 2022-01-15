#ifndef __MEMOIRE_H__
#define __MEMOIRE_H__
#include <stdio.h>
#include <stdlib.h>

extern int * tableau_mem;

void initialisation_mem();
int lecture_mem(int num_mem);
void ecriture_mem(int num_mem, int valeur);

#endif