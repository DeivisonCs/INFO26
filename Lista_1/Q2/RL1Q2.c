/*
    gcc RL1Q2.c -o q2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200
#define MAX_CHAR 50
#define MAX_LINE 600
const char *Separador = " ";

typedef struct stack{
    char name[MAX][MAX_CHAR];  //name[posição][quantidade_letras]
    int qtd;
}Stack;

void sort_stack(Stack *p, Stack *aux);
int sort_string(Stack *p, int range);
void push(Stack *p, char *token);
void pop(Stack *p, Stack *aux);
void remove_fgets(Stack *p);

int main(){
    FILE *arq_in; arq_in = fopen("L1Q2.in", "r");
    FILE *arq_out; arq_out = fopen("L1Q2.out", "w");
    Stack stack;
    Stack aux;
    char *token;

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de Entrada Não Encontrado!");
        return EXIT_FAILURE;
    }

    char *line = malloc(MAX_LINE * sizeof(char));

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, Separador);

        aux.qtd=0;
        stack.qtd=0;
        while(token!=NULL){
            push(&aux, token);
            token = strtok(NULL, Separador);
        }

        sort_stack(&stack, &aux);

    }while(!feof(arq_in));

    free(line);
    fclose(arq_in);
    fclose(arq_out);
}

void push(Stack *p, char *token){
    FILE *arq_out; arq_out = fopen("L1Q2.out", "a");

    if(p->qtd == MAX-1){
        fprintf(arq_out, "Stack Overflow");
        return;
    }

    strcpy(p->name[p->qtd], token);
    p->qtd++;

    fclose(arq_out);
}

void pop(Stack *p, Stack *aux){
    FILE *arq_out; arq_out = fopen("L1Q2.out", "a");

    if(p->qtd == 0){
        fprintf(arq_out, "Stack Underflow");
        return;
    }
    
    strcpy(aux->name[aux->qtd] , p->name[p->qtd]);
    p->qtd--;
    aux->qtd++;

    fclose(arq_out);
}

int sort_string(Stack *p, int range){
    int i, j, x;
    char sup[MAX_CHAR];
    int qtd_trocas=0;

    for(i=range, x=0; i>0; i--)
    {
        if(p->name[i][x] < p->name[i-1][x])
        {
            qtd_trocas++;
            x=0;
            strcpy(sup, p->name[i]);
            strcpy(p->name[i], p->name[i-1]);
            strcpy(p->name[i-1], sup);
        }
        else if(p->name[i][x] == p->name[i-1][x])
            if(p->name[i-1][x] != '\0' || p->name[i-2][x] != '\0'){
                i++;
                x++;
            }
    }

    return qtd_trocas;
}

void sort_stack(Stack *p, Stack *aux){
    FILE *arq_out; arq_out = fopen("L1Q2.out", "a");
    int i, trocas;
    char *sup;
    
    remove_fgets(aux);

    for(i=0; i<aux->qtd; i++)
    {
        strcpy(sup, aux->name[i]);
        push(p, sup);
        trocas = sort_string(p, i);
        // printf("%s\n", p->name[i]);
        if(trocas != 0)
        {
            fprintf(arq_out, "%dx-pop ", trocas);

            for(int j=i-trocas; j<=i; j++)
                fprintf(arq_out, "push-%s ", p->name[j]);
        }
        else if(i+1==aux->qtd)
            fprintf(arq_out, "push-%s", p->name[i]);
        else
            fprintf(arq_out, "push-%s ", p->name[i]);

    }

    fclose(arq_out);
}

void remove_fgets(Stack *p){
    int i;

    i = strlen(p->name[p->qtd-1]) -1;

    printf("\ni:%d\n", i);
    // printf("Antes\n");
    // printf("|%s|\n", p->name[p->qtd-1]);
    // printf("|%s||\n", p->name[p->qtd-1]);
    // printf("|%s|||\n", p->name[p->qtd-1]);

    if(p->name[p->qtd-1][i] == '\n')
        p->name[p->qtd-1][i] = '\0';

    // printf("\nDepois\n");
    // printf("|%s|||\n", p->name[p->qtd-1]);
}