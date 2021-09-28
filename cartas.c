#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define NCARTAS 104
#define NCARTASMAO 9

//-------------------------------------------------------
//A estrutura carta não é uma pilha.
typedef struct{

char naipe[10];
char cor[10]; 
int valor;

}carta;

//-------------------------------------------------------
//A estrutura deck é uma pilha (de cartas).
typedef struct{

int tammax;
int topo;
carta *pilha;

}deck; 

//-------------------------------------------------------
//A estrutura mao não é uma pilha.
typedef struct{

carta cartas[NCARTASMAO];

}mao;

//-------------------------------------------------------
//A estrutura player não é uma pilha.
typedef struct{

carta cartas[5];

char nome[10];
mao hand;
int pontuacao;

}player;


//-------------------------------------------------------
 
    /*
    Dado um inteiro que representa o tamanho de um deck, cria um deck novo; retorna um ponteiro para um deck.
    Como o ponteiro aponta para um deck, também deve ser do tipo deck.
    */

deck* newDeck(int tamanho){

    deck *pt = (deck*)malloc(sizeof(deck)); //Criando um ponteiro do tipo deck.
 
    pt->tammax = tamanho; //Colocando no atributo tammax do deck o argumento passado.
    pt->topo = -1; // Deixa assim, pelo menos por ora.
    pt->pilha = (carta*)malloc(sizeof(carta)*tamanho);
    //A alocação de memória para o tamanho da pilha é dinâmica, mas nem precisaria, neste caso, pois um deck de cartas tem sempre o mesmo tamanho. Mesmo assim, estou criando um programa mais abrangente somente para mostrar que existem maiores possibilidades. 
 
    return pt;
}

//------------------------------------------------------- 
 
// Dada uma pilha(aqui, um deck), verifica se está cheia ou não.
int isFull(deck *pt) {
    return pt->topo == pt->tammax - 1; 
    // Também funcionaria: return size(pt) == pt->maxsize;
}

//-------------------------------------------------------

    /*
    Dada uma pilha e uma carta, adiciona a carta à pilha.
    Pode facilmente ser modifiada para inserir elementos de outros tipos à pila.
    */

void push(deck *pt, carta card){

    // Primeiro, verifica e a pilha já está cheia. 
    // Inserir mais um elemento a uma pilha cheia dá origem a um "stack overflow", ou seja,
    // Estaríamos utilizando memória que não foi designada à pilha para "enfiar guela abaixo" esse elemento em algum lugar.
    // Não sei se os compiladores, ou mesmo o sistema operacional, me impediria de fazê-lo, 
    //logo, eu poderia arranjar problemas se não observasse essa possibilidade antes de prosseguir.
    // Sei que linguagens de mais alto nível, como Python, não me permitem fazê-lo e eu não corro o risco.
    //(Prefiro o C).
       
    if (isFull(pt))
    {
        printf("Overflow!\nPrograma Finalizado.\n");
        exit(EXIT_FAILURE);
    }
 
    //printf("Inserindo elemento\n"); //Só balaca.
 
    // Adiciona um elemento à pilha e incrementa o topo em uma unidade.
    pt->pilha[++pt->topo] = card; //Álgebra de ponteiros... 
}
//-------------------------------------------------------

    /*
    Dado um vetor, um valor inteiro e o tamanho do vetor, a função verifica se o valor inteiro dado 
    é ou não um elemento do vetor. 
    Retorna 0 emcaso negativo e 1 em caso positivo. 
    */
    
int estaNoVetor(int *vetor, int entrada, int tamanhoVetor){

int igual = 0;

    for(int i = 0; i < tamanhoVetor; i++)
        if(entrada == vetor[i]) igual = 1;
        
    return igual;
}
//-------------------------------------------------------

