#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Fonction permettant de mettre un fichier dans un string : */

void lecture_fichier(char * nom_du_fichier, char * data){
	int i=0;
	FILE * donnees;

	/*Ouverture en lecture*/
	donnees = fopen(nom_du_fichier, "r");		

	/*Gestion d'erreurs a l'ouverture*/
	if (donnees == NULL)  {
		perror("Probleme lors de l'ouverture du fichier pour la lecture\n");
		exit(EXIT_FAILURE);
	}
	
	/*Lecture jusqu'a la fin du fichier*/
	while(!feof(donnees)) {
		fscanf(donnees, "%c", &data[i]); 
		i++;
	}

	/*Fermeture*/
	fclose(donnees);
}

void ecriture_fichier(char nomFichier[], char *tableauHexa[], int taille) {
	int i = 0;
	FILE * resultats; 
	
	/*Ouverture en écriture*/
	resultats = fopen( nomFichier, "w");

	/*Gestion d'erreurs à l'ouverture*/
	if (resultats == NULL)  {
		perror("Probleme lors de l'ouverture du fichier pour l'écriture\n");
		exit(EXIT_FAILURE);
	}

	/*Ecriture du tableau dans le fichier*/
	while (tableauHexa[i] != NULL) 
	{
		fprintf(resultats, "%s\n", tableauHexa[i]);
		i++;
	}

	/*Fermeture*/
	fclose(resultats);
}


void lecture_fichier_ligne_par_ligne(char * fichier){

	FILE * fichier_txt = fopen(fichier,"r");

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
			printf("%s",ligne);
			ligne[0] = '\0';
		}


	}

	fclose(fichier_txt);
	free(ligne);

}