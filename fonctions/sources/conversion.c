#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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
