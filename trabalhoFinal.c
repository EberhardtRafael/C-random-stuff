/*
Este código simula a compra de produtos contidos no estoque de uma loja, permite ao usuário que escolha os produtos que queira comprar, calcula o valor final da compra e armazena informações sobre o cliente.
O programa gera um relatório com as informações de cada cliente, data e horário da compra, além do que foi comprado por cada um.

Este código é uma adaptação do trabalho anterior, contendo somente uma loja desta vez, pois não há muito sentido em realizar o mesmo que o código anterior fazia, dado que precisamos gerar uma nota fiscal para uma loja. Então, não faz mais sentido podermos escolher dentre duas.
Ainda, o cliente não pode mais arrepender-se e retornar as compras. Caso isso aconteça, será tratado como um novo cliente.
Por isso, em algum ponto, pode haver vetores onde somente um escalar seria o suficiente. Mas, preferi deixar assim para anter uma característica genérica ao código e mostrar que eu poderia expandi-lo, caso necessário, para contextos mais abrangentes.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

//Declaração de PARÂMETROS
//Parâmetros não são a mesma coisa que variáveis globais, pois, não são variáveis.
//Abaixo, quero criar um booleano: 0 ou 1.
#define TRUE 1
#define FALSE 0 
//O valor do frete é fixo para todos os produtos aos quais se associa frete.
#define FRETE 10


//ESTRUTURAS//

//----------------------
// Tipo DATA
//----------------------

typedef struct {
int fabricacao_mes;
int fabricacao_ano;
int validade_mes;
int validade_ano;
}data;

//----------------------
// Tipo PRODUTO
//----------------------

typedef struct{
int codigo;
char tipo[100]; //Não é a melhorforma, mas funciona.
char marca[100];
float valor;
int quantidade;
int frete; //Não esquecer de adicionar o frente no valor final da compra!
int perecivel;
data fab_val;
}produto;

//----------------------
// Tipo LOJA
//----------------------

typedef struct{
char nome[100];
produto estoque[6]; //Array de produtos.
}loja;


//----------------------
// Tipo ENDERECO
//----------------------
typedef struct{
char rua[100];
int num;
char bairro[100];
char cidade[100];
}endereco;

//----------------------
// Tipo CLIENTE
//----------------------
typedef struct{
char nome[100];
endereco add;
char CPF[100];
}cliente;

//FUNÇÕES//


//-------------------------------------------------------------------------------------------
//A função funciona perfeitamente. Mas, dentro deste programa, não funciona.
void lecomespacos(char *linha){
char entrada;
int i = 0;
do{
entrada = getchar();
linha[i] = entrada;
i++;

}while(entrada != '\n');
}

//-------------------------------------------------------------------------------------------
//Modifica a variável do tipo cliente passada por referência; não retorna nada.
void criaCliente(cliente *client){

    printf("Nome (sem espaços): ");    
    scanf(" %s", client->nome); //O operador -> serve para acessarmos um parâmetro de uma estrutura a qual se acessa por referência.
    printf("CPF: ");    
    scanf(" %s", client->CPF)	;
    printf("Rua (sem espaços): ");
    scanf(" %s", client->add.rua);
    printf("Nro.: ");
    scanf(" %d", &client->add.num);
    printf("Bairro (sem espaços): ");
    scanf(" %s", client->add.bairro);
    printf("Cidade (sem espaços): ");
    scanf(" %s", client->add.cidade);
    //Tentei fazer com que fosse possível ler os nomes com espaço, mas coisas que funcionam em outros programas não funcionam neste.
}

//-------------------------------------------------------------------------------------------
//Recebe uma string como parâmetro e não retorna nada.
//Calcula a quantidade de espaços a ser adicionada a pós uma string para que, ao todo, a string mais os espaços ocupem o espaço, em tela (não na memória!), equivalente a cerca de 20 caracteres (o tamanho de um caracter pode variar, então, não funciona com tanta precisão). 
void calculaEspacos(char* palavra){
	int a = 20 - strlen(palavra);
	for(int i = 0; i < a; i++) printf(" "); 
}

//-------------------------------------------------------------------------------------------
//Recebe uma loja e um inteiro; não retorna nada.
//Dadas uma loja e o número de produtos no estoque, mostra todos os produtos, junto com suas marcas, valores e códigos de barra.
void mostraEstoque(loja *market, int numeroProdutos){

	printf("Produto: ");
	calculaEspacos("Produto: "); //Adiciona uma quantidade conveniente de espaços de forma a tornar o menu mais elegante.
	for(int j = 0; j < numeroProdutos; j++){
		printf("%s", market->estoque[j].tipo);
		calculaEspacos(market->estoque[j].tipo);
	}
	printf("\n");
	printf("Marca: "); 		
	calculaEspacos("Marca: ");
	for(int j = 0; j < numeroProdutos; j++){
		printf("%s", market->estoque[j].marca);
		calculaEspacos(market->estoque[j].marca);
	} 
	printf("\n");
	printf("Valor: ");
	calculaEspacos("Valor: ");
	for(int j = 0; j < numeroProdutos; j++){
		printf("R$ %0.2f", market->estoque[j].valor);
		calculaEspacos("R$ 00.0");
	} 
	printf("\n");
	printf("Código: ");
	calculaEspacos("Código: ");
	for(int j = 0; j < numeroProdutos; j++){
		printf("%04d", market->estoque[j].codigo);
		calculaEspacos("000");
	} 
	printf("\n\n");
}

//-------------------------------------------------------------------------------------------
//Não recebe nada e retorna um inteiro.
//Permite que o usuário escolha se vai comprar na loja 1 ou na loja 2.
//Caso fossem adicionadas mais lojas, esta função deveria ser modificada de acordo.
int escolheLoja(){
	int quantidade_estoque = 0;
	int loja;
	
	do{	
		printf("Digite o número da loja escolhida: ");
		scanf("%d", &loja);
		if(loja == 1 ) quantidade_estoque = 5;
		else if(loja == 2) quantidade_estoque = 6;
		else printf("Loja inexistente. \n");
		}while(loja != 1 && loja != 2);
		
return quantidade_estoque;
}

//-------------------------------------------------------------------------------------------
/*Recebe uma loja (por referência), um inteiro representando a quantidade de produtos que um estoque contém originalmente, um carrinho (por referência) e um inteiro representando a quantidade de produtos dentro de um carrinho;
retorna um float correspondente à soma do valor de todos os produtos contidos no carrinho.
Os produtos no carrinho são representados por seus códigos de barra.

A função verifica, para cada código no carrinho, se ele corresponde a algum produto do estoque. Se sim, soma seu valor ao resultado da aplicação recursiva da função sobre o mesmo carrinho com uma quantidade de produtos reduzida de uma unidade.
*/
float calculaValor(loja *market, int quantidade_estoque, int *carrinho, int quantidade_carrinho){
float sum;

    if(quantidade_carrinho){	
        for(int i = 0; i < quantidade_estoque; i++)				
            if (carrinho[quantidade_carrinho - 1] == market->estoque[i].codigo)			
                sum = market->estoque[i].valor +  calculaValor(market, quantidade_estoque, carrinho, quantidade_carrinho - 1);			
	}else sum = 0; //Caso não haja nenhum produto no carrinho, a função retorna 0. Sem isso, além de a função não funcionar para um carrinho vazio, ela geraria um loop infinito.
		
return sum;	
}
//-------------------------------------------------------------------------------------------
//Recebe uma loja(por referência), um inteiro representando a quantidade de produtos que um estoque contém originalmente, e um inteiro correspondendo a um código de barras;
//retorna um booleano correspondendo à existência, ou não, do produto com o código dado no estoque.
 
