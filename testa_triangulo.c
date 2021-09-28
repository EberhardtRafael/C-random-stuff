#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

char le_S_N(){

char saida;

    do{
        puts("Mais um (S/N)?");
        scanf(" %c", &saida);
        saida = tolower(saida);
        if (saida != 'n' && saida != 's') puts("Opcao invalida!");
    }while(saida != 'n' && saida != 's');

    return saida;
}


char triangulo(float a, float b, float c, float *area){

char tipo_triangulo;
//float area_triangulo;
float T;

    if(a < (b + c) && b < (a + c) && c < (a + b)){
        T = (a + b + c)/2;
        *area = sqrt(T*(T - a)*(T - b)*(T - c));
        if (a == b && b == c) tipo_triangulo = 'q';
        else if(a == b || a == c || b == c) tipo_triangulo = 'i';
        else tipo_triangulo = 'e';
    }else tipo_triangulo = 'n';

    return tipo_triangulo;

}


int main(){

float lado_a, lado_b, lado_c;
float area;
char tipo_triangulo, saida;

    do{
        puts("Entre com os valores dos lados do triangulo:");
        //scanf(" %f, %f, %f", &lado_a, &lado_b, &lado_c);
        scanf(" %f", &lado_a);
        scanf(" %f", &lado_b);
        scanf(" %f", &lado_c);

        tipo_triangulo = triangulo(lado_a, lado_b, lado_c, &area);

        //printf("%c\n", tipo_triangulo);

        if(tipo_triangulo == 'q') printf("O triangulo eh equilatero. Sua area eh: %f.\n", area);
        else if(tipo_triangulo == 'i') printf("O triangulo eh isosceles. Sua area eh: %f.\n", area);
        else if(tipo_triangulo == 'e') printf("O triangulo eh escaleno. Sua area eh: %f.\n", area);
        else printf("Nao eh triangulo.\n");

        saida = le_S_N();

    }while(saida != 'n');

return 0;

}
