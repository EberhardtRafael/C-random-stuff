#include "jogo_biblioteca.c"

int main(){


int altura_cenario, largura_cenario, tecla_entrada;
int i, j;
int selecao_menu;
GRADE menu[DIMENSAO_MENU];
GRADE tabuleiro[NCOLUNAS][NLINHAS]; //Verificar a questão de linhas e colunas. Tá tudo confuso isso.

WINDOW *cenario_maior, *cenario_menor;

time_t t;

	srand((unsigned) time(&t));
	
	initscr(); //Before you use any other curses routines, the initscr() routine must be called first. 
	keypad(stdscr, TRUE);

	 //Para poder entrar com informação do teclado sem parar o programa:
	noecho(); //Não printa na tela.
	cbreak(); //Faz com que uma letra seja interpretada de cada vez. 
	//timeout(50); //Continua rodando enquanto entra com caracter. 
	//Comentar timeout() para que a tela não desapareça.
	criaArquivoNivel(0, 10);
	//criaCenario(cenario_maior, cenario_menor, &altura_cenario, &largura_cenario);		
	do{
		criaCenario(cenario_maior, cenario_menor, &altura_cenario, &largura_cenario);		
		selecao_menu = Menu(menu);
		if(selecao_menu == 0){
			pintaTabuleiro(tabuleiro);
			Game(cenario_maior, tabuleiro, altura_cenario, largura_cenario);
			//delwin(cenario_menor);
		}else if (selecao_menu == 1){
			mvprintw(20, 70, "FAZER!!!!!");
			getch();			
		} 
		//delwin(cenario_menor);
	}while(selecao_menu != 2);
	
	
		
	endwin();	
	
	//nocbreak(); Se descomentar isso, caga o terminal depois que sai do jogo.

return 0;

}
