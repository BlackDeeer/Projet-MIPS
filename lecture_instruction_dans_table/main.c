#include <stdio.h>
#include <string.h>

/* Fonction qui permet de découper un string en tableau d'éléments (séparés par " " et "\n") */
void parseData(char dataTxt [], char * data []){
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


/* TODO #1 : Fonction nombre vers bianaire dans le bon sens et str vers dec aussi*/
void int2bin(int n, char bin[]){
	int i=0;
	while (n>0){
		bin[i] = n%2;
		n/=2;
		i ++;
	}
}


int main()
{
	char instru[] = "BEQ $3 $4 20"; /* Instrction qui sera récupérée dans un fichier*/
	char tableTxt[] = "ADDI 001000 I\nBEQ 000100 I"; /*Table d'instruction à terme dans un fichier */
    
	char *data[10]; /*Tableau qui va contenir les différents éléments de l'instruction : ["ADDI","$1","$2","$3"] */
	
	char *table[100]; /*Tableau qui va contenir toute la table d'instruction séparées par des retours à la ligne */

	int k=0; /* k : index de l'opération de l'instruction trouvé dans la table */
	
	parseData(instru,data); /* Decoupage de l'instruction */
	parseData(tableTxt,table); /* Decoupage de la table d'instruction */
	for (k=0;(strcmp(table[k],data[0])!=0) & (table[k]!=NULL);k+=3); /* Recherche de k */
	
	
	/* affichage des valeurs identifiées */
	printf("C'est une opération %s, son oppcode est : %s et c'est une instruction de type %s\n",data[0],table[k+1],table[k+2]); /* Opération */
	printf("registre de destination : $%d\n",data[1][1]-48); /* Valeur du registre de destination */
	printf("registre sourcce : $%d\n",data[2][1]-48); /* Valeur du registre source */
	printf("valeur immediate : %s\n",data[3]); /* Valeur immediate */

	

	return(0);
}