//Recebe um deck e preenche a pilha elemento a elemento. Não retorna nada.
void populaPilha(deck *stack){

int valor, contador = 0, codigo, random;
int codigoVec[NCARTAS + 1];
char naipe[10], cor[10]; 
carta card;

FILE *arq1; //Assim que se declara um arquivo do tipo file.

srand(time(NULL));   // Usa o horário do computador como seed.

arq1 = fopen("cartas.txt", "r"); //Abrindo o arquivo.

	if(arq1 == NULL){ //Verificando se o arquivo abriu mesmo.
		printf("Erro: problemas em abrir o arquivo!");
	}
	else{
	    while(contador < stack->tammax){ //Enquanto não popular todas as cartas,
	        random = rand() % NCARTAS + 1; //Gera um número aeatório entre 1 e NCARTAS,
	            do{ 
	                fscanf(arq1, "%d", &codigo); //Procura no arquivo pela carta cujo código corresponda ao número aleatório gerado,
	                fscanf(arq1, "%s", naipe); //No momento em que encontar, automaticamente o que for lido agora estará na mesma linha.
	                fscanf(arq1, "%s", cor);
	                fscanf(arq1, "%d", &valor);                           	        
	                }while(codigo != random); //O loop acontece enquanto o código não for encontrado. (Assumo qeu o código existe.)
	            
	                /*
	                    OBS.:
	                       1) O código da carta necessariamente existe porque eu fui quem criou o arquivo contendo todas as cartas;
	                       2) Neste jogo, cartas não podem ser destruídas (A manos que se tenha acesso ao arquivo).
	                */
	                
	            codigoVec[contador] = codigo;
	            fseek( arq1, 0, SEEK_SET);	//Retorna para o início do arquivo.
	            
	            //printf("%d, %s, %s, %d\n", codigo, naipe, cor, valor);	//Apenas para controle.
	            
	            // Guarda as informações lidas na variável card:
	            if(!estaNoVetor(codigoVec, codigo, contador)){
	                strcpy(card.naipe, naipe); 
	                strcpy(card.cor, cor);
	                card.valor = valor;
	                push(stack, card);
	                contador++; //Aumenta a cada vez que o número aleatório correponder ao código de uma carta.
	            }
	        }//termina while loop  

            fclose(arq1); //Fechando o arquivo. Importante lembrar!!!
            
            } //termina else
}

//------------------------------------------------------- 
 
// Dada uma pilha (aqui, um deck), retorna seu tamanho atual.
// Serve para controle.
int size(deck *pt) {
    return pt->topo + 1;
}
//-------------------------------------------------------

// Dada uma pilha (aqui, um deck), verifica se está vazia ou não.
// Serve para controle.

int isEmpty(deck *pt) {
    return pt->topo == -1;  // Também funcionaria: return size(pt) == 0;
}
//-------------------------------------------------------

 
// Dada uma pilha (aqui, um deck), retorna o último elemento a ter sido adicionado.
carta UltimaCarta(deck *pt){
    // Verifica, antes, se a pilha está vazia.
    if (!isEmpty(pt)) {
        return pt->pilha[pt->topo];
    }
    else {
        exit(EXIT_FAILURE);
    }
}
//-------------------------------------------------------
 
// Dada uma pilha, retira o último elemento a ter sido adicionado.
carta pop(deck *pt){
    // Verifica se a pilha está vazia.
    if (isEmpty(pt))
    {
        printf("Underflow!\nPrograma finalizado.\n");
        exit(EXIT_FAILURE);
    }
 
    //printf("Retirando elemento!\n");
 
    // Decrementa o tamanho da pilha e retorna o elemento retirado.
    return pt->pilha[pt->topo--];
}
//-------------------------------------------------------
// Dado um vetor de player e um inteiro n, cria n jogadores novos.
void newGamer(player *gamer, int n){

int i, j;

    printf("Player %d.\nEscreva o nome do jogador: \n", n + 1);
    scanf(" %s", gamer->nome); //Por enquanto, o nome não pode ter espaços.    
    gamer->pontuacao = 0; 
    
}

//-------------------------------------------------------
// Dado um vetor de player, um número de jogadores e um deck de cartas, distribui as cartas para cada jogador.
void distribuiCartas(player *gamers, int nplayers, deck *stack){

    for (int j = 0; j < NCARTASMAO; j++) //Distribui de forma alternada entre os jogadores.
         for (int i = 0; i < nplayers; i++) gamers[i].hand.cartas[j] = pop(stack);
         //O deck tem que ser passado como ponteiro para que seja realmente modificada a pilha de cartas.
}
//-------------------------------------------------------

// Dadas duas cartas, vrifica se ambas têm o mesmo valor, independente de cor e naipe.
int mesmoValor(carta card1, carta card2){

    return card1.valor == card2.valor;
}
//-------------------------------------------------------

