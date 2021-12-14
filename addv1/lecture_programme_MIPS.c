#include <stdio.h>
#include <stdlib.h>

int main( int argc, char * argv[])
{
	char T[200] ;
	int i=0;
	int j=0;
	FILE * donnees;

	/*Ouverture en lecture*/
	printf("nomFichier = %s\n", argv[1]);
	donnees = fopen(argv[1] , "r");		

	/*Gestion d'erreurs à l'ouverture*/
	if (donnees == NULL)  {
		perror("Probleme lors de l'ouverture du fichier pour la lecture\n");
		exit(EXIT_FAILURE);
	}
	
	/*Lecture jusqu'à la fin du fichier*/
	while(!feof(donnees)) {
		fscanf(donnees, "%c", &T[i]);
		i++;
	}

	/*Fermeture*/
	fclose(donnees);
	for(j=0; j <= 200; j++)
	{
		printf("%c ",T[j]);
	}
	
	return(0);
	/*return (i-1); */
	/*i-1 car feof devient vrai qu'une fois qu'on a essayé de lire au-delà de la fin du fichier*/
	
	
	
}
