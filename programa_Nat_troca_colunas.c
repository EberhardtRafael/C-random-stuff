#include<stdio.h>
#include<string.h>


int main(){

char col1[10], col2[10], col3[10], col4[10];
char col5[10], col6[10], col7[10], col8[10];
char col9[10], col10[10]; 
int n = 0, i = 0;

	FILE *arquivo;
	
	arquivo = fopen("ecanceri.fasta.out ", "r");
	
	do{
	
		fscanf(arquivo, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", col1[n], col2[n], col3[n], col4[n], col5[n], col6[n], col7[n], col8[n]);
		n++;
	}while(arquivo != EOF);

	
	for(i = 0; i < n; i++) printf("%s", col7[i]);

return 0;

}
