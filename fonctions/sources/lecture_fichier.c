#include <stdio.h>
#include <stdlib.h>
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