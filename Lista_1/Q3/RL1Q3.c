/*
    gcc RL1Q3.c -o q3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 600
#define MAX_NUMS 100

typedef struct s_Node{
    float key;
    struct s_Node *next;
}s_Node;

typedef struct p_Node{
    float key;
    struct p_Node *prev;
    struct p_Node *next;
    s_Node *sub;
}p_Node;

typedef struct p_Head{
    p_Node *head;
}p_Head;

typedef struct s_head{
    s_Node *head;
}s_Head;

// typedef struct nums{
//     float p_num[MAX_NUMS];
//     int qtd_P_num;
//     float s_num[MAX_NUMS];
//     int qtd_S_num;
// }Nums;

void init(p_Head *p, p_Node *x);
void insert(p_Head *Head, p_Node *list);
void print_list(p_Head *Head);

int main(){
    FILE *arq_in; arq_in = fopen("L1Q3.in", "r");
    FILE *arq_out; arq_out = fopen("L1Q3.out", "w");
    char *token;
    int ctrl;


    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de Entrada Não Encontrado!");
        return EXIT_FAILURE;
    }

    p_Head *main_Head = malloc(sizeof(p_Head));
    p_Node *main_Node;
    init(main_Head, main_Node);

    char *line = malloc(MAX_LINE * sizeof(char));

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, " ");

        while(token != NULL)
        {
            if(strcmp(token, "LE") == 0){
                ctrl=0;
                token = strtok(NULL, " ");
                continue;
            }
            else if(strcmp(token, "LI") == 0){
                ctrl=1;
                token = strtok(NULL, " ");
                continue;
            }

            if(ctrl==0){
                main_Node = malloc(sizeof(p_Node));
                main_Node->key = atof(token);
                insert(main_Head, main_Node);
                // printf("key-out: %f\n", main_Node->key);
                // printf("here1\n");
            }

            token = strtok(NULL, " ");
        }
        print_list(main_Head);

    }while(!feof(arq_in));

    free(line);
    fclose(arq_in);
    fclose(arq_out);

    return EXIT_SUCCESS;
}

void init(p_Head *p, p_Node *x){
    p->head=NULL;
    // x->sub=NULL;
}

void insert(p_Head *H, p_Node *list){

    p_Node *x = H->head;
    while(x != NULL && x->key < list->key){
        x = x->next;
    }

    if(x == H->head){    //Caso seja no primeiro elemento 
        list->next = H->head;
        list->prev = NULL;
        H->head = list;
    }
    else{
        list->next = x;
        list->prev = x->prev;
    }
}

void print_list(p_Head *Head){

    p_Node *x = Head->head;
    while(x != NULL){
        printf("key: %f\n", x->key);
        x = x->next;
    }
    // printf("here3\n");
}