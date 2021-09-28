#include "jogo.h"

//----------------------------------------------------------------------------------------------------------------------------------------
void Game(WINDOW *janela_maior, GRADE tabuleiro[NCOLUNAS][NLINHAS], int altura_cenario, int largura_cenario){

int i, j, tecla_entrada, a_foi_clicado = 0, subestado_ativado_Y, subestado_ativado_X;
int nivel = 0;

	for(j = 0; j < NLINHAS; j++) 
		for(i = 0; i < NCOLUNAS; i++) tabuleiro[i][j].estado_ativacao = 0;
		
	for(j = 0; j < NLINHAS; j++) 
		for(i = 0; i < NCOLUNAS; i++) tabuleiro[i][j].subestado_ativacao = 0;
	
	i = 0;
	j = 0; //Esqueci de zerar essa merda de novo e demorei uma caralha pra descobrir!
			
	tabuleiro[0][0].estado_ativacao = 1;
	
do{	
	ncomb = 0;
	refresh();
	do{
		
		mvprintw(5, 10, "NIVEL: %d \0", nivel + 1);
		refresh();
		mvprintw(8, 10, "Combinacoes: %d \0", ncomb);		
		refresh();
		mvprintw(5, 20, "Score: %d  \0", score);
		refresh();
			
		preencheTabuleiro(tabuleiro, altura_cenario, largura_cenario);
		
		tecla_entrada = getch();
		
		switch(tecla_entrada){
			case KEY_UP:
				tabuleiro[j][i].estado_ativacao = 0;
				if(i > 0) i--; 
				tabuleiro[j][i].estado_ativacao = 1;
			break;
			case KEY_DOWN:
				tabuleiro[j][i].estado_ativacao = 0;
				if(i < 4) i++; 
				tabuleiro[j][i].estado_ativacao = 1;
			break;
			case KEY_RIGHT:
				tabuleiro[j][i].estado_ativacao = 0;
				if(j < 8) j++; 
				tabuleiro[j][i].estado_ativacao = 1;
			break;
			case KEY_LEFT:
				tabuleiro[j][i].estado_ativacao = 0;
				if(j > 0) j--; 
				tabuleiro[j][i].estado_ativacao = 1;
			break;
			case 'a': 
				if(tabuleiro[j][i].subestado_ativacao == 0 && a_foi_clicado == 0){
					tabuleiro[j][i].subestado_ativacao = 1;
					subestado_ativado_X = i;
					subestado_ativado_Y = j;
					a_foi_clicado++;
				}else if(tabuleiro[j][i].subestado_ativacao == 0){						
					tabuleiro[j][i].subestado_ativacao = 1;
					a_foi_clicado++;					
				}else{
					tabuleiro[j][i].subestado_ativacao = 0;
					a_foi_clicado--;
				} 					
			break;
			case 'p': 
				tecla_entrada = 'm';
				while(tecla_entrada != 'p' && tecla_entrada != 'q') tecla_entrada = getch(); //Para pausar o jogo.
			break;												
		}	
		
		if(a_foi_clicado == 2){
			trocaCores(tabuleiro, j, subestado_ativado_Y, i, subestado_ativado_X);
			a_foi_clicado = 0;
		}	
		
		limpaMemoriaTabuleiro(tabuleiro);		
		
	}while(tecla_entrada != 'q' && ncomb < 10 + nivel*5);
	
	deletaTabuleiro(tabuleiro);
	refresh();
	
nivel ++;	
}while(tecla_entrada != 'q' && nivel < NNIVEIS);
	
}

//----------------------------------------------------------------------------------------------------------------------------------------
void animaQuadros(){

//Resolver este pepino!

}