// Dadas duas cartas, verifica se são sucessivas.
// Retorna 0 caso as cartas sejam de mesmo valor;
// Retorna 1 caso a primeira carta seja sucessora da segunda;
// Retorna -1 caso a segunda carta seja sucessora da primeira;
// Retorna 10 caso nenhuma das alternativas acima seja satisfeita.
int sequencia(carta card1, carta card2){

int seq;
    
     if(card1.valor == card2.valor) seq = 0;
     else if (card1.valor == card2.valor + 1) seq = 1; //card1 é sucessora de card2.
     else if (card1.valor == card2.valor - 1) seq = -1; //card1 é antecessora de card2.
     else seq = 10;
          
     return seq; 
}
//-------------------------------------------------------

// Dada uma mão (contendo especificamente NCARTASMAO cartas), verifica se há uma sequência de três cartas com valores sucessivos.
// Retorna um ponteiro o qual aponta para um vetor de entradas -1 caso não haja sequência;
// Retorna um ponteiro o qual aponta par aum vetor ccujos elementos são as posições das cartas em que há sequência, caso exista.
// Pode facilmente ser modificada para receber mãos com diferentes quantidades de cartas.
int* sequenciaMao(mao hand, int *eqvec1, int *eqvec2){

int *trinca = (int*)malloc(sizeof(int)); //Retornar ponteiro de função não é a melhor coisa, mas caso o faça, inicializa ele com malloc().

for(int i = 0; i < 3; i++) trinca[i] = -1; 
    
     // Não estou ligando para as redundâncias, pois são apenas NCARTASMAO cartas.
    // Caso a quantidade de cartas fosse maior que NCARTASMAO, a função deveria ser modificada para tornar-se mais eficiente.
    for(int j = 0; j < NCARTASMAO; j++){ //Para cada uma das  cartas da mão,
        if(j != eqvec1[0] && j != eqvec1[1] && j != eqvec1[2] && j != eqvec2[0] && j != eqvec2[1] && j != eqvec2[2]) //Isto serve para eliminar a possibilidade de contarmos duas vezes a mesma trinca. O problema é que, a partir do momento que uma trinca for feita, não posso mais voltar atrás e utilizar uma de suas cartas para outro fim. Ainda, as posições das cartas na trinca não poderão mais conter outras cartas que possam vir a fazer parte de outra trinca. É um bug da versão atual do jogo e eu poderia melhorar pensando um pouco mais, mas, como em geral o jogo funciona relativamente bem, estou deixando assim.
        for(int i = 0; i < NCARTASMAO; i++){ //Para cada uma das outras cartas da mesma mão,
            if(i != eqvec1[0] && i != eqvec1[1] && i != eqvec1[2] && i != eqvec2[0] && i != eqvec2[1] && i != eqvec2[2]) //Evitando contar mais de uma vez a mesma trinca.
            if(i != j) //Sendo essas diferentes da carta j,
                if(!strcmp(hand.cartas[i].naipe, hand.cartas[j].naipe)) //Caso os naipes de i e j sejam iguais,
                if(sequencia(hand.cartas[i], hand.cartas[j]) < 10){ //Caso a função sequencia() retorne a possibilidade de haver sequência entre as cartas da posição i e j da mão,
                    if(sequencia(hand.cartas[i], hand.cartas[j]) < 0){ //Verifico se a carta i é antecessora de j,
                        for(int k = 0; k < NCARTASMAO; k++) //Se sim, para cada carta do resto da mão,
                            if(k != eqvec1[0] && k != eqvec1[1] && k != eqvec1[2] && k != eqvec2[0] && k != eqvec2[1] && k != eqvec2[2])
                            if(k != j && k!= i) //Sendo essas diferentes das cartas j e i,
                                if(!strcmp(hand.cartas[j].naipe, hand.cartas[k].naipe)) //Caso os naipes de j e k sejam iguais,
                                if(sequencia(hand.cartas[j], hand.cartas[k]) < 0){ //Verifico se a carta k é sucessora de j. Se sim, há sequência
                                     trinca[0] = i; //Inicializo as entradas do vetor para o qual o ponteiro trinca aponta.
                                     trinca[1] = j;
                                     trinca[2] = k;
                                 } //Verifico se a carta j é antecessora de alguma carta k. Se sim, tenho uma trinca.
                                else if (sequencia(hand.cartas[i], hand.cartas[k]) == 1){
                                     trinca[0] = i;
                                     trinca[1] = j;
                                     trinca[2] = k;
                                 } //Se não, verifico ainda a possibilidade de i ser sucessora de alguma carta k. Se sim, também tenho uma trinca.
                    }else if(sequencia(hand.cartas[i], hand.cartas[j]) > 0){ //Caso i não seja sucessora de nenhuma j, pode ser que ainda seja antecessora de alguma j. Se sim,
                        for(int k = 0; k < NCARTASMAO; k++) //Para cada uma das outras cartas k, 
                            if(k != j && k!= i) //Sendo k diferente de i e j,
                                if(!strcmp(hand.cartas[j].naipe, hand.cartas[k].naipe)) //Caso os naipes de j e k sejam iguais,
                                    if(sequencia(hand.cartas[j], hand.cartas[k]) == 1){
                                        trinca[0] = i;
                                        trinca[1] = j;
                                        trinca[2] = k;
                                    } //Verifico se j é sucessora de alguma k,
                                    else if (sequencia(hand.cartas[i], hand.cartas[k]) < 0){
                                        trinca[0] = j;
                                        trinca[1] = i;
                                        trinca[2] = k;
                                    } //Se não, verifico se i é antecessora de alguma k. Em ambos os casos, tenho uma trinca.                
                    }                
                } //Se não houver nenhuma possibilidade de sequência, não preciso colocar um else aqui porque já inicializei trinca = -1.
            }
        }
 
    return trinca;    
}
//-------------------------------------------------------

