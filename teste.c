#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

#define tolerancia 0.01


int main(){

char teste[10];
/*float x, numerador, denominador, soma = 0, termo, pot;
int sinal = 1;
int i = 0;

termo = 1;

	do{
		scanf("%f", &x);
			if(x < -1 || x > 1) printf("Entrada invalida \n");
			else{
				while(termo > tolerancia){
					//numerador = pow(2,2);
					pot = 2*i+1;
					numerador = pow(x,pot);
					denominador = (2*i+1)*(2*i+2);
					termo = numerador/denominador;
					soma += sinal*termo;
					sinal = (-1)*sinal;
					//printf("%f\n", soma);
					i++;					
				}
			
			}	
	}while(x < -1 || x > 1); 


 	printf("%f\n", soma - termo);*/
 	printf("Entre com um string qualquer.\n");
 	scanf("%s", teste);
 	printf("%s.\n", teste);

return 0;

}
