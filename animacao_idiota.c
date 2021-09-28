/*
Este programa serve para ilustrar algumas funcionalidades da biblioteca ncurses, que é uma versão para Linux mais poderosa que a coino do windows.
Ela serve para criar displays que podem servir, mais adiante, para criação d jogos simples. Será utilizada no trabalho final da cadeira de Algoritmos e Programação.

No momento de compilar, usar:  gcc tela.c -o tela -lncurses -lm, para poder acessar as funções da biblioteca - aqui,tanto a curses como a math.
*/




#include <stdio.h>
#include <ncurses.h>
#include <curses.h>
#include <math.h>

#define SAIDA 0

int main(){


char entrada = 'a';
int x, y, i;
 
	initscr(); //Cria uma tela.
	//raw();
	//keypad(stdscr, TRUE);
	cbreak(); //Permite sair da tela com ctrl+z, o que ajuda muito enquanto estiver testando coisas
	//printw("Teste");
	
	//getch(); //Serve para ler um caracter do teclado, mas, também serve para que o programa não rode antes de o usuário clicar qualquer coisa.
	//if(getch() == KEY_UP) printw("UP");
	
	//Abaixo, eu fiz uma idiotice para mostrar como é possível animar coisas utilizando essa biblioteca. Certamente existem outras formas, mas essa eu criei agora e funciona.
	
	//Bola 1________________________________________________________________________________________
	for(int j = 0; j < 50; j++){
		
		for(i = 0; i < 100; i++) mvprintw(11 + 8*sin(i), 11 + 8*cos(i) + j, "."); //Cria um desenho
		
		getch();
		
		for(i = 0; i < 100; i++){ //Cria o mesmo desenho, pr cima do anterior, ma invisível.
	
			attron(A_INVIS);
			mvprintw(11 + 8*sin(i), 11 + 8*cos(i) + j, ".");
			attroff(A_INVIS);		
		}
		
		getch();
		
		for(i = 0; i < 100; i++) mvprintw(11 + 8*sin(i), 11 + 8*cos(i) + j+1, "."); //Cria o mesmo desenho, visível, um pixel adiante.
	
	}
		//Repete a ação acima, só pra fazer um desenho idiota.
		
		//Bola 2________________________________________________________________________________________
	
		for(int j = 0; j < 50; j++){
		
		for(i = 0; i < 100; i++) mvprintw(31 + 8*sin(i), 11 + 8*cos(i) + j, ".");
		
		getch();
		
		for(i = 0; i < 100; i++){
	
			attron(A_INVIS);
			mvprintw(31 + 8*sin(i), 11 + 8*cos(i) + j, ".");
			attroff(A_INVIS);		
		}
		
		getch();
		
		for(i = 0; i < 100; i++) mvprintw(31 + 8*sin(i), 11 + 8*cos(i) + j+1, ".");
	
	}
	 
	//move(10, 20); //Isso apenas moveria o cursor para essa posição.
	getch();
	
	for (i = 0; i < 50; i++){
		mvprintw(15, 67+i, ".");
		getch();
		/*attron(A_STANDOUT);		
		mvprintw(15, 65+i, ".");
		attroff(A_STANDOUT);
		//getch();	
		mvprintw(15, 65+i, ".");
		//getch();*/
	} 
	
	for (i = 0; i < 50; i++){
		mvprintw(24, 65+i, ".");
		//getch();	
		
	} 
	
	for (i = 0; i < 1000; i++){
		mvprintw(20 + 4*sin(i/200.),120 + 4*cos(i/100.), "."); 
		//getch();	
	
	} 
	
	for(i = 0; i < 5; i++)
	
	getch();
	endwin(); //Sempre fechar a janela que criou!


return 0;

}