// Dada uma mão, verifica a existência de alguma trinca nela.
/// Retorna um ponteiro o qual aponta para um vetor de entradas 0 caso não haja sequência;
// Retorna um ponteiro o qual aponta par aum vetor ccujos elementos são as posições das cartas em que há sequência, caso exista.
int* mesmoValorMao(mao hand, int *eqvec1, int *eqvec2){

int *trinca = (int*)malloc(sizeof(int));

    for(int i = 0; i < 3; i++) trinca[i] = -1;
   
    // Novamente, não estou ligando para redundâncias.
    for(int j = 0; j < NCARTASMAO; j++) //Para cada carta da mão,
        if(j != eqvec1[0] && j != eqvec1[1] && j != eqvec1[2] && j != eqvec2[0] && j != eqvec2[1] && j != eqvec2[2])            
        for(int i = 0; i < NCARTASMAO; i++) //Para cada uma das outras cartas da mão,
            if(i != eqvec1[0] && i != eqvec1[1] && i != eqvec1[2] && i != eqvec2[0] && i != eqvec2[1] && i != eqvec2[2])
            if(j != i) //Certificando que a carta i é diferente de j,
                if(mesmoValor(hand.cartas[i], hand.cartas[j])) //Verifico se os valores de i e j são iguais,
                    for(int k = 0; k < NCARTASMAO; k++) //Se sim, para cada uma das outras cartas k da mão,
                        if(k != eqvec1[0] && k != eqvec1[1] && k != eqvec1[2] && k != eqvec2[0] && k != eqvec2[1] && k != eqvec2[2])
                        if (k != i && k != j) //Sendo essas cartas diferentes das duas anteriores,
                                 if(mesmoValor(hand.cartas[i], hand.cartas[k])){
                                     trinca[0] = j;
                                     trinca[1] = i;
                                     trinca[2] = k;
                                 }  //Verifico se os valores de i e k são iguais. Se sim, trinca é verdadeira. Caso a trinca nunca seja verdadeira dentro da mão, o valor permanece -1, pois assim foi inicializado.
 
    return trinca;   
}

//------------------------------------------------------- 

    
     //Dada uma mão e o número de cartas nela contida, printa na tela os desenhos das cartas contidas nessa mão.
    
