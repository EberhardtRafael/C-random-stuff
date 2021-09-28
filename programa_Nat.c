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
# define NLIN 2000
# define NCHAR 100

//Variáveis globais.
//int n_linhas_arq;
//char linha[NLIN][NCHAR];//Criando uma matriz de strings, posso armazenar na memória o conteúdo de cada linha do arquivo. O tamanho está demasiado de propósito. Na verdade, com i = 1000, não houve espaço o suficiente pra um dos arquivos.

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
	
	fclose(arq); //Fechando o arquivo.
	
	puts("__________________________________________________________________________________________");		
	//printf("No arquivo %s, foram encontrados os segintes registros:\n\n", arquivo_nome);

	return nlinhas;

}
//_______________________________________________________________________________________________________________________________________

int main(){

int i, j, count1, count2, count3, k, l, n_linhas_arq, nlinhas, n_barras;
int linha_proteinas;
char sair = 's';
char linha[NLIN][NCHAR];
char proteinas[200][NCHAR];
int  contagem_proteinas[50];

	while(sair != SAIDA){
	
	linha_proteinas = 0;
	count1 = 0;
	count2 = 0;
	count3 = 0;
	k = 0;
	l = 0;
	i = 0;	
		nlinhas = getFile(linha);
		
		//printf("Linha do\t\t Registro:\narquivo:\n");
	
		//Passando por tooooodas as linhas da matriz e procurando as linhas desejadas:
		for(j = 0; j < nlinhas; j++){
			
			if(strstr(linha[j], "Query=") != 0){
			
				//n_barras = 0;				
				
				if(strstr(linha[j], "|") != 0){
					//printf("\n");	
					//printf("%d\t\t", j);				
					//for(i = 10; i < 16; i++) printf("%c", linha[j][i]);
					for(i = 0; i < 6; i++){
						proteinas[linha_proteinas][i] = linha[j][i+10]; //Trocar os nomes das variáveis para coisas que fazem sentido!!! To perdendo o controle, já.				
						} 
					//printf("\n");	
					linha_proteinas++;			
					}
				
//Abaixo eu tentei implementar uma forma mais independente de se printar apenas o nome da proteína presente na linha onde aparece algo do tipo "Query= tr|Q7S8S2|[...]", mas isso gerou problemas no armazenamento de memória os quais ainda não parei pra resolver. Em vez disso, acima eu fiz o programa imprimir os seis caracteres correspondentes ao nome da proteína que, POR SORTE, sempre tem o mesmo tamanho. Mas isso é gambiarra. Vai funcionar por ora. Preciso mudar isso!!!!
				
				/*if(strstr(linha[j], "|") != 0){
					/*printf("\n");					
					while(n_barras < 2){
						if(linha[j][i] == '|'){
							n_barras++;
							i++;
							} 								
						if(n_barras == 1){
							printf("%c", linha[j][i] );						
							} 
							i++;
						}
						printf("\n");
				}*/		
			}
			
			count3 = 0;
			
			//Verificando a ocorrência do padrão supracitado:
			if(strstr(linha[j], "Sequences producing significant alignments:") != 0){ //strstr verifica se uma string contém uma string.
				k = j+2;
				count1++;				
				//printf("\n"); //Senão fica tudo junto.
				while(strcmp(linha[k], "\n") != 0 && k < nlinhas){ //Verificando se chegou numa linha em branco.
					//printf("%d\t%s", k, linha[k]);
					k++;
					count2++;
					count3++;	
				}
				//Se tentar usar linha[k] == "\n", não funciona.
				contagem_proteinas[linha_proteinas] = count3;			
			}		
		}
	
		/*if (k == 0){
			puts("\n  --- \t\t\tMeh... nenhum :(");
		}else{ 
			puts("__________________________________________________________________________________________");
			printf("\nAo todo, houve %d ocorrências, com %d registros.\n", count1, count2);
		}*/
		puts("__________________________________________________________________________________________");
		
		printf("\n");
		for(i = 0; i < linha_proteinas; i++) printf("%s\t", proteinas[i]);
		printf("\n");
		for(i = 0; i < linha_proteinas; i++) printf("%d\t", contagem_proteinas[i]);
		printf("\n");
		
		
		puts("__________________________________________________________________________________________");
		
		
		puts("\033[22;32mDeseja buscar em outro arquivo? [s]/[n]:");
		scanf(" %c", &sair);
		sair = tolower(sair);
		puts("\x1b[0m");
			if(sair == 's') printf("\n\n\n");	
			
	}
	

return 0;

}
