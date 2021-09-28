#include<ncurses.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int main(){

time_t t;

	srand((unsigned) time(&t));
	
	
	initscr(); //Before you use any other curses routines, the initscr() routine must be called first. 
	keypad(stdscr, TRUE);

	 // don't interrupt for user input:
	noecho(); //To suppress the automatic echoing of typed characters, you need to call (Não printa na porra da tela.)
	cbreak(); //To disable the buffering of typed characters by the TTY driver and get a character-at-a-time input, you need to call 
	timeout(50); //É ISTO que faz com que o programa continue rodando enquanto o usuário entra com caracter.


int altura, largura, inicio_x, inicio_y;
char saida = 'a', ch = 'a';
int i = 0, v;
int posicao_blocos[100][20];


altura = 20;
largura = 50;
inicio_x = inicio_y = 10;

WINDOW * janela = newwin(altura, largura, inicio_x, inicio_y); //Parece Java. Gostei. Cria uma variável janela.
WINDOW * nave = newwin(4,4, 0, 0);

	
	curs_set(0);
	
	refresh();
	//Acima eu criei a janela. Aqui eu preencho as bordas dela:
	//box(janela, 46, 45); //Os números correspondem à tabela ASCII! usando (0,0), fica uma janela contínua.
	box(janela, 0, 0);
	//wborder(janela, 0, 0, 0, 0, 0, 0, 0, 0); //Posso usar isto também. Tanto faz.
	wrefresh(janela);
	//getch();
	
	int x = inicio_x + 1;
	int y = inicio_y + altura - 5;
	int tecla;
	int y_bloco;
	int k = 0;
	
	do{
	
	int teste = rand()%10;
	k = 0;
	saida = getch();
		
		if (teste == 1 || teste == 5 || teste == 7){	
			for(int i = 0; i < 20; i++){
				for(int j = 0; j < 100; j++){
					posicao_blocos[i][j] = rand()%50;
				}	
			}	
	
			for(int i = 2; i < 48; i++){
				for(int j = 2; j < 4; j++){
					if (posicao_blocos[j][i] == 5 || posicao_blocos[j][i] == 15){
						wmove(janela, j, i);
						waddch(janela, ACS_BLOCK);
						wrefresh(janela);
					}
				}	
	
			}
		}
	
		do{
		
		
			
			//getch();
			
			for(int i = 2; i < 48; i++){
				for(int j = 2; j < 4; j++){
					if(j+k < inicio_y + altura - 11){
						if (posicao_blocos[j][i] == 5 || posicao_blocos[j][i] == 15){
							wmove(janela, j+k, i);
							waddch(janela, ACS_BLOCK);
							wrefresh(janela);
						}
					}					
				}	
			}
			
			tecla = getch();
			
			switch(tecla){
				case KEY_RIGHT:
					if(x < inicio_x + largura - 10)	v = 3;
					else v = 0;
				break;
				case KEY_LEFT:
					if(x > inicio_x + 1) v = -3;
					else v = 0;
				break;
				case 'p': 
					tecla = 'a';
					while(tecla != 'p' && tecla != 'q') tecla = getch(); //Para pausar o jogo.
				default: //Uso o default pra que a base não continue se movendo enquanto o usuário não segurar o comando.
				v = 0;		
			}
		
			x += v;
			
			//box(janela, 0, 0); //tá mais barato construir essa porra de novo do que controlar até quando os blocos caem.
			//wrefresh(janela);
			//No fim, consegui controlar. Mas fica aí a opção.
		
			werase(nave);
			wrefresh(nave);
		
			mvwin(nave, y, x);
		
			box(nave, 0, 0);
			wrefresh(nave);
		
			for(int i = 2; i < 48; i++){
				for(int j = 2; j < 4; j++){
					if(j+k < inicio_y + altura - 11){
						if (posicao_blocos[j][i] == 5 || posicao_blocos[j][i] == 15){
							wattron(janela,A_INVIS);
							wmove(janela, j+k, i);
							waddch(janela, ACS_BLOCK);
							wattroff(janela, A_INVIS);
							wrefresh(janela);
						}					
					}						
				}	
			}
		
			k++;	
			//napms(50);				
					
		}while(k < 20 && tecla != 'q');
		
		
	}while(saida != 'q' && tecla != 'q');
	
	
	
	//getch();
	
	endwin();
	//nocbreak();


return 0;

}
