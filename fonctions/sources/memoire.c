#include "../header/memoire.h"

int * tableau_mem;


void initialisation_mem(){
    tableau_mem = (__int32_t *) calloc(16, sizeof(__int32_t));
}

int lecture_mem(int num_mem) {
    return tableau_mem[num_mem];
}

void ecriture_mem(int num_mem, int valeur){
    tableau_mem[num_mem] = valeur;
}
