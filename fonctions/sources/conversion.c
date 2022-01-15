#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int bin_to_int(char* bin, int length){

	int k,x;
	x = 0;
	for (k=0;k<length;k++){
		x += (bin[k]-48)*pow(2,length-k-1);
	}

	return (x);
}


/* fonction de conversion d'un entier vers un binaire / probleme conversion */
void int_to_binary( int x, int length, int binary[] ){
	int i = 0;
	
	if (x<0){
		x = pow(2,length+1) + x;
	}

	for(i=length-1; i >= 0 ;i--)    
	{    
		if( x > 0)
		{
			binary[i] = x%2;    
			x = x/2;
		}
		else
		{
			binary[i] = 0;
		}

	}  
}

/* fonction de conversion d'un nombre binaire vers un nombre hexadecimal*/

void bin_to_hexa(int length, int bin_operation[], char hexa_operation[] )
{	
	int i, j, k, hexa, pow_bin;
	hexa = 0;
	k = 7;
	for(j = length - 1 ; j >= 0; j = j - 4)
	{
		pow_bin = 0;
		/* On sépare en bloc de 4 bits et on calcule la valeur décimale du bloc de 4 bits */
		for( i = j; i > j - 4 && i >= 0 ; i--)
		{
			hexa += bin_operation[i] * pow(2,pow_bin);
			pow_bin ++;
		}
		pow_bin = 0;

		/* On affecte une valeur en hexadécimal en fonction du résultat précédent */
		if ( hexa <= 9)
		{
			hexa_operation[k] = hexa +'0' ;
		}
		else
		{
			switch(hexa)
			{
				case 10:
					hexa_operation[k] = 'A';
					break;
				case 11:
					hexa_operation[k] = 'B';
					break;
				case 12:
					hexa_operation[k] = 'C';
					break;
				case 13:
					hexa_operation[k] = 'D';
					break;
				case 14:
					hexa_operation[k] = 'E';
					break;
				case 15:
					hexa_operation[k] = 'F';
					break;
			}
		}
		hexa = 0;
		k--;
		
	}
	hexa_operation[8] = '\0';
}
<<<<<<< HEAD


void hexa_to_bin(int length, char *hexa, char bin[32], int length_bin)
{
    /* Initialisation des variables */
    int i,j,x = 0;
    /* On traverse chaque élément de hexa*/
    for(i = 0; i <= length; i++ )
    {
        switch(hexa[i])
			{
				case 'A':
					bin[length_bin-1] = '1';
                    bin[length_bin-2] = '0';
                    bin[length_bin-3] = '1';
                    bin[length_bin-4] = '0';
					break;
				case 'B':
					bin[length_bin-1] = '1';
                    bin[length_bin-2] = '0';
                    bin[length_bin-3] = '1';
                    bin[length_bin-4] = '1';
					break;
				case 'C':
					bin[length_bin-1] = '1';
                    bin[length_bin-2] = '1';
                    bin[length_bin-3] = '0';
                    bin[length_bin-4] = '0';
					break;
				case 'D':
					bin[length_bin-1] = '1';
                    bin[length_bin-2] = '1';
                    bin[length_bin-3] = '0';
                    bin[length_bin-4] = '1';
					break;
				case 'E':
					bin[length_bin-1] = '1';
                    bin[length_bin-2] = '1';
                    bin[length_bin-3] = '1';
                    bin[length_bin-4] = '0';
					break;
				case 'F':
					bin[length_bin-1] = '1';
                    bin[length_bin-2] = '1';
                    bin[length_bin-3] = '1';
                    bin[length_bin-4] = '1';
					break;
                /* Si hexa[i] n'est pas égale aux caractères précédents alors c'est un entier que l'on va transformer en binaire */
                default:
                    /* On transforme le caractère en un integer */
                    x = hexa[i] - '0'; 
                    for(j= length_bin - 4 ; j < length_bin ; j++)    
                    {    
                        bin[j] = x % 2 + 48;
                        x = x/2;
                    }   
			}
            length_bin -= 4;

    }


}
=======
>>>>>>> main
