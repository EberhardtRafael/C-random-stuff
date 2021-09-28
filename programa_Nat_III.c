/*
_______________________________________________________________________________________________________________________________________
Este programa prodcura em um arquivo por uma determinada string e, em seguida, imprime as strings subsequentes até encontrar uma linha em branco.
Foi criado originalmente para ajudar a doutoranda Nathalia Ramme em sua pesquisa com o fungo .....(como é mesmo o nome?).
Em sua pesquisa, ela precisa contar o número de vezes em que determinaas proteínas ocorrem num arquivo txt, o que se dá sempre após a ocorrênciade uma string contendo "Sequences producing significant alignments:", a qual me permitiu selecionar a parte desejada do arquivo. Após tal string, é padrão haver uma linha em branco e em seguida, serem listadas as linhas desejadas. O programa, portanto, imprime somente o conteúdo destas.

O programa foi escrito de forma pouco eficiente, pois primeiro lê o arquivo inteiro e, em seguida, procura pela ocorrência da string utilizada como referência. Logo, embora funcione, é gambiarra. Temos sorte que o arquivo é pequeno.
_______________________________________________________________________________________________________________________________________
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

# define SAIDA 'n'
# define NLIN 3200
# define NCHAR 100
# define QUANTIDADE_DE_CHAR_PROTEINA 6 //Mudar aqui caso a proteína seja descrita por uma quantidade de caracteres diferente de 6!


/*
_______________________________________________________________________________________________________________________________________
Função que lê todas as linhas do arquivo:
_______________________________________________________________________________________________________________________________________
*/
int getLinhas(FILE *arq, char linha[NLIN][NCHAR]){

int n_linhas_arq = 0;

	//Lendo todas as linhas do arquivo:
	while(!feof(arq)){ //O laço acontece enquanto o arquivo não termina.
		fgets(linha[n_linhas_arq], NCHAR - 1, arq); //Sim, isso funciona - i coresponde à linha da matriz.
		n_linhas_arq++;
	}
	//Usar fgets é melhor que usar fscanf, pois o fgets() lê uma linha inteira e guarda na linha i da matriz.
	
	return n_linhas_arq;
	
}

/*
_______________________________________________________________________________________________________________________________________
Função que abre o arquivo e chama a função de ler as linhas.
_______________________________________________________________________________________________________________________________________
*/

int getFile(char linha[NLIN][NCHAR]){

FILE *arq; //Assim que se declara uma variável arquivo.
char arquivo_nome[50];
int nlinhas;

	puts("__________________________________________________________________________________________");		
	printf("Escreva o nome do arquivo no qual se desejam encontrar as proteinas: ");
	scanf(" %s", arquivo_nome);
	
	arq = fopen(arquivo_nome, "r"); //Abrindo o arquivo. NÃO ESQUECER DE FECHÁ-LO!
	
		if(arq == NULL) printf("\033[22;32mErro ao abrir o arquivo! Pode ter ocorrido erro de digitação!\n");
		
	fflush(arq);
	
	nlinhas = getLinhas(arq, linha);
	
	fflush(arq);
	
	fclose(arq); //Fechando o arquivo.
	
	puts("__________________________________________________________________________________________");		
	printf("No arquivo %s, foram encontrados os segintes registros:\n\n", arquivo_nome);

	return nlinhas;

}
//_______________________________________________________________________________________________________________________________________

int main(){

int i, j, count3, k, l, n_linhas_arq, nlinhas;
int linha_proteinas;
char sair = 's';
char linha_arq[NLIN][NCHAR];
char proteinas[200][NCHAR];
int  contagem_proteinas[50];
int ocorrencia = 0;

	while(sair != SAIDA){
	
	linha_proteinas = 0;
	count3 = 0;
	k = 0;
	l = 0;
	i = 0;	
	
		nlinhas = getFile(linha_arq);
		
		//Passando por tooooodas as linhas da matriz e procurando as linhas desejadas:
		for(j = 0; j < nlinhas; j++){
			
			if(strstr(linha_arq[j], "Query=") != 0){
				
				if(strstr(linha_arq[j], "|") != 0){
					printf("%s", linha_arq[j]); //Este comando imprime a linha inteira contendo a informação sobre a proteína encontrada.
					for(i = 0; i < QUANTIDADE_DE_CHAR_PROTEINA; i++){ //Escreve os nomes das proteínas num vetor.
						proteinas[linha_proteinas][i] = linha_arq[j][i+10]; 				
					} 
					
					linha_proteinas++;	
							
					}
			}
		}
		
		
		for(i = 0; i < linha_proteinas; i++) contagem_proteinas[i] = 0;
		
		//for(i = 0; i < linha_proteinas; i++) printf("%d\n", contagem_proteinas[i]);
		
		//printf("CU\n");
		
		j = 0;
		
		for(i = 0; i < linha_proteinas; i++){
		
		count3 = 0;
		//j = 0; 	
		ocorrencia = 0;
		k = 0;
			
			while(ocorrencia == 0 && j < nlinhas){
			
			//printf("CU\n");
			///printf("%d\n", j);
			
			
				//Verificando a ocorrência do padrão supracitado:
				if(strstr(linha_arq[j], "Sequences producing significant alignments:") != 0){ //strstr verifica se uma string contém uma string.
				
					//printf("HIT\n");	
					k = j+2;
					ocorrencia = 1;
					
					while(strcmp(linha_arq[k], "\n") != 0 && k < nlinhas){ //Verificando se chegou numa linha em branco.
						//printf("K %d\n", k);
						//printf("%s", linha_arq[k]);
						count3++;
						//printf("Contagem %d\n", count3);
						k++;						
					}
					//printf("Termina o while\n");	

				j = j + count3 + 1;
				
				}else if(strstr(linha_arq[j], "No hits found") != 0) i++;
								
				j++;			
			}
			
			
			contagem_proteinas[i] = count3;
			//printf("%s\n", proteinas[i]);				
			//printf("Linha %d, contagem %d\n", i, count3);							
		} 
		
		
	
		puts("__________________________________________________________________________________________");
		
		printf("\n");
		for(i = 0; i < linha_proteinas; i++) printf("%s\t", proteinas[i]);
		printf("\n");
		for(i = 0; i < linha_proteinas; i++) printf("%d\t", contagem_proteinas[i]);
		printf("\n");		
					
	}
	

return 0;

}
