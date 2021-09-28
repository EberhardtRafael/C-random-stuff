#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

#define MAX 40

void intersec(int vec_1[], int n_vec_1, int vec_2[], int n_vec_2, int vec_intersec[], int *n_intersec){

int i, j, k = 0;

    for(i = 0; i < n_vec_1; i++)
        for(j = 0; j < n_vec_2; j++)
                if(vec_1[i] == vec_2[j]){
                //printf("Teste\n");
                (*n_intersec)++;
                vec_intersec[k] = vec_1[i];
                k++;
           }
          // printf("%d\n", *n_intersec);
}

int main(){

int vec_1[MAX], vec_2[MAX], vec_intersec[MAX];
int n_1, n_2, n_intersec = 0;
int i;
//
int *point_intersec;

    puts("Entre com o nr. de elementos do primeiro vetor: ");
    scanf(" %d", &n_1);
    printf("Entre com os %d elementos do primeiro vetor: ", n_1);

    for(i = 0; i < n_1; i++) scanf("%d", &vec_1[i]);

    puts("");

    puts("Entre com o nr. de elementos do segundo vetor: ");
    scanf(" %d", &n_2);
    printf("Entre com os %d elementos do segundo vetor: ", n_2);

    for(i = 0; i < n_2; i++) scanf("%d", &vec_2[i]);

    puts("");

    //printf("%d\n", n_intersec);

    intersec(vec_1, n_1, vec_2, n_2, vec_intersec, &n_intersec);

    //printf("%d\n", n_intersec);

    if(n_intersec == 0) puts("Interseccao vazia.");
    else{
        puts("A intereseccao consiste em:");
        for(i = 0; i < n_intersec; i++) printf("%d ", vec_intersec[i]);
    }


return 0;

}
