/*
    gcc RL2Q1.c -o q1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 600
#define separador " "

typedef struct alt_list {
    int key;
    struct alt_list *next;
}alt_List;

typedef struct head_list {
    alt_List *list;
}head_Alt;

typedef struct node {
    struct node *father;
    struct node *right;
    struct node *left;
    int key;
}Node;

typedef struct Root {
    Node *root;
}Root;

void clear_tree(Node *root);
Node* create_node(int value);
void show_in_order(Node *root);
Node* get_predecessor(Node *node);
void clear_alt_list(head_Alt *alt);
void get_height(int height, alt_List *head);
Node* get_max_plus_alt(Node *root, int *alt);
void init(Root *root, head_Alt *height_list);
void add_height_list(head_Alt *head, int alt);
int insert_tree_get_height(Root *root, Node *node);
void transfer_2_file(Root *root, FILE* __arq_in, head_Alt *alt);

int main(){
    FILE *arq_in; arq_in = fopen("L2Q1.in", "r");
    FILE *arq_out; arq_out = fopen("L2Q1.out", "w");

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de entrada não encontrado!\n");

        fclose(arq_out);
        return EXIT_FAILURE;
    }
    
    Root *root = malloc(sizeof(Root));
    head_Alt *height_list = malloc(sizeof(head_Alt));

    char *line = malloc(MAX_LINE * sizeof(char)); 
    char *token;
    int alt;

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, separador);

        init(root, height_list);
        while(token != NULL)
        {   
            alt = insert_tree_get_height(root, create_node(atoi(token)));
            add_height_list(height_list, alt);
            token = strtok(NULL, separador);
        }
        transfer_2_file(root, arq_in, height_list);

        // show_in_order(root->root);
        clear_tree(root->root);
        clear_alt_list(height_list);
    }while(!feof(arq_in));

    free(line);
    fclose(arq_in);
    fclose(arq_out);
    return EXIT_SUCCESS;
}

void init(Root *root, head_Alt *height_list) {
    root->root = NULL;
    height_list->list = NULL;
} 

Node* create_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->key = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int insert_tree_get_height(Root *root, Node *node) {
    Node *x = NULL;
    Node *y = root->root;
    int height = 0;

    while(y != NULL){
        x = y;

        if(x->key > node->key) y = y->left;
        else y = y->right;

        height++;
    }

    node->father = x;

    if(x == NULL)  root->root = node;
    else if(node->key < x->key) x->left = node;  
    else x->right = node;

    return height;
}

void add_height_list(head_Alt *head, int alt){
    alt_List *new_node = malloc(sizeof(new_node));
    new_node->key = alt;
    new_node->next = NULL;

    alt_List *aux = head->list;

    if(aux == NULL) head->list = new_node;
    else{
        while(aux->next != NULL)
            aux = aux->next;

        aux->next = new_node;
    }
}

void show_in_order(Node *root) {

    if(root != NULL){
        show_in_order(root->left);
        printf("%d ", root->key);
        show_in_order(root->right);
    }
}

void get_height(int height, alt_List *head) {
    alt_List *alt = malloc(sizeof(alt_List));
    alt->key = height;
    alt->next = NULL;

    alt_List *aux = head;

    if(aux == NULL) aux = alt;

    else while(aux->next != NULL)
            aux = aux->next;

    aux->next = alt;    
}

Node* get_predecessor(Node *node) {
    Node *pred = node;

    if(pred->left != NULL){
        pred = pred->left;

        while(pred->right != NULL)
            pred = pred->right;

        return pred;
    }

    pred = node->father;
    while(pred != NULL && node == pred->left){
        node = pred;
        pred = pred->father;
    }

    return pred;
}

Node* get_max_plus_alt(Node *root, int *alt) {

    if(root != NULL)
        while(root->right != NULL){
            root = root->right;
            (*alt)++;
        }

    return root;
}

void transfer_2_file(Root *root, FILE* __arq_in, head_Alt *alt) {
    FILE *arq_out; arq_out = fopen("L2Q1.out", "a");
    Node *node = root->root;
    int alt_max = 0;

    if(root != NULL)
    {
        alt_List *aux = alt->list;

        while(aux != NULL){
            fprintf(arq_out, "%d ", aux->key);
            aux = aux->next;
        }

        node = get_max_plus_alt(node, &alt_max);

        fprintf(arq_out, "max %d ", node->key);
        fprintf(arq_out, "alt %d ", alt_max);

        node = get_predecessor(node);

        if(node == NULL)  fprintf(arq_out, "pred NaN");
        else  fprintf(arq_out, "pred %d", node->key);

    }
    else fprintf(arq_out, " max alt pred NaN");
    
    if(!feof(__arq_in)) fprintf(arq_out, "\n");

    fclose(arq_out);
} 

void clear_tree(Node *root) {

    if(root != NULL)
    {
        clear_tree(root->left);
        clear_tree(root->right);
        free(root);
    }
}

void clear_alt_list(head_Alt *alt) {
    alt_List *atual = alt->list;

    if(atual != NULL){

        alt_List *ant;
        while(atual != NULL){
            ant = atual->next;

            free(atual);
            atual = ant;
        }
    }
}