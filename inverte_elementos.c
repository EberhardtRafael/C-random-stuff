/*
Este programa recebe do usuário números positivos e negativos em qualquer ordem os armazena num vetor e, em seguida, imprime o vetor de entrada junto a um vtor contendo as entradas positivas e negativas em posições invertidas, respeitando a ordem de entrada. (Caso pareça confuso roda o programa pra ver um exemplo.)
(Estou programando com muito sono, então, pode ser que o código não seja o mais eficiente do mundo. Mas é um programa simples, de qualquer forma, então, não tem problema.)
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 8 //Posso definir a quantidade de entradas aqui sem precisar mexer em mais nada ao longo do programa (sempre deve ser par).

int main(){

int entrada, resultado[MAX], entradas[MAX]; //As entradas poderiam ser reais, mas que sejam inteira só pela estética na impressão.
int positivos[MAX/2], negativos[MAX/2]; //Declarei em duas linhas só pra não ficar feio.
int quantidade_mais = 0, quantidade_menos = 0;
int i = 0, k = 0, l = 0;

//Eu prefiro declarar a variável antes e inicializar depois, mas o fiz concomitantemente para mostrar que tconheço a possibilidade.

	printf("Entre com %d números positivos e %d números negativos, em qualquer ordem:\n", MAX/2, MAX/2);
		
		//Enquanto um vetor com somente as entradas positivas e outro com somente as entradas negativas não forem preenchidos, o loop 			continuará rodando.
		while(quantidade_mais < MAX/2 || quantidade_menos < MAX/2){
			scanf(" %d", &entrada);		
			if(entrada > 0 && quantidade_mais < MAX/2){ //Se usar <=, o programa vai receber uma entrada a mais!
				positivos[quantidade_mais] = entrada; //Criando um vetor auxiliar com somente positivos.
				entradas[i] = entrada; 
				quantidade_mais++; //A posição ao longo do vetor auxiliar só deve ser incrementada caso a entrada corresponda. 
				i++; 
			}else if(entrada < 0 && quantidade_menos < MAX/2){
				negativos[quantidade_menos] = entrada;//Criando um vetor auxiliar com somente negativos.
				entradas[i] = entrada; //O vetor entradas não deve filtrar a informação recebida, então, sempre a guarda.
				quantidade_menos++;
				i++;	//Não importando o qu eaconteça, a posição ao longo das entradas deve ser incrementada.
				}else printf("Entrada inválida.\n"); //Caso entre com zero ou com mais de MAX/2 entradas com mesmo 										sinal, nenhum vetor é incrementado.		
		}	
		
					
		/*
		Loop para preencher o vetor com as posições entre os números positivos e negativos trocadas.
		Percorrendo todo o vetor entradas[], verifico se o sinal da antrada é positivo, caso o seja, preencho o resultado[] com um 			elemento de negativos[], caso contrário, o preencho com um elemento de positivos[]. Assim, garanto que a ordem de entrada seja 			respeitada.
		*/
		for(i = 0; i < MAX; i++){ //Independente do sinal da entrada, a posição ao longo de resultado[] deve ser incrementada.
			if(entradas[i] > 0){  
				resultado[i] = negativos[k];
				k++;
			}else{
				resultado[i] = positivos[l];
				l++;			
			} 
		
		}
		
		//Printando o resultado na tela de forma organizada.
		printf("Entradas:\n");
		for(i = 0; i < MAX; i++) printf("%d\t", entradas[i]);
		printf("\n");
		printf("Apos inversao:\n");
		for(i = 0; i < MAX; i++) printf("%d\t", resultado[i]);
		printf("\n");


return 0;

}

