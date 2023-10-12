/*
    gcc RL1Q1.c -o q1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LINE_MAX 600
#define MAX_NUM 20
const char *Separador = " ";

typedef struct nums{
    int num[MAX_NUM];
    int qtd;
    int soma;
}Start;

int get_number(Start *p, int index, char *token);
void transfer_files(Start *p, int index, int lineOut);
void sum(Start *p, int index, int qtd);
void int_sort(Start *p, int index);
void sum_sort(Start *p, int index);

int main(){
    FILE *arq_in; arq_in = fopen("L1Q1.in", "r");
    FILE *arq_out; arq_out = fopen("L1Q1.out", "w");
    Start line_out[MAX_NUM]; int qtd;
    int ctrl, linhas=0;
    char *token;

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de Entrada Nao Encontrado!\n");
        return EXIT_FAILURE;
    }

    char *line = malloc(LINE_MAX * sizeof(char));

    do{
        fgets(line, LINE_MAX, arq_in);
        token = strtok(line, Separador);

        qtd = -1;
        line_out[0].soma = 0;
        line_out[0].qtd = 0;
        while(token != NULL)
        {
            ctrl = get_number(line_out, qtd, token);
            if(ctrl == EXIT_SUCCESS){
                line_out[qtd].soma += line_out[qtd].num[line_out[qtd].qtd];
                line_out[qtd].qtd++;
            }

            if(strcmp(token, "start") == 0){
                qtd++;
                line_out[qtd].qtd = 0;
                line_out[qtd].soma = 0;
            }

            token = strtok(NULL, Separador);
        }
        int_sort(line_out, qtd+1);
        sum_sort(line_out, qtd+1);
        transfer_files(line_out, qtd+1, linhas);
        linhas++;
    }while(!feof(arq_in));

    free(line);
    fclose(arq_in);
    fclose(arq_out);

    return EXIT_SUCCESS;
}

int get_number(Start *p, int index, char *token){

    if(strcmp(token, "start") == 0 || token == NULL)
        return EXIT_FAILURE;
    
    
    p[index].num[p[index].qtd] = atoi(token);

    return EXIT_SUCCESS;
}

void sum(Start *p, int index, int qtd){
    p[index].soma = 0;

    for(int j=0; j < qtd; j++)
        p[index].soma += p[index].num[j];
}

void int_sort(Start *p, int index){
    int i, j, k, menor;

    for(i=0; i<index; i++)
    {  
        for(j=0; j<p[i].qtd-1; j++)
        {
            menor = j;

            for(k=j+1; k<p[i].qtd; k++)
                if(p[i].num[k] < p[i].num[menor])
                    menor = k;

            if(p[i].num[menor] != p[i].num[j])
            {
                k = p[i].num[j];
                p[i].num[j] = p[i].num[menor];
                p[i].num[menor] = k;
            }
        }
    }
}

void sum_sort(Start *p, int index){
    int i, j, menor;
    Start aux;

    for(i=0; i<index; i++)
    {
        menor =  i;

        for(j=i+1; j<index; j++)
            if(p[j].soma < p[menor].soma)
                menor = j;

        if(p[menor].soma != p[i].soma)
        {
            aux = p[menor];
            p[menor] = p[i];
            p[i] = aux;
        }
    }
}

void transfer_files(Start *p, int index, int lineOut){
    FILE *arq_out; arq_out = fopen("L1Q1.out", "a");
    int i, j;

    if(lineOut != 0)
        fprintf(arq_out, "\n");

    for(i=0; i<index; i++)
    {
        if(i==0)
            fprintf(arq_out, "%s ", "start");
        else
            fprintf(arq_out, " %s ", "start");

        for(j=0; j<p[i].qtd; j++){
            fprintf(arq_out, "%d", p[i].num[j]);

            if(j+1 != p[i].qtd)
                fprintf(arq_out, " ");
        }
    }

    fclose(arq_out);
}
