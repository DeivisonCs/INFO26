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

void sort_stack(Stack *p, Stack *aux, int lineQtd);
int sort_string(Stack *p, int range, char newElement[]);
void push(Stack *p, char *token);
void pop(Stack *p, Stack *aux);
void remove_fgets(Stack *p);
void print_stack(Stack *p);

int main(){
    FILE *arq_in; arq_in = fopen("L1Q2.in", "r");
    FILE *arq_out; arq_out = fopen("L1Q2.out", "w");
    Stack stack, aux;
    char *token;
    int lineQtd=0;

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

        sort_stack(&stack, &aux, lineQtd);
        lineQtd++;

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
    
    strcpy(aux->name[aux->qtd] , p->name[p->qtd-1]);
    // printf("aux: %s\n", aux->name[aux->qtd]);
    // printf("p: %s\n", p->name[p->qtd-1]);
    p->qtd--;
    aux->qtd++;

}

int sort_string(Stack *p, int range, char newElement[]){
    int i, j, x;
    char sup[MAX_CHAR];
    int qtd_trocas=0;
    Stack aux; aux.qtd = 0;

    for(i=range-1, x=0; i>=0; i--)
    {
        if(newElement[x] < p->name[i][x])
        {
            qtd_trocas++;
            x=0;
            // strcpy(sup, p->name[range]);
            // strcpy(p->name[range], p->name[i-1]);
            // strcpy(p->name[i-1], sup);
        }
        else if(newElement[x] == p->name[i][x])
            if(newElement[x] != '\0' || p->name[i][x] != '\0'){
                i++;
                x++;
            }
    }

    if(qtd_trocas!=0){
        for(i=0; i<qtd_trocas; i++)
            pop(p, &aux);

        //strcpy(sup, aux.name[0]);
        push(p, newElement);
        // print_stack(aux);
        // print_stack(*p);

        for(i=aux.qtd-1; i>=0; i--){
            strcpy(sup, aux.name[i]);
            push(p, sup);
        }
    }else push(p, newElement);

    return qtd_trocas;
}

void sort_stack(Stack *p, Stack *aux, int lineQtd){
    FILE *arq_out; arq_out = fopen("L1Q2.out", "a");
    int i, trocas;
    char sup[MAX_CHAR];
    
    remove_fgets(aux);

    if(lineQtd != 0)
        fprintf(arq_out, "\n");

    for(i=0; i<aux->qtd; i++)
    {
        strcpy(sup, aux->name[i]);
        trocas = sort_string(p, i, sup);
        if(trocas != 0)
        {
            fprintf(arq_out, "%dx-pop ", trocas);

            for(int j=i-trocas; j<=i; j++){
                fprintf(arq_out, "push-%s", p->name[j]);
                    if(j != i)
                        fprintf(arq_out, " ");
            }
        }
        else
            fprintf(arq_out, "push-%s", p->name[i]);

        if(i+1!=aux->qtd)
            fprintf(arq_out, " ");

    }
 
    fclose(arq_out);
}

void remove_fgets(Stack *p){
    int i;

    i = strlen(p->name[p->qtd-1]) -1;

    if(p->name[p->qtd-1][i] == '\n')
        p->name[p->qtd-1][i] = '\0';
}

void print_stack(Stack *p){
    printf("Qtd:%d\n", p->qtd);
    for(int i=p->qtd-1; i>=0; i--)
        printf("%s\n", p->name[i]);
    printf("\n");
}