int verificaEstoque(loja *market, int quantidade_estoque, int codigo){
int estoque;

    for(int i = 0; i < quantidade_estoque; i++)
        if(market->estoque[i].codigo == codigo) 
            if(market->estoque[i].quantidade > 0) estoque = TRUE;
            else estoque = FALSE;
            
return estoque;
}

//-------------------------------------------------------------------------------------------
/*Recebe uma loja (por referência), um inteiro representando a quantidade de produtos que um estoque contém originalmente, um carrinho (por referência) e um inteiro representando a quantidade de produtos dentro de um carrinho (por referência); 
não retorna nada.
A função printa as informações sobre os produtos contidos no carrinho, como tipo, marca e valor.
Ainda, a função verifica a necessidade de se cobrar frete na compra.
Printa o valor total do carrinho, contando com o frete.
*/
void mostraCarrinho(loja *market, int quantidade_estoque, int *carrinho, int *quantidade_carrinho){
int quantidade = *quantidade_carrinho;
int frete = 0; //Inicializa como zero, pois, se nenhum produto tiver frete, não preciso modificar nada.
	
	printf("\n\nCarrinho: \n\n");
	for(int k = 0; k < quantidade; k++) //Varre todo o estoque, verificando se o código contido no carrinho corresponde a algum produto do estoque.
	    for(int l = 0; l < quantidade_estoque; l++) //Faz isso para cada produto do carrinho.
	        if (carrinho[k] == market->estoque[l].codigo){
		    printf("%s %s", market->estoque[l].tipo, market->estoque[l].marca);
		    printf("------");
		    printf("%0.2f\n", market->estoque[l].valor);
		    if(market->estoque[l].frete) frete = 1;
	
	}
	printf("Frete:----------------------- %d\n", FRETE*frete);
	printf("\n\t\t Total: %0.2f\n", calculaValor(market, quantidade_estoque, carrinho, quantidade) + (float)frete*FRETE);
}