//----------------------------------------------------------------------------------------------------------------------------------------
void verificaCombinacao(GRADE tabuleiro[NCOLUNAS][NLINHAS], int altura_cenario, int largura_cenario){

int i, j, k, l;
time_t medida1, medida2;

WINDOW *mascara[NCOLUNAS][NLINHAS];


int alt = altura_cenario/(2*NLINHAS);
int larg = largura_cenario/(2*NCOLUNAS);

	for(j = 0; j < NLINHAS; j++) 
		for(i = 0; i < NCOLUNAS; i++){
			if(tabuleiro[i][j].cor == tabuleiro[i + 1][j].cor && tabuleiro[i - 1][j].cor == tabuleiro[i][j].cor){
				
				//for(l = 0; l <= j; l++)
					for(k = i - 1; k <= i + 1; k++){
						mascara[k][j] = newwin(alt, larg, altura_cenario/4 + 1 + j*alt, largura_cenario/4 + 3 + k*larg);
						box(mascara[k][j], 0, 0);
						wrefresh(mascara[k][j]);
						ncomb++;
						score+= 10;
					}
					
				medida1 = time(NULL);
				do medida2 = time(NULL);
				while(medida2 - medida1 < 0.009);
				
				for(k = i -1; k <= i + 1; k++) tabuleiro[k][j].cor = rand()%NCORES +1;
				
				//for(k = 0; k < 2; k++) tabuleiro[k][j].cor = tabuleiro[i][k-1].cor;	
				
				mvprintw(8, 10, "Combinacoes: %d", ncomb);
				refresh();		
								
				preencheTabuleiro(tabuleiro, altura_cenario, largura_cenario);
				
			}						
		}

}


//----------------------------------------------------------------------------------------------------------------------------------------
void trocaCores(GRADE tabuleiro[NCOLUNAS][NLINHAS], int j, int Y, int i, int X){

int n;
	
	n = tabuleiro[j][i].cor;
	tabuleiro[j][i].cor = tabuleiro[Y][X].cor;
	tabuleiro[Y][X].cor = n;
	
	for(j = 0; j < NLINHAS; j++) 
		for(i = 0; i < NCOLUNAS; i++) tabuleiro[i][j].subestado_ativacao = 0;
				
}

//----------------------------------------------------------------------------------------------------------------------------------------
void criaNivel(){
	
int i, numero_de_combinacoes;
	
		for(i = 0; i < NNIVEIS; i++){
			numero_de_combinacoes = 10 + 5*i;
			criaArquivoNivel(i, numero_de_combinacoes);
		
		} 

}

//----------------------------------------------------------------------------------------------------------------------------------------
void criaArquivoNivel(int level, int ncomb){

int i, j;
char nome_arquivo[TAMANHO_NOME_ARQUIVO_NIVEL];
FILE *nivel;

		
	sprintf(nome_arquivo, "nivel%d", level); //Serve para concatenar string e inteiro.
	
	nivel = fopen(nome_arquivo, "w");
	
	if(nivel == NULL) printf("Erro ao abrir o arquivo!");
	else{
		fprintf(nivel, "%d\n", ncomb);
		
		for(j = 0; j < NLINHAS; j++){ 
			for(i = 0; i < NCOLUNAS; i++) 
				if(fprintf(nivel, "%d\t", rand()%NCORES + i) > 0);
					else printf("Erro na escrita do arquivo!\n");
		fprintf(nivel, "\n");
				
		}
		
		fclose(nivel);		
	}
		
}



//----------------------------------------------------------------------------------------------------------------------------------------
void pintaTabuleiro(GRADE tabuleiro[NCOLUNAS][NLINHAS]){

int i, j;	
	
	
	for(j = 0; j < NLINHAS; j++) 
		for(i = 0; i < NCOLUNAS; i++) tabuleiro[i][j].cor = rand()%NCORES +1;

}

