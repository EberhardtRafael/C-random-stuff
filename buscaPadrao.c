/*
Este programa lê um arquivo escolhido pelo usuário e imprime na tela todas as suas linhas enumeradas (caso escolhido).
Por default, a opção acima vem desativada.
O arquivo original não será alterado, pois apenas estamos printando suas informações na tela.
SE FOR REALIZAR MAIS DE UMA OPERAÇÃO SOBRE UM MESMO ARQUIVO: LEMBRAR DE FECHÁ-LO ASSIM QUE TERMINAR CADA OPERAÇÃO!
QUERENDO REALIZAR MAIS ALGUMA LEITURA OU ESCRITA SOBRE O MESMO ARQUIVO, ABRE E FECHA NOVAMENTE!
SENÃO VAI DAR CONFLITO!

O programa pede uma string ao usuário, a qual será procurada dentro do arquivo dado;
A quantidade de ocorrências dessa string no arquivo é printada em tela.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void lecomespacos(char *linha){
char entrada;
int i = 0;
do{
entrada = getchar();
linha[i] = entrada;
i++;
}while(entrada != '\n');
}

//buscaPadrao: recebe string, string; retorna int. 
/*
Dados uma string qualquer e uma string referente ao nome de um arquivo, a função abre o arquivo, conta a ocorrências da string dada no arquivo
e o fecha.
*/

int buscaPadrao(char *linha, char *arquivo_nome){

char linha_arq[100]; //Exagerei de propósito no tamanho mesmo.
FILE *arq1; //Assim que se declara um arquivo do tipo file.
int i = 0, j = 0; //Aqui eu inicializo o i porque ele será um contador.

arq1 = fopen(arquivo_nome, "r"); //Abrindo o arquivo.

	if(arq1 == NULL){ //Verificando se o arquivo abriu mesmo.
		printf("Erro: problemas em abrir o arquivo!");
	}
	else{
		while((fgets(linha_arq, 99, arq1))){ //Enquanto fgets não encontrar o que ler
		j++; //Conta o número de linhas o arquivo
		//Descomente abaixo para printar o texto inteiro em tela:
		//printf("%d - %s", j, linha_arq);		
		if(strstr(linha_arq, linha)) i++; //strstr() procura pela ocorrência de uma string dentro de uma string.			
		}
		printf("A quantidade de linhas nesse texto é: %d.\n", j); //Isso também é extra; apenas para controle.
	}
fclose(arq1); //Fechando o arquivo. Importante lembrar!!!

return i;
}


int main(){


char linha[100], arquivo_nome[50];
int i; //Aqui i não é um contador e não rpecisa ser inicializado.


lecomespacos(linha);
printf("%s", linha);

printf("Escreva uma frase que gostaria de procurar em um texto: ");
gets(linha); //Funciona com um trecho do texto também.
printf("Agora escreva o nome do arquivo no qual gostaria de procurar pela linha_arq: ");
gets(arquivo_nome);

printf("\n"); //Somente para não ficar tudo muito próximo na tela.

i = buscaPadrao(linha, arquivo_nome); //String, assim como qualquer vetor, já é um ponteiro e, portanto, isso é passar a string como ponteiro.
		
printf("A quantidade de ocorrências da string dada nesse texto é: %d.\n", i); 

return 0;
}
