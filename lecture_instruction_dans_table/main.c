#include <stdio.h>
#include <string.h>
#include "../fonctions/header/lecture_fichier.h"
#include "../fonctions/header/conversion.h"

/* Fonction qui permet de découper un string en tableau d'éléments (séparés par " " et "\n") */
void parseData(char * dataTxt, char * data []){
	char *elements;
	int i = 0;
	elements = strtok(dataTxt,"\r\n ");
	while(elements)
	{
		data[i] = elements;
		elements = strtok(NULL,"\r\n ");
		i++;
	}
}




int main()
{
	char instru[] = "ADD $1 $2 $3"; /* Instrction qui sera récupérée dans un fichier*/

	char tableTxt[10000]; /* table d'instruction en string */
	
	char *data[4]; /*Tableau qui va contenir les différents éléments de l'instruction : ["ADDI","$1","$2","$3"] */
	
	char *table[142]; /*Tableau qui va contenir toute la table d'instruction séparées par des retours à la ligne */

	int k=0; /* k : index de l'opération de l'instruction trouvé dans la table */

	char * instruction;

	char * opcode;
	char type_instruction;

	
	lecture_fichier("table_instructions.txt",tableTxt); /* Stocke la table d'instruction */

	parseData(instru,data); /* Decoupage de l'instruction */

	parseData(tableTxt,table); /* Decoupage de la table d'instruction */

	/* On recupere l'instruction dans l'opération */
	instruction = data[0];

	for (k=0 ; (strcmp(table[k],instruction)!=0) & (table[k]!=NULL) ; k+=7); /* Recherche de la ligne correspondant à l'opération */
	
	/* On récupere dans la table des instructions les valeurs suivantes : */
	opcode = table[k+1];
	type_instruction = table[k+2][0];
	
	
	int bin_operation[32]; /* opération complete en binaire */
	
	int i = 0; /* compteur qui avance dans les opérandes prévues dans la table */
	int j = 0; /* compteur qui va avancer dans les opérandes de l'instruction*/



	if (type_instruction == 'I'){ /* OPE $rd, $rs, imm*/

		int *bin_op[3];
		int op[3];

		for (i=0;i<3;i++){
			int * bin_op_temp = NULL;
			int bin_taille;
			switch(table[k+3+i][0]){
				case ('r') : 
					op[i] = atoi(data[table[k+3+i][1]-48]+1);
					bin_taille = 5;
					break;
				case ('i') : 
					op[i] = atoi(data[++j]); 
					bin_taille = 16;
					break;
				case ('0') :
					op[i] = 0; /* ça implique aussi qu'on avance en opérandes prévues par la table mais pas pour celle de l'instruction */
					bin_taille = 5;
					break; 
			} 
			
			bin_op_temp = (int *) malloc(bin_taille * sizeof(int));
			int_to_binary(op[i],bin_taille,bin_op_temp);
			bin_op[i] = bin_op_temp;

		}

		
		/* CONCATENATION */
		
	    for(i=0;i<32;i++) {
			if (i<6){
				bin_operation[i] = opcode[i]-48;
			}
			else if (i<11){
				bin_operation[i] = bin_op[0][i-6];
			}
			else if (i<16){
				bin_operation[i] = bin_op[1][i-11];
			}
			else {
				bin_operation[i] = bin_op[2][i-16];
			}	

			printf("%d",bin_operation[i]);
		}
		printf("\n");
	}
	else if (type_instruction == 'R'){ /* OPE $rd, $rs, imm*/

		char special[] = "000000";
		int *bin_op[4];
		int op[4];
	
		for (i=0;i<4;i++){
			int * bin_op_temp = NULL;
			int bin_taille;
			switch(table[k+3+i][0]){
				case ('r') : 
					op[i] = atoi(data[table[k+3+i][1]-48]+1);
					bin_taille = 5;
					break;
				case ('0') :
					op[i] = 0; /* ça implique aussi qu'on avance en opérandes prévues par la table mais pas pour celle de l'instruction */
					bin_taille = 5;
					break; 
			} 
			
			bin_op_temp = (int *) malloc(bin_taille * sizeof(int));
			int_to_binary(op[i],bin_taille,bin_op_temp);
			bin_op[i] = bin_op_temp;

		}

		
		/* CONCATENATION */
		
	    for(i=0;i<32;i++) {
			if (i<6){
				bin_operation[i] = special[i]-48;
			}
			else if (i<11){
				bin_operation[i] = bin_op[0][i-6];
			}
			else if (i<16){
				bin_operation[i] = bin_op[1][i-11];
			} 
			else if (i<21){
				bin_operation[i] = bin_op[2][i-16];
			}
			else if (i<26){
				bin_operation[i] = bin_op[3][i-21];
			}
			else {
				bin_operation[i] = opcode[i-26]-48;
			}	

			printf("%d",bin_operation[i]);
		}
		printf("\n");
	}
	

	return(0);
}