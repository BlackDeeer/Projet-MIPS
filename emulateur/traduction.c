#include <stdio.h>
#include <string.h>
#include "../fonctions/header/fichier.h"
#include "../fonctions/header/conversion.h"

#define TAILLE_TABLE 175 /* Taille de la table d'instructions */


/* -------------------------------- Fonction qui permet de découper un string en tableau d'éléments -------------------------- */

void decoupage_data(char * dataTxt, char * data [], char * separateurs){
	char *elements;
	int i = 0;
	/*On cherche à récupérer, un à un, tous les mots de notre fichier texte compris entre les séparateurs et on commence par le premier.*/
	elements = strtok(dataTxt,separateurs);
	while(elements)
	{
		/* On stocke l'élément dans un tableau et on passe à l'élément suivant */
		data[i] = elements; 
		elements = strtok(NULL, separateurs);
		i++;
	}

}


/* ------------------------------------------------------ FONCTION TXT VERS HEXA --------------------------------------------- */

void assembleur_str_to_hexa(char * assembleur_string, char hexa_operation[],char *table[], int ligne_courante){

	/* --- DECLARATION */

	char *data[4]; /*Tableau qui va contenir les différents éléments de l'instruction : ["ADD","$1","$2","$3"] */
	
	int k=0; /* Index de l'instruction correspondante trouvée dans la table */

	char * instruction; /* Contient l'instruction "ADD" par exemple */

	char * opcode; /* Contient l'opcode correspondant à l'instruction dans la table (pour ADD : 100000)  */
	char type_instruction; /* Contient le type d'instruction correspondant (pour ADD : R) */

	int bin_operation[32]; /* Opération résultante en binaire */


	int i = 0; /* compteur qui avance dans les opérandes prévues dans la table (pour ADD : r2, r3, r1, puis 0*/
	int j = 0; /* compteur qui va avancer dans les opérandes de l'instruction (ici : $1, $2 puis $3) */
	

	char * separateurs; /* Contient les séparateurs nécessaires pour le prochain découpage de données */




	/* --- INITIALISATION */

	separateurs = " ,\r\n\t"; /* Séparateurs necessaires pour le découpage de l'instruction */
	decoupage_data(assembleur_string,data,separateurs); /* découpage d'une ligne d'assembleur en tableau d'éléments : data */

	/* data[k] :
		k == 0 <=> instruction (ici ADD)
		k == 1 <=> première opérande (ici $1)
		etc.
	*/

	instruction = data[0]; /* On recupere l'instruction dans data  */

	for (k=0 ; (k<=TAILLE_TABLE) && (strcmp(table[k],instruction)!=0); k+=7); /* Recherche de la ligne correspondant à l'opération */
	/* On avance de 7 pour accéder au mot clé (correspondant à une instruction) suivant */ 

	/* Si la recherche s'est arrêtée parce que k a dépassé la taille de la table alors l'instruction n'est pas reconnue : on le signale et quitte le programme */
	if (k>TAILLE_TABLE){
		fprintf(stderr,"ERREUR : L'instruction à la ligne %d n'est pas reconnue\n",ligne_courante);
		exit(EXIT_FAILURE); 
	}

	/* On récupere dans la table des instructions les valeurs suivantes : */
	opcode = table[k+1];
	type_instruction = table[k+2][0];
	
	


	/* --- EXECUTION en fonction du type d'instruction */

	if (type_instruction == 'I'){ /* INSTR $rd, $rs, imm*/

		int *bin_op[3]; /* 3 "opérandes" modifiable dans l'opération finale binaire (5 bits, 5 bits, 16 bits, on alouera leur taille après)*/
		int op[3]; /* les même "opérandes" en décimal */
		char * split; /* pour le cas de sw et lw qui ont un format différent nécésittant un split entre base et offset : "offset(base)" */


		for (i=0;i<3;i++){ /* on va remplir chaque "opérande" nécessaire pour l'opération finale */
			int * bin_op_temp = NULL; /* Pointeur sans mémoire alouée qui va contenir le binaire avant de la placer dans le tableau bin_op */
			int bin_taille; /* Contiendra la taille en bits necessaire pour le type d'opérande voulue */

			switch(table[k+3+i][0]){ /* On lit 'r', 'r' puis "i" */

				case ('r') : 

					/* 
					On va utiliser une opérande de l'instruction. (++j)
					Pour les r, on lit le chiffre suivant (1,2,3) qui nous précisera la place de l'opérande correspondante dans l'instruction
					On détecte les erreurs : si c'est pas un registre ("$" absent) ou nombre trop grand pour 5 bits.
					On défini la taille du binaire necessaire sur 5 bits.
					*/

					++j;

					if (data[table[k+3+i][1]-48][0]!='$'){
						fprintf(stderr,"ERREUR : A la ligne %d, l'opérande n°%d doit être un registre ...\n",ligne_courante,table[k+3+i][1]-48);
						exit(EXIT_FAILURE);
					} else if (atoi(data[table[k+3+i][1]-48]+1)>63 || atoi(data[table[k+3+i][1]-48]+1)<0 ) {
						fprintf(stderr,"ERREUR : A la ligne %d, le registre %d doit être compris entre 0 et 31 ...\n",ligne_courante,table[k+3+i][1]-48);
						exit(EXIT_FAILURE);
					}


					op[i] = atoi(data[table[k+3+i][1]-48]+1);
					bin_taille = 5;
					
					break;


				case ('i') : 

					/*
					On va utiliser une opérande. (++j)
					Pour les i, le j correspondra à la dernière opérande qui est toujours la valeur immediate (ou offset, etc.).
					On détecte les erreurs : utilisation d'un registre ("$") ou nombre trop petit ou trop grand pour un binaire signé de 16 bits. 
					On défini la taille du binaire necessaire sur 16 bits. 
					*/

					++j;

					if (data[j][0]=='$'){
						fprintf(stderr,"ERREUR : A la ligne %d, l'opérande n°%d doit être une valeur\n",ligne_courante,j);
						exit(EXIT_FAILURE);
					} else if (atoi(data[j])>65535 || atoi(data[j])<-65536 ) {
						fprintf(stderr,"ERREUR : A la ligne %d, la valeur immédiate doit être comprise entre -65536 et 65535\n",ligne_courante);
						exit(EXIT_FAILURE);
					}

					op[i] = atoi(data[j]); 
					bin_taille = 16;

					break;


				case ('0') :

					/* va remplir de 0 un binaire de 5 bits
					l'absence du ++j; implique qu'on n'avance pas dans les opérandes de l'instruction mais bien dans les "opérandes" 
					dans la ligne de la table correspondant à l'instruction.
					*/

					op[i] = 0;
					bin_taille = 5;

					break; 

				case ('b') :
					
					/*
					Pour les b, on découpe le "offset(base)" on a alors data[2] qui garde que l'offset et split qui garde la base
					Pas de gestion d'erreur pour l'instant ... il faudra faire attention avec les sw et lw
					La base est codée sur 5 bit.
					*/

					split = strtok(data[2],"()");
					split = strtok(NULL,"()");

					if (split[0]!='$'){
						fprintf(stderr,"ERREUR : A la ligne %d, la base doit être un registre ...\n",ligne_courante);
						exit(EXIT_FAILURE);
					} else if (atoi(split+1)>63 || atoi(split+1)<0 ) {
						fprintf(stderr,"ERREUR : A la ligne %d, la base doit être compris entre 0 et 63 ...\n",ligne_courante);
						exit(EXIT_FAILURE);
					}

					op[i] = atoi(split+1);
					bin_taille = 5;

					break;


				case ('o') :

					/* 
					Récupère la première partie de "offset(base)" : l'offset (codé sur 5 bit)
					Pas de gestion d'erreur également
					*/

					if (data[2][0]=='$'){
						fprintf(stderr,"ERREUR : A la ligne %d, l'offset doit être une valeur\n",ligne_courante);
						exit(EXIT_FAILURE);
					} else if (atoi(data[2])>32767 || atoi(data[2])<-32768 ) {
						fprintf(stderr,"ERREUR : A la ligne %d, l'offset doit être comprise entre -32768 et 32767\n",ligne_courante);
						exit(EXIT_FAILURE);
					}

					op[i] = atoi(data[2]);
					bin_taille = 16;

					break;
			} 
			
			/* On alloue dynamiquement la mémoire necessaire en fonction du type d'opérande */
			bin_op_temp = (int *) malloc(bin_taille * sizeof(int));
			int_to_binary(op[i],bin_taille,bin_op_temp); /* on transforme le nombre décimal en binaire */
			bin_op[i] = bin_op_temp; /* on le sauvegarde dans le tableau des "opérandes" binaires pour l'opération finale */

		}

		
		/* CONCATENATION */
		
	    for(i=0;i<32;i++) {
			if (i<6){
				bin_operation[i] = opcode[i]-48; /* opcode sur 6 bits */
			}
			else if (i<11){
				bin_operation[i] = bin_op[0][i-6]; /* rd sur 5 bits */
			}
			else if (i<16){
				bin_operation[i] = bin_op[1][i-11]; /* rs sur 5 bits */
			}
			else {
				bin_operation[i] = bin_op[2][i-16]; /* imm sur 16 bits */ 
			}	

		}

	}


	else if (type_instruction == 'R'){ /* OPE $rd, $rs1, $rs2*/

		char special[] = "000000"; /* 6 bits qui restent identique pour toutes les instructions dans l'opération finale ... */
		int *bin_op[4]; /* 4 "opérandes" modifiable dans l'opération finale binaire (4 fois 5 bits) */
		int op[4]; /* Les mêmes "opérandes" en décimal */

		/* --- Même fonctionnement avec 4 itération pour les 4 fois 5 bits à remplir */
		
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
					++j;
					break;
				case ('i') : 
					++j;
					if (data[j][0]=='$'){
						fprintf(stderr,"ERREUR : A la ligne %d, l'opérande n°%d doit être une valeur\n",ligne_courante,j);
						exit(EXIT_FAILURE);
					} else if (atoi(data[j])>31 || atoi(data[j])<0 ) {
						fprintf(stderr,"ERREUR : A la ligne %d, la valeur immédiate doit être comprise entre 0 et 31\n",ligne_courante);
						exit(EXIT_FAILURE);
					}
					op[i] = atoi(data[j]); 
					bin_taille = 5;
					break;
				case ('0') :
				
					op[i] = 0; 
					bin_taille = 5;
					break; 
				case ('1') :
					op[i] = 1; 
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
		}
	}


	else if (type_instruction == 'J'){ /* OPE instr_index*/

		/* Une seule opérande à traiter on alloue directement la mémoire pour 26 bits et on transforme instr_index en binaire */
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
		}


	}


	/* --- ENFIN, on traduit le résultat binaire en hexadécimal */
	bin_to_hexa(32,bin_operation,hexa_operation);

}


