#include <stdio.h>
#include <string.h>
#include "../fonctions/header/fichier.h"
#include "../fonctions/header/conversion.h"

/* Fonction qui permet de découper un string en tableau d'éléments (séparés par " " et "\n") */
void decoupage_data(char * dataTxt, char * data [], char * separateurs){
	char *elements;
	int i = 0;
	/*On cherche à récupérer, un à un, tous les mots de notre fichier texte compris entre les séparateurs et on commence par le premier.*/
	elements = strtok(dataTxt,separateurs);
	while(elements)
	{
		/* On passe au séparateur suivants et on stocke l'élément dans un tableau */
		data[i] = elements; 
		elements = strtok(NULL, separateurs);
		i++;
	}

}

void assembleur_str_to_hexa(char * assembleur_string, char hexa_operation[],char *table[]){

	
	char *data[4]; /*Tableau qui va contenir les différents éléments de l'instruction : ["ADDI","$1","$2","$3"] */
	
	int k=0; /* k : index de l'opération de l'instruction trouvé dans la table */

	char * instruction; /* va contenir l'instruction "ADD" par exemple */

	char * opcode; /* va contenir l'opcode trouvé correspondant à l'instruction dans la table */
	char type_instruction;

	int bin_operation[32]; /* opération complète en binaire */



	int i = 0; /* compteur qui avance dans les opérandes prévues dans la table */
	int j = 0; /* compteur qui va avancer dans les opérandes de l'instruction*/
	
	char * separateurs = " ,\n";

	decoupage_data(assembleur_string,data,separateurs); /* Decoupage de l'instruction */



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

	


	return(0);
}


int main()
{

	/* Lecture du jeu d'instruction */
	char tableTxt[10000]; /* table d'instruction en string */
	char *table[156]; /*Tableau qui va contenir toute la table d'instruction séparées par des retours à la ligne */
	lecture_fichier("table_instructions.txt",tableTxt); /* Stocke la table d'instruction */
	char * separateurs_data = " ,\n";
	decoupage_data(tableTxt,table,separateurs_data); /* Decoupage de la table d'instruction */
	
	
	/* Lecture du fichier assembleur */
	int i = 0;
	char * separateurs_lignes = "\n";
	char assembleur_txt[1000];
	char *assembleur_lignes[100];
	lecture_fichier("in2.txt",assembleur_txt);
	decoupage_data(assembleur_txt,assembleur_lignes,separateurs_lignes); 

	/* Il faut stocker les résultats en hexadécimal dans un tableau pour pouvoir l'utiliser pour écrire dans le fichier txt final */
	int nb_instruction = 100;
	/*
	char** tableauHexa = NULL;
	tableauHexa = malloc(nb_instruction * sizeof(char*)); */

	char *tableauHexa[100];
	while(strcmp(assembleur_lignes[i],"\0") != 0)
	{
		char hexa_operation[8];
		printf("%s\n",assembleur_lignes[i]);
		assembleur_str_to_hexa(assembleur_lignes[i], hexa_operation, table);
		printf("0x%s\n",hexa_operation);
		/*char *valeur = malloc(8);
		valeur = hexa_operation; */
		tableauHexa[i] = hexa_operation;
		i++;
	}

	tableauHexa[nb_instruction] = '\0';
	ecriture_fichier("resultat_hexa.txt",tableauHexa,nb_instruction);
	printf("\nEcriture du fichier OK\n");
	
	return 0;
}

