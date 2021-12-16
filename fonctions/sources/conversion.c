#include <stdio.h>
#include <stdlib.h>


/* fonction de conversion d'un entier vers un binaire / probleme conversion */
void int_to_binary( int x, int lengh, int binary[] ){
	
	int i = 0;
	
	for(i=lengh-1; i >= 0 ;i--)    
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

/* TODO #2 Conversion bin vers hexa*/


