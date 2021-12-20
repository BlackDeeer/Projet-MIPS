#include <stdio.h>
#include <string.h>
#include "../fonctions/header/fichier.h"
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
	char instru[] = "BGTZ $2 54"; /* Instrction qui sera récupérée dans un fichier LW $3 54(2) ADDI $2,$0,5 */

	char tableTxt[10000]; /* table d'instruction en string */
	
	char *data[4]; /*Tableau qui va contenir les différents éléments de l'instruction : ["ADDI","$1","$2","$3"] */
	
	char *table[156]; /*Tableau qui va contenir toute la table d'instruction séparées par des retours à la ligne */

	int k=0; /* k : index de l'opération de l'instruction trouvé dans la table */

	char * instruction; /* va contenir l'instruction "ADD" par exemple */

	char * opcode; /* va contenir l'opcode trouvé correspondant à l'instruction dans la table */
	char type_instruction;

	int bin_operation[32]; /* opération complète en binaire */

	char hexa_operation[8]; /* opération complète en hexadécimal */


	int i = 0; /* compteur qui avance dans les opérandes prévues dans la table */
	int j = 0; /* compteur qui va avancer dans les opérandes de l'instruction*/
	
	lecture_fichier("table_instructions.txt",tableTxt); /* Stocke la table d'instruction */

	parseData(instru,data); /* Decoupage de l'instruction */

	parseData(tableTxt,table); /* Decoupage de la table d'instruction */

	/* On recupere l'instruction dans l'opération */
	instruction = data[0];

	for (k=0 ; (strcmp(table[k],instruction)!=0) & (table[k]!=NULL) ; k+=7); /* Recherche de la ligne correspondant à l'opération */
	
	/* On récupere dans la table des instructions les valeurs suivantes : */
	opcode = table[k+1];
	type_instruction = table[k+2][0];
	
	


	if (type_instruction == 'I'){ /* OPE $rd, $rs, imm*/

		int *bin_op[3];
		int op[3];
		char * split;
		for (i=0;i<3;i++){
			int * bin_op_temp = NULL;
			int bin_taille;
			switch(table[k+3+i][0]){
				case ('r') : 
					op[i] = atoi(data[table[k+3+i][1]-48]+1);
					bin_taille = 5;
					++j;
					break;
				case ('i') : 
					op[i] = atoi(data[++j]); 
					bin_taille = 16;
					break;
				case ('0') :
					op[i] = 0; /* ça implique aussi qu'on avance en opérandes prévues par la table mais pas pour celle de l'instruction */
					bin_taille = 5;
					break; 
				case ('b') :
					split = strtok(data[2],"()");
					split = strtok(NULL,"()");
					op[i] = atoi(split);
					bin_taille = 5;
					break;
				case ('o') :
					op[i] = atoi(data[2]);
					bin_taille = 16;
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
	else if (type_instruction == 'R'){ /* OPE $rd, $rs1, $rs2*/

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
	else if (type_instruction == 'J'){ /* OPE instr_index*/

		int * bin_instr_index = NULL;
		bin_instr_index = (int *) malloc(26 * sizeof(int));
		int_to_binary(atoi(data[1]),26,bin_instr_index);
		
		
		/* CONCATENATION */
		
	    for(i=0;i<32;i++) {
			if (i<6){
				bin_operation[i] = opcode[i]-48;
			}
			else {
				bin_operation[i] = bin_instr_index[i-6];
			}	

			printf("%d",bin_operation[i]);
		}
		printf("\n");


	}

	/* On traduit le résultat binaire en hexadécimal */
	bin_to_hexa(32,bin_operation,hexa_operation);
	printf("\n0x%s\n",hexa_operation);

	/* Il faut stocker les résultats en hexadécimal dans un tableau pour pouvoir l'utiliser pour écrire dans le fichier txt final */
	int nb_instruction = 2;
	char** tableauHexa = NULL;

	tableauHexa = malloc(nb_instruction * sizeof(char*));
	char *valeur0 = malloc(8);
	char *valeur1 = malloc(8);
	
	valeur0 = "73039000";
	valeur1 = "730391BA";
	tableauHexa[0] = valeur0;

   	tableauHexa[1] = valeur1 ;

	tableauHexa[nb_instruction] = '\0';

	ecriture_fichier("resultat_hexa",tableauHexa,nb_instruction);


	return(0);
}