#include <stdio.h>
#include <string.h>

/*
int main(){

	char instru[]  = "ADDI $2 $3 200";
	
	char *operation;
	
	operation = strcpy(operation, instru);
	
	operation = strtok(operation, " ");
	
	printf("%s\n", operation);
	operation = strtok(NULL, " ");
	printf("%s\n", operation);
	
	char table[] = "ADDI 001000 I";
	
	return 0;
}
*/


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

void int2bin(int n, char bin[]){
	int i=0;
	while (n/2>1){
		bin[i] = n%2;
		n/=2;
		i ++;
		printf("%d",n%d);
	}
}

int main()
{
	char instru[] = "ADDI $2 $3 200";
	char tableTxt[] = "ADDI 001000 I\nBEQ 000100 I";
    
	char *data[10];
	parseData(instru,data);
	
	char *table[100];
	parseData(tableTxt,table);
	
	int k=0;
	for (k=0;(strcmp(table[k],data[0])!=0) & (table[k]!=NULL);k+=3);
	
	/*
	if (table[k+2]=="I"){
		bin = 
	}*/
	
	printf("%d",k);
	
	char bin [100];
	int2bin(15,bin);
	printf("%s",bin);
	

	return(0);
}