void mostraMao(mao hand, int ncartas){

int valor_lido;
char carta_paus[12], carta_ouros[12], carta_copas[12], carta_espadas[12]; 
int contador;
int marcador;

FILE *arq1; //Assim que se declara um arquivo do tipo file.

arq1 = fopen("desenho_cartas.txt", "r"); //Abrindo o arquivo.

    if(!arq1){ //Verificando se o arquivo abriu mesmo.
		printf("Erro: problemas em abrir o arquivo!");
	}
	else{ 
	   
	   printf("\t 1 \t\t 2 \t\t 3 \t\t 4 \t\t 5 \t\t 6 \t\t 7 \t\t 8 \t\t 9 \t\n"); //Printa a posição de cada carta.
	   for(int j = 0; j < 8; j++){ //O loop acontece 8 vezes porque o desenho de uma carta tem 8 linhas.
	       for(int i = 0; i < ncartas; i++){ //A ordem dos loops importa para printar as cartas uma ao lado da outra.
	       marcador = hand.cartas[i].valor; //Para cada carta da mão, eu verifico qual é o valor.
	       contador = -1;
	       do{
	           fscanf(arq1, "%d", &valor_lido); //Leio no arquivo com os desenhos das cartas linha por linha até encontrar o valor da carta.
	           fscanf(arq1, "%s", carta_paus); //Leio no arquivo, linha por linha, o desenho de cada uma das cartas (veja o arquivo!).
	           fscanf(arq1, "%s", carta_ouros);
	           fscanf(arq1, "%s", carta_copas);
	           fscanf(arq1, "%s", carta_espadas);
	           if(valor_lido == marcador) contador++; 	                      
	        }while(contador != j); //Serve para que não leia 8 x somente a primeira linha do desenho.
	        
	        printf("\t"); //Para que uma carta seja printada ao lado da outra de forma organizada.	        
	        if(!strcmp(hand.cartas[i].naipe, "paus"))printf("%s   ", carta_paus); //Somente printo o desenho correspondente ao naipe certo.
	        else if(!strcmp(hand.cartas[i].naipe, "ouros"))printf("%s   ", carta_ouros);
	        else if(!strcmp(hand.cartas[i].naipe, "copas"))printf("%s   ", carta_copas);
	        else if(!strcmp(hand.cartas[i].naipe, "espadas"))printf("%s   ", carta_espadas);
	        fseek( arq1, 0, SEEK_SET); //Retorna par ao início do arquivo para printar as outras cartas da mão.
	       }
	   printf("\n");
	   
	   }
	   fclose(arq1);
    }
}
//------------------------------------------------------- 

    /*
     Não recebe nada.
     Permite que o usuário escolha uma carta da mão para ser descartada.
     Retorna a posição da carta escolhida. 
     Serve para ser utilizada internamente por outra função.
    */
int largarCarta(){

int posicao = 0;

    while(posicao < 1 || posicao > NCARTASMAO){
        printf("Qual a posição da carta que você gostaria de largar? (entre 1 e 9)");
        scanf("%d", &posicao);
        if(posicao < 1 || posicao > NCARTASMAO) printf("Carta não existente!\n");   
    }  
    
    return posicao;
}
//-------------------------------------------------------

    /*
    Dados um deck de cartas voltadas para baixo, um deck de cartas correspondente às que já foram descartadas, uma mão e um 
    inteiro que corresponde a um jogador (player 1, player 2 etc), permite que o jogador compre uma carta do deck de cartas,
     a qual, de acordo com as regras do pife, está voltada para baixo. Portanto, é uma compra cega.
     Não retorna nada.
    */
void comprarCarta(deck *baralho, deck *morto, mao *hand, int gamer){

int posicao;
    
    if(gamer) posicao = NCARTASMAO; //Caso o gamer não seja o player 1, (no caso, a máquina), ele sempre descarta a última carta da mão.
    else posicao = largarCarta(); //Caso seja o player 1, ele pode escolher a carta a ser descartada.
    //Neste jogo, a máquina não é um jogador inteligente, portanto, o que aumenta as chances de o usuário ganhar.
    //Não seria muito difícil tornar a máquina mais eficiente, mas o jogo funciona bem o suficiente para os propósitos do trabalho.
    
    push(morto, hand->cartas[posicao - 1]); //Coloco no morto, que é uma pilha, a carta descartada.
    
    hand->cartas[posicao - 1].valor = UltimaCarta(baralho).valor; //Coloco na mão a carta do topo da pilha correspondente ao deck.
    strcpy(hand->cartas[posicao - 1].naipe, UltimaCarta(baralho).naipe);
    strcpy(hand->cartas[posicao - 1].naipe, pop(baralho).naipe); //Já retira a última carta do deck.

}
//-------------------------------------------------------
    /*
     Dados um deck de cartas correspondente às que já foram descartadas e uma mão, permite que o player 1 compre a carta do topo
     do morto, a qual está voltada para cima.
     Não retorna nada.
    */
void pegardoMorto(deck *morto, mao *hand){

int posicao;
    
    posicao = largarCarta(); //Pede para escolher qual carta será descartada.
        
    hand->cartas[posicao - 1].valor = UltimaCarta(morto).valor; //Coloca na mão a carta do topo do morto.
    strcpy(hand->cartas[posicao - 1].naipe, UltimaCarta(morto).naipe);
    strcpy(hand->cartas[posicao - 1].naipe, pop(morto).naipe); //Já retira a última carta do morto.
}

