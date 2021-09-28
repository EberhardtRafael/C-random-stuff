/*
Este programa gera uma matriz 4X4 e a preenche com n´=umeros aleatórios. Em jfdhskjibgfmçoknl
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int main(){

int matriz[4][4];
int i, j;
int maior[4], menor[4];

    srand(time(NULL));

    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            matriz[i][j] = rand() % 40 + 2;
            //matriz[i][j] = j;
        }
    }

     for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
     }

    printf("\n");

    for(j = 0; j < 4; j++){
        maior[j] = matriz[0][j];
        for(i = 0; i < 4; i++){
            if(matriz[i][j] > maior[j]){
                maior[j] = matriz[i][j];
            }
        }
    }

    for(i = 0; i < 4; i++){
        menor[i] = matriz[i][0];
        for(j = 0; j < 4; j++){
            if(matriz[i][j] < menor[i]) menor[i] = matriz[i][j];

        }

    }

               // printf("\n");
              //printf("%d ", maior[j]);
               //printf("%d ", menor[j]);

    printf("Arranjo com os maiores elementos de cada coluna:\n");
    for(i = 0; i < 4; i++) printf("%d ", maior[i]);
    printf("\n");
    printf("Arranjo com os menores elementos de cada linha:\n");
    for(i = 0; i < 4; i++) printf("%d ", menor[i]);


return 0;

}
