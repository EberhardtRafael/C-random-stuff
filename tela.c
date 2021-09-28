#include<ncurses.h>
#include<math.h>
#include<stdlib.h>

int main(){

	initscr(); //Before you use any other curses routines, the initscr() routine must be called first. 
	keypad(stdscr, TRUE);

	 // don't interrupt for user input:
	noecho(); //To suppress the automatic echoing of typed characters, you need to call (Não printa na porra da tela.)
	cbreak(); //To disable the buffering of typed characters by the TTY driver and get a character-at-a-time input, you need to call 
	timeout(10); //É ISTO que faz com que o programa continue rodando enquanto o usuário entra com caracter.


	curs_set(0);
	
int altura, largura, inicio_x, inicio_y;
float x_bola, y_bola;
float vx_bola, vy_bola, deltax, deltay;
char saida = 'a';
char ch = 'a';
int i = 0;

x_bola = 1;
y_bola = 1;
vx_bola = 1.5;
vy_bola = 1.5;


altura = 20;
largura = 50;
inicio_x = inicio_y = 10;

WINDOW * janela = newwin(altura, largura, inicio_x, inicio_y); //Parece Java. Gostei. Cria uma variável janela.



	refresh(); //
	
	///if(getch() == KEY_UP) printw("UP");
	
	//Acima eu criei a janela. Aqui eu preencho as bordas dela:
	//box(janela, 46, 45); //Os números correspondem à tabela ASCII! usando (0,0), fica uma janela contínua.
	box(janela, 0, 0);
	//wprintw(janela, "a");
	//wborder(janela, 0, 0, 0, 0, 0, 0, 0, 0); //Posso usar isto também. Tanto faz.
	//mvwprintw(janela, 1, 1, "cu");
	wrefresh(janela);
	
	mvwprintw(janela, y_bola, x_bola, "O");
	wrefresh(janela);
	
	//mvwprintw(janela, 3, 3, "cu2");
	//wrefresh(janela);
	
	for(int i = 0; i < 20; i++){
		wmove(janela, rand()%18 + 2, rand()%48 + 2);
		waddch(janela, ACS_BLOCK);
		wrefresh(janela);	
	}	
	
		////if(getch() == KEY_UP) printw("UP");
			
	do{
		
		saida = getch();
		napms(100);

		
		if(saida == KEY_UP){
		wprintw(janela, "UP");
		napms(100);
		} 			
		//else if(saida == KEY_DOWN) wprintw(janela, "DOWN");
		//else if (saida == 'c') wprintw(janela, "CU");
		else if(saida == 'p'){
			saida = 'a';
			while(saida != 'p' && saida != 'q' ){
				saida = getch();
			}
		
		}
		
		///	if(getch() == KEY_UP) printw("UP");
		deltax = vx_bola;
		deltay = vy_bola;
		
		//mvwprintw(janela, i, i, "O");
		wmove(janela, y_bola, x_bola);		
		waddch(janela, 'O');
		
		//wrefresh(janela);
						
		wattron(janela,A_INVIS);
		wmove(janela, y_bola, x_bola);		
		waddch(janela, 'O');
		wattroff(janela, A_INVIS);
		
		//wrefresh(janela);
	
		if(vx_bola > 0 && x_bola >= largura - 4) vx_bola = (-1)*vx_bola;
		if(vy_bola > 0 && y_bola >= altura - 3) vy_bola = (-1)*vy_bola; 
		if(vx_bola < 0 && x_bola <= 3) vx_bola = (-1)*vx_bola;
		if(vy_bola < 0 && y_bola <= 3) vy_bola = (-1)*vy_bola; 
		//printw("x: %f, y: %f, vx: %f, vy: %f", x_bola, y_bola, vx_bola, vy_bola);

		
		x_bola = x_bola + deltax;
		y_bola = y_bola + deltay;
		
		wmove(janela, y_bola, x_bola);		
		waddch(janela, 'O');
		wrefresh(janela);
		
		//napms(10);
		//wrefresh(janela);
		//getch();
		i++;
		
		/*switch(saida){
			case KEY_UP:
				wprintw(janela, "UP");
			case KEY_DOWN:
				wprintw(janela, "UP");
				
		
		}*/
		
	}while(saida != 'q');
	
	
	getch();
	
	endwin();
	//nocbreak();





return 0;

}