//-------------------------------------------------------

    /*
      Dada um vetor de cartas e o número de cartas nele contido, printa na tela o seus desenhos lado a lado.
      Poderia reescrever esta e a função mostraMao, obtendo somente uma.
      A questão é que é mais fácil ter uma função especializada em mostrar todas as cartas de uma mão, que é uma estrutura em si
      e outra que mostre as cartas de um vetor qualquer de cartas, que não é uma estrutura. Acho mais organizado.  
    */

void mostraCarta(carta *card, int ncards){

int valor_lido;
char carta_paus[12], carta_ouros[12], carta_copas[12], carta_espadas[12]; 
int contador;
int marcador;

FILE *arq1; //Assim que se declara um arquivo do tipo file.

arq1 = fopen("desenho_cartas.txt", "r"); //Abrindo o arquivo.

    if(!arq1){ //Verificando se o arquivo abriu mesmo.
		printf("Erro: problemas em abrir o arquivo!");
	}
	else{ 
        
	   printf("\tMonte:\t\t Morto:\n");
           
           //Aqui o funcionamento é semelhante à mostraMao().
	   for(int j = 0; j< 8; j++){
	       for(int i = 0; i < ncards; i++){
	       marcador = card[i].valor;
	       contador = -1;
	       do{
	           fscanf(arq1, "%d", &valor_lido);
	           fscanf(arq1, "%s", carta_paus);
	           fscanf(arq1, "%s", carta_ouros);
	           fscanf(arq1, "%s", carta_copas);
	           fscanf(arq1, "%s", carta_espadas);
	           if(valor_lido == marcador) contador++;	                      
	        }while(contador != j);         
	        
	        printf("\t");
	        if(!strcmp(card[i].naipe, "paus"))printf("%s   ", carta_paus);
	        else if(!strcmp(card[i].naipe, "ouros"))printf("%s   ", carta_ouros);
	        else if(!strcmp(card[i].naipe, "copas"))printf("%s   ", carta_copas);
	        else if(!strcmp(card[i].naipe, "espadas"))printf("%s   ", carta_espadas);
	        else if(!strcmp(card[i].naipe, "Null"))printf("%s   ", carta_espadas); //É uma carta voltada para baixo.
	        fseek( arq1, 0, SEEK_SET);
	       }
	       
	       printf("\n");
	   
	   }
	   fclose(arq1);
    }

}
//-------------------------------------------------------
    /*
     Dado um vetor de players e um inteiro correspondente ao número de jogadores da partida, 
     cria todas as variáveis e chama todas as funções necessárias para que a partida aconteça.
    */