//-------------------------------------------------------------------------------------------
void printaCarrinhoRelatorio(loja *market, int quantidade_estoque, int *carrinho, int *quantidade_carrinho, FILE *arq){
int quantidade = *quantidade_carrinho;
int frete = 0; //Inicializa como zero, pois, se nenhum produto tiver frete, não preciso modificar nada.
	
	if(arq){
	fprintf(arq, "\n\nNota: \n\n");
	for(int k = 0; k < quantidade; k++) //Varre todo o estoque, verificando se o código contido no carrinho corresponde a algum produto do estoque.
	    for(int l = 0; l < quantidade_estoque; l++) //Faz isso para cada produto do carrinho.
	        if (carrinho[k] == market->estoque[l].codigo){
	            fprintf(arq, "%s %s", market->estoque[l].tipo, market->estoque[l].marca);
		    fprintf(arq, "------");
		    fprintf(arq, "%0.2f\n", market->estoque[l].valor);
		    if(market->estoque[l].frete) frete = 1;
	
	}
	fprintf(arq, "Frete:----------------------- %d\n", FRETE*frete);
	fprintf(arq, "\n\t\t Total: %0.2f\n", calculaValor(market, quantidade_estoque, carrinho, quantidade) + (float)frete*FRETE);
	}else printf("Erro: problemas em abrir o arquivo!\n");
}

//-------------------------------------------------------------------------------------------
//Recebe o ponteiro para um arquivo, um cliente e nõ retorna nada.
//Imprime num arquivo a data e a hora do registro da compra e as informações de um cliente.

