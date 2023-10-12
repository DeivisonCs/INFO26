#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 600

typedef struct Node_secundario{
    int key;
    int *next;
}s_Node;

typedef struct Node_principal{
    int key;
    int *prev;
    int *next;
    s_Node *sub;
}p_Node;

typedef struct head{
    p_Node *head;
}My_list;

typedef struct head{
    s_Node *head;
}My_sub_list;

void init(My_list *p);

int main(){
    FILE *arq_in; arq_in = fopen("L1Q3.in", "r");
    FILE *arq_out; arq_out = fopen("L1Q3.out", "w");
    char *token;

    My_list *p_List = malloc(sizeof(p_List));
    p_Node *main_Node;

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de Entrada Não Encontrado!");
        return EXIT_FAILURE;
    }

    init(p_List);

    char *line = malloc(MAX_LINE * sizeof(char));

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, " ");

        while(token != NULL)
        {
            
        }

    }while(!feof(arq_in));

    fclose(arq_in);
    fclose(arq_out);

    return EXIT_SUCCESS;
}

void init(My_list *p){
    p->head=NULL;
}