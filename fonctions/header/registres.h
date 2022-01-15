#ifndef __REGISTRES_H__
#define __REGISTRES_H__
#include <stdio.h>
#include <stdlib.h>

extern int * tableau_reg;
extern char * IR;
extern int PC;

void initialisation_reg();
int lecture_reg(int num_reg);
void ecriture_reg(int num_reg, int valeur);

#endif