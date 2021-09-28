#ifndef _jogo_H_
#define _jogo_H_

#include<ncurses.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define NLINHAS 5
#define NCOLUNAS 9
#define DIMENSAO_MENU 3
#define NCORES 4
#define NNIVEIS 3
#define TAMANHO_NOME_ARQUIVO_NIVEL 7

int ncomb = 0;
int score = 0;

typedef struct{

WINDOW *armacao;
WINDOW *subarmacao;
int estado_ativacao;
int subestado_ativacao;
int cor;

}GRADE;


void criaCenario(WINDOW *janela, WINDOW *janela2, int *altura, int *largura);
void criaMenu(GRADE *menu, char linha[DIMENSAO_MENU][100]);
void escreveMenu(GRADE *menu, int altura, int largura, char linha_arquivo_menu[DIMENSAO_MENU][10], int i);
int Menu(GRADE *menu);
void deletaMenu(GRADE *menu);
void preencheTabuleiro(GRADE tabuleiro[NCOLUNAS][NLINHAS], int altura, int largura);
void Game(WINDOW *janela_maior, GRADE tabuleiro[NCOLUNAS][NLINHAS], int altura_cenario, int largura_cenario);
void pintaTabuleiro(GRADE tabuleiro[NCOLUNAS][NLINHAS]);
void deletaTabuleiro(GRADE tabuleiro[NCOLUNAS][NLINHAS]);
void limpaMemoriaTabuleiro(GRADE tabuleiro[NCOLUNAS][NLINHAS]);
void trocaCores(GRADE tabuleiro[NCOLUNAS][NLINHAS], int j, int Y, int i, int X);
void verificaCombinacao(GRADE tabuleiro[NCOLUNAS][NLINHAS], int altura_cenario, int largura_cenario);
void criaArquivoNivel(int level, int ncomb);
void criaNivel();


#endif