void printaClienteRelatorio(FILE *arq, cliente client){

time_t t = time(NULL); 
struct tm tm = *localtime(&t);


    if(arq){
    //Printando a data e a hora locais; recebe do computador.
    	fprintf(arq,"Data: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    	
    	//Printando as informações sobre o cliente:
        fprintf(arq, "Nome: %s\n", client.nome);        
        fprintf(arq, "CPF: %s\n", client.CPF);
        fprintf(arq, "Rua: %s\n", client.add.rua);
        fprintf(arq, "Nro.: %d\n", client.add.num);
        fprintf(arq, "Bairro (sem espaços): %s\n", client.add.bairro);
        fprintf(arq, "Cidade (sem espaços): %s\n", client.add.cidade);
        fprintf(arq, "\n");
        }else printf("Erro: problemas em abrir o arquivo!\n");
        
}


//-------------------------------------------------------------------------------------------
/*Recebe uma loja (por referência), um inteiro representando a quantidade de produtos que um estoque contém originalmente, um carrinho (por referência), um inteiro representando a quantidade de produtos dentro de um carrinho (por referência um ponteiro para um arquivo e um cliente; 
não retorna nada.
A função manda printar as informações sobre todos os produtos contidos no estoque da loja escolhida.
Em seguida, pede para o usuário escolher um produto contido no estoque, o que é informado por meio do código de barras, que é um inteiro.
Caso o valor entrado pelo usuário exista no estoque, a função verifica se a quantidade daquele produto no estoque é maior que 0. Se sim, ela adiciona o produto correspondente ao carrinho, se não, avisa que não há produto suficiente e retorna à compra.
O usuário poderá comprar quantos produtos quiser enquanto digitar códigos de barra existentes. Para finalizar as compras, o usuário deve entrar com -1.
Finalizadas as compras, a função manda imprimir tudo o que foi adicionado ao carrinho, junto com o valor total da compra, incluindo o frete.
Ainda, imprime eno arquivo passado as informações sobre o cliente e as compras realizadas.
*/
void realizaCompras(loja *market, int quantidade_estoque, int *carrinho, int *quantidade_carrinho, FILE *arq, cliente client){
int codigo, forma_pagamento;

	mostraEstoque(market, quantidade_estoque);
	do{
		
		printf("Escreva o código do produto para adicioná-lo ao carrinho (ou -1, para terminar a compra): ");
		scanf("%d", &codigo);	
				
		for(int i = 0; i < quantidade_estoque; i++){ //Varre todo o estoque verificando se o código de barras entrado corresponde a um produto existente.
		if(codigo == market->estoque[i].codigo){ //Caso o produto exista
			if(verificaEstoque(market, quantidade_estoque, market->estoque[i].codigo)){ //Verifica se há produto suficiente.
			    printf("Adicionando 1 produto %s, modelo %s - valor: R$ %0.2f .\n\n", market->estoque[i].tipo, market->estoque[i].marca, market->estoque[i].valor );			   
			    market->estoque[i].quantidade -= 1; //Diminui a quantidade de produtos no estoque em uma unidade.			    
			    carrinho[*quantidade_carrinho] = codigo; //Modifica a posição atual do carrinho, colocando o código do produto comprado lá dentro.
			    *quantidade_carrinho += 1; //Aumenta a quantidade de produtos no carrinho de uma unidade.			
			   }else printf("Estoque insuficiente.\n\n"); //Caso não haja produto no estoque.
			} 		
		}		
	}while(codigo != -1 );	//O loop roda enquanto o usuário não mandar finalizar.
	mostraCarrinho(market, quantidade_estoque, carrinho, quantidade_carrinho);
	
	arq = fopen("Relatorio.dat", "a");
	//Pede informações acerca do cliente.
   	criaCliente(&client); //As informações sobre o cliente serão guardadas.   	    	
    	printf("Forma de pagamento (1.dinheiro; 2.cartão): "); //Não será nada guardado.
    	scanf("%d", &forma_pagamento); 
   	if(forma_pagamento == 1) printf("Selecionado forma de pagamento: dinheiro. \n");
   	else printf("Selecionado forma de pagamento: cartão. \n");    
	printaClienteRelatorio(arq, client);
	printaCarrinhoRelatorio(market, quantidade_estoque, carrinho, quantidade_carrinho, arq);
	fclose(arq);
}

//-------------------------------------------------------------------------------------------


int main(){

//DECLARAÇÃO DE VARIÁVEIS

//Variáveis de várias naturezas.

FILE *arq1; //Assim que se declara um arquivo do tipo file.

int quantidade_estoque;
int carrinho[100]; //Este tamanho não é realista e deveria ser indefinido, mas funciona para o problema em particular.
int quantidade_carrinho[100];
cliente CLIENTELA[100]; //Este tamanho não é realista e deveria ser indefinido, mas funciona para o problema em particular.
int escolha_menu = -1;
char escolha_final = 'n';
int num_clientes = 0;


//Variáveis do tipo PRODUTO
produto PRODUTO1;
PRODUTO1.codigo = 30;
strcpy(PRODUTO1.tipo, "Pão fatiado");
strcpy(PRODUTO1.marca, "Four Boys");
PRODUTO1.valor = 06.60;
PRODUTO1.quantidade = 1;
PRODUTO1.perecivel = TRUE; 
PRODUTO1.fab_val.fabricacao_mes = 04;
PRODUTO1.fab_val.fabricacao_ano = 2021;
PRODUTO1.fab_val.validade_mes = 04;
PRODUTO1.fab_val.validade_ano = 2021;
PRODUTO1.frete = FALSE; //De acordo com o enunciado, o frete é associado a um produto, não a uma loja. além de ter um valor fixo.

produto PRODUTO2;
PRODUTO2.codigo = 110;
strcpy(PRODUTO2.tipo, "Detergente");
strcpy(PRODUTO2.marca, "Qdetergente");
PRODUTO2.valor = 03.45;
PRODUTO2.quantidade = 100;
PRODUTO2.frete = TRUE;
PRODUTO2.perecivel = FALSE;

produto PRODUTO3;
PRODUTO3.codigo = 3010;
strcpy(PRODUTO3.tipo, "Banana");
strcpy(PRODUTO3.marca, "Caturra");
PRODUTO3.valor = 07.90;
PRODUTO3.quantidade = 20;
PRODUTO3.frete = TRUE;
PRODUTO3.perecivel = FALSE;

produto PRODUTO4;
PRODUTO4.codigo = 2210;
strcpy(PRODUTO4.tipo, "Arroz");
strcpy(PRODUTO4.marca, "Tio Carlos");
PRODUTO4.valor = 20.45;
PRODUTO4.quantidade = 5;
PRODUTO4.frete = TRUE;
PRODUTO4.perecivel = TRUE;
PRODUTO4.fab_val.fabricacao_mes = 04;
PRODUTO4.fab_val.fabricacao_ano = 2021;
PRODUTO4.fab_val.validade_mes = 10;
PRODUTO4.fab_val.validade_ano = 2021;

produto PRODUTO5;
PRODUTO5.codigo = 11;
strcpy(PRODUTO5.tipo, "Cerveja");
strcpy(PRODUTO5.marca, "Lokão");
PRODUTO5.valor = 01.25;
PRODUTO5.quantidade = 1000;
PRODUTO5.frete = FALSE;
PRODUTO5.perecivel = TRUE;
PRODUTO5.fab_val.fabricacao_mes = 04;
PRODUTO5.fab_val.fabricacao_ano = 2021;
PRODUTO5.fab_val.validade_mes = 04;
PRODUTO5.fab_val.validade_ano = 2022;

produto PRODUTO6;
PRODUTO6.codigo = 1010;
strcpy(PRODUTO6.tipo, "Cerveja");
strcpy(PRODUTO6.marca, "Belavisão");
PRODUTO6.valor = 2.99;
PRODUTO6.quantidade = 200;
PRODUTO6.frete = TRUE;
PRODUTO6.perecivel = FALSE;
PRODUTO6.fab_val.fabricacao_mes = 04;
PRODUTO6.fab_val.fabricacao_ano = 2021;
PRODUTO6.fab_val.validade_mes = 04;
PRODUTO6.fab_val.validade_ano = 2022;

produto PRODUTO7;
PRODUTO7.codigo = 14;
strcpy(PRODUTO7.tipo, "Sabonete");
strcpy(PRODUTO7.marca, "Qsabão");
PRODUTO7.valor = 01.35;
PRODUTO7.quantidade = 500;
PRODUTO7.frete = FALSE;
PRODUTO7.perecivel = FALSE;

produto PRODUTO8;
PRODUTO8.codigo = 666;
strcpy(PRODUTO8.tipo, "Pasta de dente");
strcpy(PRODUTO8.marca, "Qpasta");
PRODUTO8.valor = 3.60;
PRODUTO8.quantidade = 1000;
PRODUTO8.frete = TRUE;
PRODUTO8.perecivel = FALSE;

//Variáveis do tipo LOJA
loja LOJA1;
strcpy(LOJA1.nome, "Qpreco");
LOJA1.estoque[0] = PRODUTO1;
LOJA1.estoque[1] = PRODUTO2;
LOJA1.estoque[2] = PRODUTO3;
LOJA1.estoque[3] = PRODUTO4;
LOJA1.estoque[4] = PRODUTO5;


                 
     printf(" -------------------------   \n");
     printf("| Bem vindo à loja %s !|\n", LOJA1.nome);
     printf(" -------------------------   \n");
     printf("Confira nosso estoque: \n\n");
     realizaCompras(&LOJA1, 5, &carrinho[num_clientes], &quantidade_carrinho[num_clientes], arq1, CLIENTELA[0]);
         
   


return 0;
}
