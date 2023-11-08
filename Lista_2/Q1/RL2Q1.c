/*
    gcc RL2Q1.c -o q1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 600
#define separador " "

int main(){
    FILE *arq_in; arq_in = fopen("L2Q1.in", "r");
    FILE *arq_out; arq_out = fopen("L2Q1.out", "w");

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de entrada não encontrado!\n");

        fclose(arq_out);
        return EXIT_FAILURE;
    }
    
    char *token;
    char *line = malloc(MAX_LINE * sizeof(char)); 

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, separador);

        while(token != NULL)
        {   

            token = strtok(NULL, separador);
        }


    }while(!feof(arq_in));

    free(line);
    fclose(arq_in);
    fclose(arq_out);
    return EXIT_SUCCESS;
}