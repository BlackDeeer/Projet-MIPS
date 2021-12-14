#include <stdio.h>

void int_to_binary( int x, int lengh, int binary[] ){
	
	int i = 0;
	
	for(i=0; i < lengh ;i++)    
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


void add_to_T( rd_bi, T, int lengh, 16, 20 );
{
	for 
	
}


int main(){
	
	char instru[100] ="ADD $7,$5,$2";
	int T[31];
	int rs,rt, rd;
	int rs_bi[5], rt_bi[5], rd_bi[5];
	int registre ,i;
	i = registre = 0;
	
	/* opcode */
	for( i = 0; i <= 5; i++ )
	{
		T[i] = 0;
	}
	
	/* sa */
	
	for( i = 21; i <= 25; i++ )
	{
		T[i] = 0;
	}
	
	/* function */
	T[26] = 1;
	for( i = 27; i <= 31; i++ )
	{
		T[i] = 0;
	}
	
	i = 0;
	while( (registre < 2) || (instru[i] != '\0') )
	{
		if( instru[i] == '$')
		{
			if( registre == 0){
				rd = instru[i+1] - '0'; 
				registre++;
			}
			else if( registre == 1){
				rs = instru[i+1] - '0'; 
				registre++;
			}
			else if( registre == 2){
				rt = instru[i+1] - '0'; 
			}
		}
		i ++;
	}

	printf("\n rd:%d,rs:%d,rt:%d \n",rd, rs, rt);
	
	int_to_binary( rd , 5 , rd_bi);
	int_to_binary( rs , 5 , rs_bi);
	int_to_binary( rt , 5 , rt_bi);
	
	
	add_to_T( rd_bi, 5, 16, 20 );
	
	
	
	return(0);
}