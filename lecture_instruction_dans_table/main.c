#include <stdio.h>
#include <string.h>
#include "../fonctions/header/lecture_fichier.h"
#include "../fonctions/header/conversion.h"

/* Fonction qui permet de découper un string en tableau d'éléments (séparés par " " et "\n") */
void parseData(char * dataTxt, char * data []){
	char *elements;
	int i = 0;
	elements = strtok(dataTxt,"\n ");
	while(elements)
	{
		data[i] = elements;
		elements = strtok(NULL,"\n ");
		i++;
	}
}




int main()
{
	char instru[] = "BEQ $3 $2 20"; /* Instrction qui sera récupérée dans un fichier*/

	char tableTxt[10000]; /* table d'instruction en string */
	
	char *data[4]; /*Tableau qui va contenir les différents éléments de l'instruction : ["ADDI","$1","$2","$3"] */
	
	char *table[30]; /*Tableau qui va contenir toute la table d'instruction séparées par des retours à la ligne */

	int k=0; /* k : index de l'opération de l'instruction trouvé dans la table */

	char * instruction;

	char * opcode;
	char type_instruction;

	
	lecture_fichier("table_instructions.txt",tableTxt); /* Stocke la table d'instruction */

	parseData(instru,data); /* Decoupage de l'instruction */

	parseData(tableTxt,table); /* Decoupage de la table d'instruction */

	/* On recupere l'instruction dans l'opération */
	instruction = data[0];

	for (k=0 ; (strcmp(table[k],instruction)!=0) & (table[k]!=NULL) ; k+=3); /* Recherche de la ligne correspondant à l'opération */
	
	/* On récupere dans la table des instructions les valeurs suivantes : */
	opcode = table[k+1];
	type_instruction = table[k+2][0];
	
	
	if (type_instruction == 'I'){ /* OPE $rd, $rs, imm*/
		
		int op1 = atoi(data[1]+1); /* rd sans "$" */
		int op2 = atoi(data[2]+1); /* rs sans "$" */
		int op3 = atoi(data[3]); /* val imm */

		int bin_op1[5];
		int bin_op2[5];
		int bin_op3[16];
		
		int bin_operation[32]; /* opération complete en binaire */
		int i = 0; /* index de concaténation */

		int_to_binary(op1,5,bin_op1);
		int_to_binary(op2,5,bin_op2);
		int_to_binary(op3,16,bin_op3);


		/* CONCATENATION */
		
	    for(i=0;i<32;i++) {
			if (i<6){
				bin_operation[i] = opcode[i]-48;
			}
			else if (i<11){
				bin_operation[i] = bin_op1[i-6];
			}
			else if (i<16){
				bin_operation[i] = bin_op2[i-11];
			}
			else {
				bin_operation[i] = bin_op3[i-16];
			}	

			printf("%d",bin_operation[i]);
		}
		printf("\n");
	}
	

	return(0);
}