#ifndef __TRADUCTION_H__
#define __TRADUCTION_H__

#define TAILLE_TABLE 175 /* Taille de la table d'instructions */

extern char* table[TAILLE_TABLE];

char** traduction(char* fichier, char* destHexa);
void init_table(char* table[]);
void assembleur_str_to_hexa(char * assembleur_string, char hexa_operation[],char *table[], int ligne_courante, int interactif);

#endif