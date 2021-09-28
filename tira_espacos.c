/*
Este programa recebe uma string qualquer e a devolve sem espa�os, al�m de contar o n�mero de voigais nela presente.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 60

int main(){

char entrada[MAX + 1], saida[MAX + 1] ;
int i, j = 0, vogais = 0;

    puts("Escreva uma frase com, no m�ximo 60 caracteres:");
    gets(entrada); //Quero usar scanf em vez de gets, s� pra diversificar.

    for(i = 0; i < strlen(entrada); i++){
        if(entrada[i] == ' '){
            saida[j] = entrada[i+1];
            i++;
        }
        else saida[j] = entrada[i];
    j++;
    }

    printf("String sem espacos:\n");
    for(i = 0; i < j; i++) printf("%c", saida[i]); //Estou prointando assim pra limpar pra baixo do tapete o lixo gerado no final da string saida[].

    for(i = 0; i < strlen(entrada); i++) entrada[i] = tolower(entrada[i]); //Para que o if em seguida fique menor.
    printf("\n");

    for(i = 0; i < strlen(entrada); i++){
        if(entrada[i] == 'a'||entrada[i] == 'e'||entrada[i] == 'i'||entrada[i] == 'o'||entrada[i] == 'u') vogais++; //Verificando o n�mero de vogais.
    }

    printf("\nO numero de vogais na string entrada eh: %d.", vogais);
    //printf("%s, %ld", saida, strlen(entrada)); //Assim, sobra lixo no final de saida[].
    //puts(saida);

return 0;

}
