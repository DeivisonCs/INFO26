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

void init(p_Head *p);
void clear_list(p_Head *p_H);
void print_sub_test(p_Head *p_H);
void print_main_test(p_Head *p_H);
int verify_range(int main, float var);
void print_list(p_Head *Head, int lineQtd);
void insert_main_list(p_Head *H, p_Node *list);
void insert_sub_list(s_Node *s_node, p_Head *p_H);

int main(){
    FILE *arq_in; arq_in = fopen("L1Q3.in", "r");
    FILE *arq_out; arq_out = fopen("L1Q3.out", "w");
    char *token;
    int ctrl, lineQtd=0;

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de Entrada Não Encontrado!");
        return EXIT_FAILURE;
    }

    p_Head *main_Head = malloc(sizeof(p_Head));
    p_Node *main_Node;
    s_Node *sub_Node;

    char *line = malloc(MAX_LINE * sizeof(char));

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, " ");

        init(main_Head);
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
        print_list(main_Head, lineQtd);
        // print_main_test(main_Head);
        // print_sub_test(main_Head);
        clear_list(main_Head);
        lineQtd++;

    }while(!feof(arq_in));

    free(line);
    free(main_Head);

    fclose(arq_in);
    fclose(arq_out);

    return EXIT_SUCCESS;
}

void init(p_Head *p){
    p->head=NULL;
}

void insert_main_list(p_Head *H, p_Node *list){

    p_Node *x = H->head;

    if(x == NULL){
        list->next = NULL;
        list->prev = NULL;
        H->head = list;
    }
    else if(list->key <= x->key){    //Inserir no lugar do primeiro
        list->next = x;
        list->prev = NULL;
        x->prev = list;
        H->head = list;
    }
    else{   //Inserir no meio ou fim da lista

        while(x->next != NULL && x->key <= list->key)
            x = x->next;

        if(x->key >= list->key){    //Caso não seja final da lista
            x->prev->next = list;
            list->prev = x->prev;
            list->next = x;
            x->prev = list;
        }
        else{
            list->next = NULL;
            list->prev = x;
            x->next = list;
        }
    }

    list->sub = NULL;
}

void insert_sub_list(s_Node *s_node, p_Head *p_H){

    p_Node *main_list = p_H->head;

    while(main_list != NULL)
    {
         
        if(verify_range(main_list->key, s_node->key))
        {
            if(main_list->sub == NULL)  //Caso seja o primeiro elemento
            {
                main_list->sub = s_node;
                s_node->next = main_list->sub;
            }
            else if(s_node->key <= main_list->sub->key)    //Caso seja menor que o primeiro elemento da lista
            {
                s_node->next = main_list->sub;

                s_Node *x = main_list->sub;
                while(x->next != main_list->sub)
                    x = x->next;

                x->next = s_node;    
                main_list->sub = s_node;
            }
            else    //Caso seja adicionado no meio ou final da lista
            {
                s_Node *prev = main_list->sub;

                while(prev->next != main_list->sub && prev->next->key < s_node->key)
                    prev = prev->next;
                
                s_node->next = prev->next;
                prev->next = s_node;
    
            }

            return;
        }
        main_list = main_list->next;
    }    
}

void print_list(p_Head *Head, int lineQtd){
    FILE* arq_out; arq_out = fopen("L1Q3.out", "a");
    p_Node *x = Head->head;
    
    if(lineQtd != 0)
        fprintf(arq_out, "\n");

    fprintf(arq_out, "[");
    while(x != NULL)
    {
        fprintf(arq_out, "%d", x->key);

        if(x->sub != NULL)
        {
            s_Node *y = x->sub;

            fprintf(arq_out, "(");
            do{ 
                fprintf(arq_out, "%g", y->key);

                if(y->next != x->sub)
                    fprintf(arq_out, "->");

                y = y->next;
            }while(y != x->sub);
            fprintf(arq_out, ")");
        }
        
        if(x->next != NULL)
            fprintf(arq_out, "->");

        x = x->next;
    }
    fprintf(arq_out, "]");

    fclose(arq_out);
}

void clear_list(p_Head *p_H){

    p_Node *p_node = p_H->head;
    s_Node *s_next;

    while(p_node != NULL)
    {
        if(p_node->sub != NULL)
        {
            s_next = p_node->sub;
            do{ 
                s_Node *s_aux = s_next;
                s_next = s_next->next;
                free(s_aux);
            }while(s_next != p_node->sub);
        }
        p_node->sub = NULL;

        p_Node *p_aux = p_node;
        p_node = p_node->next;

        free(p_aux);
        if(p_aux)
            continue;
        else 
            break;
    }

    p_H->head = NULL;
}

void print_main_test(p_Head *p_H){
    int ctrl;
    p_Node *p_node = p_H->head;

    printf("\n\tPrint Main-Lista:\n");
    while(p_node != NULL)
    {   
        printf("%d\n", p_node->key);
        p_node = p_node->next;
    }
}

void print_sub_test(p_Head *p_H){
    int ctrl;
    p_Node *p_node = p_H->head;
    s_Node *node;

    printf("\n\tPrint Sub-Lista:\n");
    while(p_node != NULL)
    {   
        ctrl=0;
        printf("main: %d\n", p_node->key);

        if(p_node->sub != NULL){
            node = p_node->sub;
            do{
                printf("%.2f\n", node->key);
                node = node->next;
                // ctrl++;
                // if(ctrl == 5)
                //     break;
            }while(node != p_node->sub);
        }

        p_node = p_node->next;
    }
    printf("-------------------------------\n");
}

int verify_range(int main, float var){
    int x=0;

    // printf("Valor: %f ", var);
    // printf("Range: %f ", main - 0.99);
    // printf("Range: %f\n", main + 0.99);
    if(var <= ((float)main + 0.99) && var >= (float)main)
        x = 1;
    // else if(var >= (main - 0.99) && var <= main)
    //     x = 1;

    return x;
}