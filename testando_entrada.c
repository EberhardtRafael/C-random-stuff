#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void checaEntrada1(){

char entrada;

do{
    
    printf("Escreve uma merda de número aí (entre 1 e 4):\n");
    scanf(" %c", &entrada);
    if((int)entrada < 48 || (int)entrada > 57) printf("Escreve direito, SEU MERDA!\n\n");
    else if((int)entrada < 49 || (int)entrada > 52) printf("Número de jogadores inválido.\n\n");
    else printf("Muito bem, você sabe ler.\n\n");
    //printf("%d\n", (int)entrada);


}while((int)entrada < 49 || (int)entrada > 52);

}

void checaEntrada2(){

char entrada[6];

do{
    
    printf("Escreve uma merda de número aí (entre 1 e 4):\n");
    scanf(" %s", entrada);
    if(strcmp(entrada, "1") > 10 || strcmp(entrada, "1") < 0) printf("Escreve direito, SEU MERDA!\n\n");
    else if(strcmp(entrada, "1") > 3) printf("Número de jogadores inválido.\n\n");
    else printf("Muito bem, você sabe ler.\n\n");
    

}while(strcmp(entrada, "1") < 0 || strcmp(entrada, "1") > 3);

}

int main(){

checaEntrada2();


return 0;

}