//----------------------------------------------------------------------------------------------------------------------------------------
void preencheTabuleiro(GRADE tabuleiro[NCOLUNAS][NLINHAS], int altura, int largura){

int i, j, k, Y_inicial, X_inicial;
int alt, larg;

	alt = altura/(2*NLINHAS);
	larg = largura/(2*NCOLUNAS);
	
	Y_inicial = altura/4 + 1;
	X_inicial = largura/4 + 3;
	
	start_color();	
	
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, 1, 1);
	init_pair(2, 3, 3);
	init_pair(3, 4, 4);
	init_pair(4, 6, 6);
	
	//for(k = 0; k < NLINHAS; k++)
	for(j = 0; j < NLINHAS; j++) //i e j ficam "trocados" porque a coordenada altura aparece primeiro na função newwin().
		for(i = 0; i < NCOLUNAS; i++){
			if(tabuleiro[i][j].estado_ativacao == 1){				
				tabuleiro[i][j].armacao = newwin(alt, larg, Y_inicial + j*alt /*+ k*alt*/, X_inicial + i*larg);
					if(tabuleiro[i][j].subestado_ativacao == 1)
						tabuleiro[i][j].subarmacao = derwin(tabuleiro[i][j].armacao, alt -2, larg - 2, 0, 0);
					else{
						tabuleiro[i][j].subarmacao = derwin(tabuleiro[i][j].armacao, alt -2, larg - 2, 1, 1);	 	
						wbkgd(tabuleiro[i][j].armacao, COLOR_PAIR(tabuleiro[i][j].cor));	
					}									
				wbkgd(tabuleiro[i][j].subarmacao, COLOR_PAIR(tabuleiro[i][j].cor));
				wattron(tabuleiro[i][j].armacao, A_BOLD);					
				box(tabuleiro[i][j].armacao, 0, 0);
				wrefresh(tabuleiro[i][j].armacao);
				box(tabuleiro[i][j].subarmacao, 0, 0);
				wrefresh(tabuleiro[i][j].subarmacao);			
				wattroff(tabuleiro[i][j].armacao, A_BOLD);

			}else{	
				tabuleiro[i][j].armacao = newwin(alt, larg, Y_inicial + j*alt /*+ k*alt*/, X_inicial + i*larg);
				
				if(tabuleiro[i][j].subestado_ativacao == 1)
					tabuleiro[i][j].subarmacao = derwin(tabuleiro[i][j].armacao, alt -2, larg - 2, 0, 0);
				else
					tabuleiro[i][j].subarmacao = derwin(tabuleiro[i][j].armacao, alt - 2, larg - 2, 1, 1);
					
				wbkgd(tabuleiro[i][j].subarmacao, COLOR_PAIR(tabuleiro[i][j].cor));
				box(tabuleiro[i][j].armacao, 0, 0);
				wrefresh(tabuleiro[i][j].armacao);
				box(tabuleiro[i][j].subarmacao, 0, 0);
				wrefresh(tabuleiro[i][j].subarmacao);			
			}			
		}
	
	verificaCombinacao(tabuleiro, altura, largura);
}

//----------------------------------------------------------------------------------------------------------------------------------------
void limpaMemoriaTabuleiro(GRADE tabuleiro[NCOLUNAS][NLINHAS]){

int i, j;

	for(j = 0; j < NLINHAS; j++) 
		for(i = 0; i < NCOLUNAS; i++){
			delwin(tabuleiro[i][j].armacao);
			wrefresh(tabuleiro[i][j].armacao);		
		}
}

//----------------------------------------------------------------------------------------------------------------------------------------
void deletaTabuleiro(GRADE tabuleiro[NCOLUNAS][NLINHAS]){

int i, j;

	for(j = 0; j < NLINHAS; j++) 
		for(i = 0; i < NCOLUNAS; i++){
			werase(tabuleiro[i][j].armacao);
			wrefresh(tabuleiro[i][j].armacao);		
		}
}

//----------------------------------------------------------------------------------------------------------------------------------------
void deletaMenu(GRADE *menu){

int i;

	for(i = 0; i < DIMENSAO_MENU; i++){
		werase(menu[i].armacao);
		wrefresh(menu[i].armacao);
	}
	
}

//----------------------------------------------------------------------------------------------------------------------------------------
void leMenu(char linha_arquivo_menu[DIMENSAO_MENU][100]){

int i;

	FILE *arquivo_menu;
	
	arquivo_menu = fopen("arquivo_menu", "r");
	
		if(arquivo_menu == NULL) printf("Erro ao abrir o arquivo!");
		else	
			for(i = 0; i < DIMENSAO_MENU; i++) fscanf(arquivo_menu, "%s", linha_arquivo_menu[i]);			
			
		fclose(arquivo_menu);
}

