/*
Este programa recebe do usuário números reais positivos e calcula a média entre eles, mostrando o número de valores acima e abaixo da média.  
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 15

int main(){

float entradas[MAX];
float entrada, somatorio, media;
int i = 0, j;
int acima_media, abaixo_media;

somatorio = 0;
media = 0;
acima_media = 0;
abaixo_media = 0;

	printf("Entre com números positivos (para interromper a coleta, digite qualquer numero negativo):\n");

	do{
		scanf(" %f", &entrada);
		if(entrada > 0){
			entradas[i] = entrada;
			i++;
		} 
		//Coloco o if, mesmo com essa condição sendo testada no loop porque, caso a entrada seja não positiva, não quero 			  armazená-la no vetor.			
		else if(entrada < 0) printf("Coleta interrompida.\n");
		else printf("Entrada invalida!"); //Caso entre com zero.
		
		/*
		Não gosto de omitir as chaves, mesmo quando posso, mas o fiz para mostrar que conheço a possibilidade.
		*/			
		
		}while(entrada >= 0 && i < MAX); //Tem que rodar enquanto AMBAS as condições forem verdadeiras. E outras palavras, se uma OU 							   outra for falsa, o loop termina.

	//Loop para calcular a média. Poderia tê-lo feito ao longo da coleta de dados, mas, o enunciado dava a entender para fazer em momentos 		  diferentes.
	for(j = 0; j < i; j++) somatorio += entradas[j];
			
	media = somatorio/(i); //Poderia fazer o cálculo direto no print, também.
	
	//Loop para encontrar o número de valores acima e abaixo da média.
	for(j = 0; j < i; j++){
		if(entradas[j] > media) acima_media++;
		else if(entradas[j] < media) abaixo_media++; //uso else if porque não quero contabilizar números iguais à média.	
	}
	
	printf("A media entre os valores entrados eh: %f\nO número de entreadas acima da media eh: %d\nO número de entreadas acima da media eh: %d\n", media, acima_media, abaixo_media);
	
	
return 0;

}

