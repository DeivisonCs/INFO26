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
    int key;
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

void init(p_Head *p);
void print_sub_list(p_Node *p_node);
void print_list(p_Head *Head);
void insert_main_list(p_Head *H, p_Node *list);
void insert_sub_list(s_Node *s_node, p_Head *p_H);

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
    s_Node *sub_Node;
    init(main_Head);

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
                main_Node->key = atoi(token);
                insert_main_list(main_Head, main_Node);
            }
            else if(ctrl==1){
                sub_Node = malloc(sizeof(s_Node));
                sub_Node->key = atof(token);
                insert_sub_list(sub_Node, main_Head);
            }

            token = strtok(NULL, " ");
        }

    }while(!feof(arq_in));

    free(line);
    fclose(arq_in);
    fclose(arq_out);

    return EXIT_SUCCESS;
}

void init(p_Head *p){
    p->head=NULL;
}

void insert_main_list(p_Head *H, p_Node *list){

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
    list->sub = NULL;
}

void insert_sub_list(s_Node *s_node, p_Head *p_H){

    p_Node *main_list = p_H->head;
    while(main_list != NULL)
    {
        if(s_node->key > main_list->key-1 && s_node->key < main_list->key+1){
            printf("main: %d  ", main_list->key);
            printf("sub: %.2f\n", s_node->key);
            printf("Found\n");

            if(main_list->sub == NULL){
                printf("New\n");
                main_list->sub = s_node;
                main_list->sub->next = main_list->sub;
            }
            else if(s_node->key <= main_list->sub->key){
                s_node->next = main_list->sub;

                s_Node *x = main_list->sub;
                while(x->next != main_list->sub)
                    x = x->next;

                x->next = s_node;    
                main_list->sub = s_node;
            }
            else{
                printf("Not New\n");
                s_Node *prev = main_list->sub;

                while(prev->next != main_list->sub && prev->next->key < s_node->key)
                    prev = prev->next;
                
                s_node->next = prev->next;
                prev->next = s_node;
    
            }

            print_list(p_H);
            return;
        }
        main_list = main_list->next;
    }    
}

void print_list(p_Head *Head){
    int ctrl;

    p_Node *x = Head->head;
    // s_Node *y;
    while(x != NULL)
    {
        printf("key: %d - ", x->key);
        
        if(x->sub != NULL){
            s_Node *y = x->sub;
            ctrl=0;
            do{ 
                if(ctrl == 20)
                    break;

                printf("%.2f ", y->key);
                y = y->next;
                ctrl++;
            }while(y != x->sub);
            // print_sub_list(x);
        }
        printf("\n");
        x = x->next;
    }
    printf("\n\n");
    //printf("here3\n");
}

void print_sub_list(p_Node *p_node){
    int ctrl=0;
    s_Node *x = p_node->sub;

    do{
        if(ctrl == 20)
            break;

        // printf("Here 2\n");
        printf("%.2f ", x->key);
        x = x->next;
        ctrl++;
    }while(x->next != p_node->sub);

    printf("\n");
}