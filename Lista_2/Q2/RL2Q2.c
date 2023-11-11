/*
    gcc RL2Q2.c -o q2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 600
#define separador " "


typedef struct tree{
    struct tree *father;
    struct tree *next;
    struct tree *prev;
    int key;
}Node_tree;

typedef struct root{
    Node_tree *root;
}Root_tree;

int main(){
    FILE *arq_in; arq_in = fopen("L2Q2.in", "r");
    FILE *arq_out; arq_out = fopen("L2Q2.out", "w");

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de entrada não encontrado!");

        fclose(arq_in);
        fclose(arq_out);
    }

    char *token;
    char *line = malloc(MAX_LINE * sizeof(char));

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, separador);

        while(token != NULL)
        {
            printf("%d ", atoi(token));

            token = strtok(NULL, separador);
        }
        printf("\n");
    }while(!feof(arq_in));

    free(line);
    fclose(arq_in);
    fclose(arq_out);
}

/*Hint - Usar a função recursiva de imprimir para pegar a soma do nós em cada lado*/