void game(player *jogadores, int njogadores){

int seqMatrix[njogadores][3][3], eqValorMatrix[njogadores][3][3]; //Matrizes que guardam a quantidade de trincas de cada jogador.

    /*
     Perceba que as matrizes acima são tridimensionais.
     A primeira dimensão corresponde ao player;
     A segunda posição corresponde à qual sequência(ou trinca de mesmo valor) com que estamos tratando. Como pode haver no máximo 3 trincas, precisamos de 3 posições para isso;
     A terceira dimensão serve para armazenar as posições das cartas, na mão do jogador, nas quais a sequência(ou trinca de mesmo valor) ocorre. 
    */
    
int *trincaVec1, *trincaVec2; //Ponteiros que receberão os retornos das funções sequenciaMao() e mesmoValorMao().
int i, j, k, trincas = 0, trincasGamer[njogadores]; //Aqui o i precisa ser "público" dentro de toda a função, pois não será usado somente localmente num loop.
deck *baralho, *morto; //Criando ponteiros do tipo deck.
int posicao;
int acao = 1, rodadas = 0;
carta cardsVec[2]; //Um vetor de cartas que conterá uma carta vazia e a última carta do morto. Serve para printar em tela o resto do aspecto do jogo.

carta cartaVazia; //Criando a carta vazia.

    //Colocando valor -1 a todas as entradas das matrizes que guardam a quantidade de trincas de cada jogador.
    for(i = 0; i < njogadores; i++)
        for(j = 0; j < 3; j++)
            for(k = 0; k < 3; k++){
                seqMatrix[i][j][k] = -1;
                eqValorMatrix[i][j][k] = -1; //Voltar e verificar isto depois. Somente os valores de k que importam.
        } 
                
     for(k = 0; k < njogadores; k++) trincasGamer[k] = 0; //Cada gamer começa com 0 trincas.
     
    strcpy(cartaVazia.naipe, "Null");  //Poderia criar uma função somente para inicializar a carta vazia, mas, ok por ora.
    strcpy(cartaVazia.cor, "Null");
    cartaVazia.valor = 500; //Poderia ser um valor qualquer que nenhuma outra carta do deck pudesse ter. Mas, teria de modificar isso no .txt contendo o desenho das cartas.
    
    cardsVec[0] = cartaVazia; //Por ora, o vetor de cartas cardVec terá uma carta vazia em ambas as posições.
    cardsVec[1] = cartaVazia;
    
    baralho = newDeck(NCARTAS); //Criando as características desse deck (tamanho maximo, topo e vetor de cartas).
    morto = newDeck(NCARTAS); //Criando uma pilha que corresponde ao morto.
    push(morto, cartaVazia); //Colocando a carta vazia dentro do morto.
    printf("Embaralhando...\n");
    populaPilha(baralho); //Adicionando as características específicas deste deck de cartas (como cada uma das cartas).   

    //for(int i = 0; i < size(baralho); i++) printf("%d, %d, %s\n", i + 1, baralho->pilha[i].valor, baralho->pilha[i].naipe); //Serve apenas para controle.

    printf("Distribuindo as cartas...\n"); 
    distribuiCartas(jogadores, njogadores, baralho);    
    while(trincas < 3){
        printf("\n\tSua mão:\n");
        mostraMao(jogadores[0].hand, NCARTASMAO); //Printo a mão do player 1 e uma carta voltada para baixo logo abaixo.
        printf("\n");  
        mostraCarta(cardsVec, 2); 
        
         
           for(i = 0; i < njogadores; i++){  
               
               trincaVec1 = sequenciaMao(jogadores[i].hand, seqMatrix[i][0], seqMatrix[i][1]); //Já verifico se há sequências.
               trincaVec2 = mesmoValorMao(jogadores[i].hand, eqValorMatrix[i][0], eqValorMatrix[i][1]); //Já verifico se há três cartas de mesmo valor.
               //Caso haja trinca, aumento o número de trincas do jogador i.
               if(trincaVec1[0] + 1) trincasGamer[i]++; 
               if(trincaVec2[0] + 1) trincasGamer[i]++;
               
               /*
                Abaixo, caso seqMatrix[i][0][0] == -1, significa que, para o player i, não existe nenhuma sequência em sua mão.
                Então, a terceira dimensão da matriz receberá os valores das entradas do vetor trincaVec, o qual recebe da função sequenciaMao()
                as posições das cartas que participam da sequência (ou recebe -1 e cotinua igual).
                Há três testes abaixo porque, caso já haja uma sequência, então, movemos uma posição em relação à segunda dimensão da matriz.
               */
                 
               if(!(seqMatrix[i][0][0] + 1)) for(k = 0; k < 3; k++) seqMatrix[i][0][k] = trincaVec1[k]; //Havendo 0 sequências.
               else if(!(seqMatrix[i][1][0] + 1)) for(k = 0; k < 3; k++) seqMatrix[i][1][k] = trincaVec1[k]; //Havendo já 1 sequência.
               else if(!(seqMatrix[i][2][0] + 1)) for(k = 0; k < 3; k++) seqMatrix[i][2][k] = trincaVec1[k]; //Havendo 2 sequências.
               
               //Analogamente, faço os mesmos testes para trincas de valores iguais.            
               if(!(eqValorMatrix[i][0][0] + 1)) for(k = 0; k < 3; k++) eqValorMatrix[i][0][k] = trincaVec2[k];              
               else if(!(eqValorMatrix[i][1][0] + 1)) for(k = 0; k < 3; k++) eqValorMatrix[i][1][k] = trincaVec2[k];
               else if(!(eqValorMatrix[i][2][0] + 1)) for(k = 0; k < 3; k++) eqValorMatrix[i][2][k] = trincaVec2[k];
               
               if(trincasGamer[i] == 3){
                  trincas = 3; //Caso algum jogador tenha três trincas, quebro o while loop.
                  break; //Usar break não é muito bom, mas aqui é necessário para que o valor de i seja mantido e eu possa utilizá-lo para me referir ao jogador ganhador da partida adiante.
               } 
            
            //Printo em tela todas as trincas que o player 1 tem.      
            printf("\n \tSuas trincas: \n\n");
            printf("\tSequências: ");
            printf("\t\tCartas de mesmo valor \n\n");
           
            for(j = 0; j < 3; j++){
            printf("\t");
                for(k = 0; k < 3; k++){
                    if(seqMatrix[0][j][k] + 1) printf("%d \t", seqMatrix[0][j][k] + 1);  
                    else printf("- \t");
                }
            
            for(k = 0; k < 3; k++){
                if(eqValorMatrix[0][j][k] + 1) printf("%d \t", eqValorMatrix[0][j][k] + 1);
                else printf("- \t");
            }
            printf("\n");
         }   
        
         printf("\n");
         
         if(!rodadas){ //Na primeira rodada, o player 1 não pode escolher entre comprar do deck ou do morto.
             comprarCarta(baralho, morto, &jogadores[i].hand, i);
             rodadas++; //Não preciso iterar depois.
         }else if(!i){ //Nas próximas rodadas, é possível escolher entre comprar do deck ou do morto.
             printf("Gostaria de comprar do deck(1) ou do morto(2)?");
             scanf("%d", &acao);
             if(acao == 1) comprarCarta(baralho, morto, &jogadores[i].hand, i);
             else pegardoMorto(morto, &jogadores[i].hand); //Mesmo que o player 1 não entre com 2, ele vai comprar do morto igual.           
         }else comprarCarta(baralho, morto, &jogadores[i].hand, i); //Quem não for o player 1(i = 0) não pode escolher nada (cuidado com a Skynet). 
                                          
           }//Termina o for loop.  
           cardsVec[1] = UltimaCarta(morto); //A segunda posição do vetor cardsVec finalmente corresponde à última carta do morto.  
    }//Termina o while loop.
    
    printf("%s É O(A) VENCEDO(A)!\n", jogadores[i].nome);  
    
    printf("\n");
    
    //Printo mais uma vez as trincas do player 1, pois, anteriormente, estas eram printadas dentro de um loop que foi quebrado.
    printf("\n \tSuas trincas: \n\n");
            printf("\tSequências: ");
            printf("\t\tCartas de mesmo valor \n\n");
            
    for(j = 0; j < 3; j++){
            printf("\t");
                for(k = 0; k < 3; k++){
                    if(seqMatrix[0][j][k] + 1) printf("%d \t", seqMatrix[0][j][k] + 1);  
                    else printf("- \t");
                }
            
            for(k = 0; k < 3; k++){
                if(eqValorMatrix[0][j][k] + 1) printf("%d \t", eqValorMatrix[0][j][k] + 1);
                else printf("- \t");
            }
            printf("\n");
         }   
        
         printf("\n");  

}
//------------------------------------------------------- 

