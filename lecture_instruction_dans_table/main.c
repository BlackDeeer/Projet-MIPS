#include <stdio.h>
#include <string.h>
#include "../fonctions/header/fichier.h"
#include "../fonctions/header/conversion.h"

#define TAILLE_TABLE 156

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

void assembleur_str_to_hexa(char * assembleur_string, char hexa_operation[],char *table[], int ligne_courante){

	
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

	for (k=0 ; (k<TAILLE_TABLE) && (strcmp(table[k],instruction)!=0); k+=7); /* Recherche de la ligne correspondant à l'opération */
	if (k>TAILLE_TABLE){
		fprintf(stderr,"ERREUR : L'instruction à la ligne %d n'est pas reconnue\n",ligne_courante);
		exit(EXIT_FAILURE);
	}

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
					if (data[table[k+3+i][1]-48][0]!='$'){
						fprintf(stderr,"ERREUR : A la ligne %d, l'opérande n°%d doit être un registre ...\n",ligne_courante,table[k+3+i][1]-48);
						exit(EXIT_FAILURE);
					} else if (atoi(data[table[k+3+i][1]-48]+1)>63 || atoi(data[table[k+3+i][1]-48]+1)<0 ) {
						fprintf(stderr,"ERREUR : A la ligne %d, le registre %d doit être compris entre 0 et 63 ...\n",ligne_courante,table[k+3+i][1]-48);
						exit(EXIT_FAILURE);
					}
					op[i] = atoi(data[table[k+3+i][1]-48]+1);
					bin_taille = 5;
					++j;
					break;
				case ('i') : 
					++j;
					if (data[j][0]=='$'){
						fprintf(stderr,"ERREUR : A la ligne %d, l'opérande n°%d doit être une valeur\n",ligne_courante,table[k+3+i][1]-48);
						exit(EXIT_FAILURE);
					} else if (atoi(data[j])>131071 || atoi(data[j])<0 ) {
						fprintf(stderr,"ERREUR : A la ligne %d, la valeur immédiate doit être comprise entre 0 et 131071\n",ligne_courante,table[k+3+i][1]-48);
						exit(EXIT_FAILURE);
					}
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

			/*printf("%d",bin_operation[i]);*/
		}
		/*printf("\n");*/


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
					if (data[table[k+3+i][1]-48][0]!='$'){
						fprintf(stderr,"ERREUR : A la ligne %d, l'opérande n°%d doit être un registre ...\n",ligne_courante,table[k+3+i][1]-48);
						exit(EXIT_FAILURE);
					} else if (atoi(data[table[k+3+i][1]-48]+1)>63 || atoi(data[table[k+3+i][1]-48]+1)<0 ) {
						fprintf(stderr,"ERREUR : A la ligne %d, le registre %d doit être compris entre 0 et 63 ...\n",ligne_courante,table[k+3+i][1]-48);
						exit(EXIT_FAILURE);
					}
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

			/* printf("%d",bin_operation[i]); */
		}
		/*printf("\n");*/


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

			/*printf("%d",bin_operation[i]);*/
		}
		/*printf("\n");*/


	}
	/* On traduit le résultat binaire en hexadécimal */
	bin_to_hexa(32,bin_operation,hexa_operation);

	


}


int main()
{

	/* Lecture du jeu d'instruction */
	char tableTxt[10000]; /* table d'instruction en string */
	char *table[TAILLE_TABLE]; /*Tableau qui va contenir toute la table d'instruction séparées par des retours à la ligne */
	lecture_fichier("table_instructions.txt",tableTxt); /* Stocke la table d'instruction */
	char * separateurs_data = " ,\n";
	decoupage_data(tableTxt,table,separateurs_data); /* Decoupage de la table d'instruction */
	
	/* -------------------------------------- DEBUT LECTURE LIGNE PAR LIGNE ---------------------------------*/
	char *tableauHexa[4];
	int ligne_courante = 1;
	int ligne_utiles = 0;


	FILE * fichier_txt = fopen("in2.txt","r");

	if (fichier_txt == NULL){
		perror("Impossible d'ouvrir le fichier");
		exit(EXIT_FAILURE);
	}

	char fragment[4];
	/* On va stocker les fragments dans un tampon de ligne */
	size_t longueur_fragment = sizeof(fragment); /* type size_t = entier naturels pas de nombre négatif ! (on peut le remplacer par int si jamais mais inutile)*/
	char *ligne = malloc(longueur_fragment); /* On va le realloc plus tard */

	if (ligne == NULL){
		perror("Impossible d'allouer de la mémoire au tampon de la ligne");
		exit(EXIT_FAILURE);
	}

	/* On vide la chaine de caractere : ligne = "" */
	ligne[0] = '\0';


	while(fgets(fragment, sizeof(fragment), fichier_txt) != NULL){

		size_t longueur_ligne_utilisee = strlen(ligne); /* au debut : 0 */
		size_t longueur_fragment_utilisee = strlen(fragment); /* au debut : 32 */

		if (longueur_fragment-longueur_ligne_utilisee<longueur_fragment_utilisee) {
			longueur_fragment *= 2;
			ligne = realloc(ligne, longueur_fragment);
			if (ligne == NULL){
				perror("Impossible d'allouer plus de  mémoire au tampon de ligne");
				free(ligne);
				exit(EXIT_FAILURE);
			}
		}

		strncpy(ligne + longueur_ligne_utilisee, fragment, longueur_fragment-longueur_ligne_utilisee);
		longueur_ligne_utilisee += longueur_fragment_utilisee;
		/* Vérification de fin de ligne */
		if (ligne[longueur_ligne_utilisee-1] == '\n'){
			
			if (ligne[0] != '\r' && ligne[0] != '#'){

				printf("(%d) : %s",ligne_courante,ligne);

				char * hexa_operation = malloc(8);
				assembleur_str_to_hexa(ligne, hexa_operation, table, ligne_courante);
				tableauHexa[ligne_utiles] = hexa_operation;
				
				printf("--> %s\n\n",hexa_operation);

				ligne_utiles ++;
			}
			ligne_courante ++;
			ligne[0] = '\0';
		}


	}

	fclose(fichier_txt);
	free(ligne);

	/* -------------------------------------- FIN LECTURE LIGNE PAR LIGNE ----------------------------------*/

	
	int nb_instruction = ligne_courante;
	tableauHexa[ligne_utiles] = '\0'; /* J'ai mis i parce qu'on sait que c'est ce i qui nous fait sortir du while donc c'est la fin*/
	ecriture_fichier("resultat_hexa.txt",tableauHexa,nb_instruction);
	printf("\nEcriture du fichier OK\n");
	exit(EXIT_SUCCESS);
	
	

	return 0;
}