char** traduction(char* fichier, char* destHexa)
{

	/* --- DECLARATION */

	char tableTxt[10000]; /* Table d'instruction en chaine de caractères */
	char *table[TAILLE_TABLE]; /* Tableau qui va contenir toute la table d'instruction découpée */


	char * separateurs_data; /* Contiendra les séparateurs nécessaire au découpége de données */
	

	char **tableauHexa; /* Contient les ligne d'instructions en hexa (limité à 200, peut être une allocation dynamique pour plus tard) */ 
    char **tableauHexa_temp;
    char nbHexa;
	int ligne_courante = 1; /* Compte les lignes du fichier assembleur txt */
	int ligne_utiles = 0; /* Compte les vraies lignes utiles d'assembleur */

	char fragment[4]; /* fragments de ligne qu'on va prendre dans le fichier */
	size_t longueur_fragment; /* type size_t = entiers naturels = pas de nombre négatif ! */
	char * ligne; /* Contiendra la ligne complète à terme */


	char * hexa_operation; /* Opération finale en hexa */

	FILE * fichier_txt; /* Contiendra le fichier assembleur */

	char * ligneMod;
	char *elementsLignes[100];


	/* Lecture de la table d'instruction */
	lecture_fichier("table_instructions.txt",tableTxt); /* Stocke la table d'instruction en chaine de caractères */

	separateurs_data = " ,\n\t\r"; /* On défini les séparateurs nécessaires à la découpe */
	decoupage_data(tableTxt,table,separateurs_data); /* Decoupage de la table d'instruction qui ira dans table */
	
	



	/* -------------------------------------- DEBUT LECTURE LIGNE PAR LIGNE ---------------------------------*/

	fichier_txt = fopen(fichier,"r"); /* Ouverture du fichier assembleur */

	if (fichier_txt == NULL){
		fprintf(stderr,"Impossible d'ouvrir le fichier : '%s'\n",fichier);
		exit(EXIT_FAILURE);
	}

	/* On va stocker les fragments dans un tampon de ligne */
	longueur_fragment = sizeof(fragment); /* au début 4 du coup */
	ligne = malloc(longueur_fragment); /* On alloue la mémoire correspondant à ce fragment */

	if (ligne == NULL){ /* Détéction d'erreur d'allocation mémoire */
		perror("Impossible d'allouer de la mémoire au tampon de la ligne");
		free(ligne);
		exit(EXIT_FAILURE);
	}

	/* On vide la chaine de caractere : ligne = "" */
	ligne[0] = '\0';
    nbHexa = 0;

	/* Tant qu'il existe des fragments à prendre dans le fichier : */
	while(fgets(fragment, sizeof(fragment), fichier_txt) != NULL){

		size_t longueur_ligne_utilisee = strlen(ligne); /* au debut : 0 */
		size_t longueur_fragment_utilisee = strlen(fragment); /* au debut : 4 */

		if (longueur_fragment-longueur_ligne_utilisee<longueur_fragment_utilisee) {
			longueur_fragment *= 2; /* 4*2 = 8 par exemple */
			ligne = realloc(ligne, longueur_fragment); /* On alloue la mémoire correspondante */

			if (ligne == NULL){ /* Détection d'erreur d'allocation mémoire */
				perror("Impossible d'allouer plus de  mémoire au tampon de ligne");
				free(ligne);
				exit(EXIT_FAILURE);
			}
		}

		/* On copie à la suite de la ligne la nouvelle partie du fragment */
		strncpy(ligne + longueur_ligne_utilisee, fragment, longueur_fragment-longueur_ligne_utilisee);

		/* La longueur de la ligne est alors augmentée de celle du fragment */
		longueur_ligne_utilisee += longueur_fragment_utilisee;

		/* Vérification de fin de ligne */
		if (ligne[longueur_ligne_utilisee-1] == '\n'){ /* En cas de fin de ligne, on la traite directement */

			ligneMod = (char *) malloc(longueur_ligne_utilisee);
			strcpy(ligneMod,ligne);
			decoupage_data(ligneMod,elementsLignes,"\t\0 ");
			
			if (ligne[0] != '\r' && ligne[0] != '\n'  && ligne[0] != '#' && elementsLignes[0][0]!='#'){ /* si ce n'est pas un retour à la ligne, ou un commentaire seul */

				

				printf("(%d) : %s",ligne_courante,ligne); /* affichage */

				hexa_operation = malloc(8); /* Allocation de la mémoire pour l'opération finale en hexa */
				assembleur_str_to_hexa(ligne, hexa_operation, table, ligne_courante); /* conversion de la ligne d'assembleur en hexa */

                nbHexa++;
                tableauHexa = realloc(tableauHexa, (nbHexa+1)*8);
                tableauHexa_temp = tableauHexa;
                tableauHexa_temp+=nbHexa-1;
                *tableauHexa_temp = malloc(8);

				strcpy(*tableauHexa_temp,hexa_operation);  /* Ajout à la table des lignes d'instruction en hexa*/
				
				printf("--> %s\n\n",hexa_operation); /* affichage */

				ligne_utiles ++; /* on compte un ligne utile */
			}
			ligne_courante ++; /* on compte une ligne */


			ligne[0] = '\0'; /* On "vide" la ligne */
		}


	}

	fclose(fichier_txt);


	if (ligne[0] != '\0'){
		ligneMod = (char *) malloc(sizeof(ligne));
		strcpy(ligneMod,ligne);
		decoupage_data(ligneMod,elementsLignes,"\t\0 ");
		
		/* Pour la potentielle dernière ligne (en attendant de trouver un truc plus propre) */
		if (ligne[0] != '\r' && ligne[0] != '\n' && ligne[0] != '#'  && elementsLignes[0][0]!='#' && elementsLignes[0]!=NULL){ /* si ce n'est pas un retour à la ligne, ou un commentaire seul */

			
			printf("(%d) : %s\n",ligne_courante,ligne); /* affichage */

			hexa_operation = malloc(8); /* Allocation de la mémoire pour l'opération finale en hexa */
			assembleur_str_to_hexa(ligne, hexa_operation, table, ligne_courante); /* conversion de la ligne d'assembleur en hexa */
			
            nbHexa++;
            tableauHexa = realloc(tableauHexa, (nbHexa)*8);
            tableauHexa_temp = tableauHexa;
            tableauHexa_temp+=nbHexa-1;
            *tableauHexa_temp = malloc(8);
            

            strcpy(*tableauHexa_temp,hexa_operation); /* Ajout à la table des lignes d'instruction en hexa*/
			
			printf("--> %s\n\n",hexa_operation); /* affichage */

			ligne_utiles ++; /* on compte un ligne utile */
		}
		ligne_courante ++; /* on compte une ligne */


		ligne[0] = '\0'; /* On "vide" la ligne */
	}

	free(ligne);

	/* -------------------------------------- FIN LECTURE LIGNE PAR LIGNE ----------------------------------*/

	
	nbHexa++;
    tableauHexa = realloc(tableauHexa, (nbHexa)*8);
    tableauHexa_temp = tableauHexa;
    tableauHexa_temp+=nbHexa-1;
    *tableauHexa_temp = malloc(8);

    strcpy(*tableauHexa_temp,"\0");  /* Ajout à la table des lignes d'instruction en hexa*/

	/* Ecriture dans le fichier destination */


	if (destHexa!=NULL){
		ecriture_fichier(destHexa,tableauHexa,ligne_utiles);
		printf("Ecriture dans '%s' OK\n",destHexa);
	} else {
		char resultat[] = "hexa/hexa_";
		strcat(resultat,fichier+6);
		ecriture_fichier(resultat,tableauHexa,ligne_utiles);
		printf("Ecriture dans '%s' OK\n",resultat);
	}

    

    return tableauHexa;
	
}