int main(){

int njogadores;

// Eu posso criar os jogadores da mesma forma que criei o deck, dentro da função.
// Passaria para a função game(), então, somente o número de jogadores. Mas, quero fazer diferente.
// Apenas como exercício, vou criar no main o vetor de jogadores e passar para a função que cria um jogador
// cada elemento desse vetor de jogadores.

player jogadores[4];

//Ainda tenho problemas na alocação de memória caso crie um vetor para o número de jogadores com alocação dinâmica.
//Mas, na prática, um jogo não funciona assim: o número máximo de jpgadores é bem determinado desde o início.


    do{
        printf("Escreva o número de jogadores (<= 4): \n");
        scanf(" %d", &njogadores);
        if(njogadores < 1 || njogadores > 4 ) printf("Verifique o número máximo de jogadores.\n");
    }while(njogadores < 1 || njogadores > 4);

    for(int i = 0; i < njogadores;i++) newGamer(&jogadores[i], i);

game(jogadores, njogadores);  
   

    //Testes:
    //for(int i = 0; i < size(baralho); i++) printf("%d, %d, %s\n", i + 1, baralho->pilha[i].valor, baralho->pilha[i].naipe);
    //printf("\n");
    //printf("%d\n", size(baralho));
    
    //printf("%d\n", size(baralho));
    //for(int i = 0; i < size(baralho); i++) printf("%d, %d, %s\n", i + 1, baralho->pilha[i].valor, baralho->pilha[i].naipe);

    // Printando a última carta adicionada à pilha de cartas:
    //printf("%d \n", UltimaCarta(baralho).valor);

    // Printando todas as cartas da pilha.
    // Espera-se que o valor da última coincida com o que foi printado acima.
    //for(int i = 0; i < baralho->tammax; i++) printf("%d, %d, %s\n", i + 1, baralho->pilha[i].valor, baralho->pilha[i].naipe);

    // Printando o topo da pilha.
    // Como criei a pilha com o topo sendo -1, espera-se que seja printado NCARTAS - 1:  
    //printf("%d\n", baralho->topo);


return 0;
}
