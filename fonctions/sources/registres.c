#include "../header/registres.h"

int * tableau_reg;


void initialisation_reg(){
    tableau_reg = (__int32_t *) calloc(34, sizeof(__int32_t)); /* 32 + Hi et Lo (repectivement 32 et 33 pour les appeler) */
}

int lecture_reg(int num_reg) {
    return tableau_reg[num_reg];
}

void ecriture_reg(int num_reg, int valeur){
    tableau_reg[num_reg] = valeur;
}