//----------------------------------------------------------------------------------------------------------------------------------------
int Menu(GRADE *menu){

char linha_arquivo_menu[DIMENSAO_MENU][100];
char saida = 'a';
int tecla_entrada, i, k = 0;

	leMenu(linha_arquivo_menu);
	
	for(i = 0; i < DIMENSAO_MENU; i++)
			menu[i].estado_ativacao = 0;
					
	menu[0].estado_ativacao = 1;	

	do{
		criaMenu(menu, linha_arquivo_menu);
			
		tecla_entrada = getch();
		
		switch(tecla_entrada){
			case KEY_UP:
				menu[k].estado_ativacao = 0;
				if(k == 1 || k == 2) k--; //Colocando pra cima, levo pro componente anteior do vetor!
				menu[k].estado_ativacao = 1;
			break;
			case KEY_DOWN:
				menu[k].estado_ativacao = 0;
				if(k == 0 || k == 1) k++; 
				menu[k].estado_ativacao = 1;
			break;		
		}			
	
	}while(tecla_entrada != saida);
	
	deletaMenu(menu); //Deleta o Menu para poder começar o jogo.	
	
	return k;

}

//----------------------------------------------------------------------------------------------------------------------------------------
void criaMenu(GRADE *menu, char linha[DIMENSAO_MENU][100]){

int i, largura_cenario = 0, altura_cenario = 0;
int largura_janela, altura_janela, X_janela_inicial, Y_janela_inicial;	
	
	curs_set(0); //Torna cursor invisível.

	getmaxyx(stdscr, altura_cenario, largura_cenario); //Coleta as dimensões da WINDOW entrada.
	
	largura_janela = largura_cenario/3;
	altura_janela = altura_cenario/9;
	X_janela_inicial = largura_cenario/3;
	Y_janela_inicial = altura_cenario/3;
	
	for(i = 0; i < DIMENSAO_MENU; i++){
		if(menu[i].estado_ativacao == 1){
			menu[i].armacao = newwin(altura_janela, largura_janela, Y_janela_inicial + i*altura_janela, X_janela_inicial);
			wattron(menu[i].armacao,A_BOLD);	
			box(menu[i].armacao, 0, 0);
			mvwprintw(menu[i].armacao, altura_janela/2, largura_janela/2 - strlen(linha[i])/2, "%s" , linha[i]);
			wattroff(menu[i].armacao, A_BOLD);
			wrefresh(menu[i].armacao);						
		}else{
			menu[i].armacao = newwin(altura_janela, largura_janela, Y_janela_inicial + i*altura_janela, X_janela_inicial);
			box(menu[i].armacao, 0, 0);
			mvwprintw(menu[i].armacao, altura_janela/2, largura_janela/2 - strlen(linha[i])/2, "%s" , linha[i]);
			wrefresh(menu[i].armacao);
		}		
	}	
	
	refresh();				
		
}

//----------------------------------------------------------------------------------------------------------------------------------------
//Eu sei que estou redefinindo uma função que já existe quase como ela já é, mas não quero ter que ficar escrevendo refresh() o tempo todo.
//void criaBox(WINDOW *janela, int largura, int altura, int y_inicial){
void criaCenario(WINDOW *janela_maior, WINDOW *janela_menor, int *altura, int *largura){

int alt, larg;

	janela_maior = newwin(0, 0, 0, 0); //Já cria full screen.
	refresh();
	box(janela_maior, 0, 0);
	wrefresh(janela_maior);
	
	getmaxyx(janela_maior, alt, larg);
	
	if(alt%2 == 0) *altura = alt;
	else *altura = alt + 1;

	if(larg%2 == 0) *largura = larg;
	else *largura = larg + 1;
	
	//A função preencheTabuleiro depende destes dados também.
	janela_menor = subwin(janela_maior, *altura/2 + 2, *largura/2, *altura/4, *largura/4); 
	refresh();
	box(janela_menor, 0, 0);
	wrefresh(janela_menor);
	
}
