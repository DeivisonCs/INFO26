/*
    gcc RL2Q3.c -o q3
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define MAX_LINE 600
#define separador " "

typedef struct no {
    struct no *father;
    struct no *right;
    struct no *left;
    int height, key;
}Tree_Node;

typedef struct head {
    Tree_Node *root;
}Tree_Root;


void init(Tree_Root *root);
int get_maior(Tree_Node *node);
void tree_free(Tree_Node *node);
void show_tree(Tree_Node *node);
Tree_Node* create_node(int value);
Tree_Node* get_sucesor(Tree_Node *node);
void update_height(Tree_Node *node, int heigth);
void transfer_2_file(Tree_Root *Root, FILE* arq_in);
Tree_Node* search_node(Tree_Node *node, int value);
void delete_element(Tree_Root *Root, int value);
void insert_node(Tree_Root *root, Tree_Node *new_node);
void transefer_node(Tree_Node *node, FILE* arq_out, int maior_Atual);


int  main() {
    FILE *arq_in; arq_in = fopen("L2Q3.in", "r");
    FILE *arq_out; arq_out = fopen("L2Q3.out", "w");

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de entrada não encontrado!");

        fclose(arq_in);
        fclose(arq_out);
        return EXIT_FAILURE;
    }

    char *token;
    char *line = malloc(MAX_LINE * sizeof(char));
    Tree_Root *_Root = malloc(sizeof(Tree_Root)); 

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, separador);

        init(_Root);
        while(token != NULL)
        {
            if(strcmp(token, "a") == 0){

                token = strtok(NULL, separador);
                insert_node(_Root, create_node(atoi(token)));
            }
            else if(strcmp(token, "r") == 0){
                
                token = strtok(NULL, separador);
                delete_element(_Root, atoi(token));
                update_height(_Root->root, 0);
            }
            // show_tree(_Root->root);
            // printf("\n");

            token = strtok(NULL, separador);
        }
        transfer_2_file(_Root, arq_in);
        tree_free(_Root->root);

    }while(!feof(arq_in));

    free(line);
    free(_Root);
    fclose(arq_in);
    fclose(arq_out);
    return EXIT_SUCCESS;
}

void init(Tree_Root *root){
    root->root = NULL;
}

Tree_Node* create_node(int value){
    Tree_Node *new_node = malloc(sizeof(Tree_Node));

    new_node->right = new_node->left = new_node->father = NULL;

    new_node->key = value;

    return new_node;
}

void insert_node(Tree_Root *root, Tree_Node *new_node){
    Tree_Node *x = NULL;
    Tree_Node *y = root->root;
    int alt = 0;

    while(y != NULL)
    {
        x = y;
        alt++;

        if(new_node->key < x->key) y = y->left;
        else y = y->right;
    }

    new_node->father = x;
    new_node->height = alt;

    if(x == NULL) root->root = new_node;
    else if(new_node->key < x->key) x->left = new_node;
    else x->right = new_node;
}

Tree_Node* get_sucesor(Tree_Node *node){

    Tree_Node *aux = node;
    
    if(aux->right != NULL){
        aux = aux->right;

        while(aux->left != NULL)
            aux = aux->left;

        return aux;
    }

    aux = node->father;
    while(aux != NULL && aux == node->right){
        node = aux;
        aux = aux->father;
    }

    return aux;
}

void delete_element(Tree_Root *Root, int value){

    Tree_Node *node = search_node(Root->root, value);
    Tree_Node *to_Delete;
    Tree_Node *x;

    if(node == NULL){
        insert_node(Root, create_node(value));
        return;
    }

    if(node->left == NULL || node->right == NULL) to_Delete = node;
    else to_Delete = get_sucesor(node);

    if(to_Delete->left != NULL) x = to_Delete->left;
    else x = to_Delete->right;

    if(x != NULL) x->father = to_Delete->father;

    if(to_Delete->father == NULL) Root->root = x;
    else{
        if(to_Delete == to_Delete->father->left) to_Delete->father->left = x;
        else to_Delete->father->right = x;
    }

    if(to_Delete != node) node->key = to_Delete->key;

    free(to_Delete); 
}

Tree_Node* search_node(Tree_Node *node, int value){
    
    if(node != NULL){

        if(value < node->key) return search_node(node->left, value);
        if(value > node->key) return search_node(node->right, value);
        
        return node;
    }

    return NULL;
}

void transfer_2_file(Tree_Root *Root, FILE* arq_in){
    FILE* arq_out; arq_out = fopen("L2Q3.out", "a");

    if(Root->root != NULL) {
        int maior_Atual = get_maior(Root->root);

        transefer_node(Root->root, arq_out, maior_Atual);

        if(!feof(arq_in))
            fprintf(arq_out, "\n");
    }

    fclose(arq_out);
}

void transefer_node(Tree_Node *node, FILE* arq_out, int maior_Atual){

    if(node != NULL){

        transefer_node(node->left, arq_out, maior_Atual);

        if(node->key == maior_Atual && node->right == NULL)
            fprintf(arq_out, "%d (%d)", node->key, node->height);
        
        else
            fprintf(arq_out, "%d (%d) ", node->key, node->height);
        

        transefer_node(node->right, arq_out, maior_Atual);
    }
}

int get_maior(Tree_Node *node){

    while(node->right != NULL)
        node = node->right;

    return node->key;
}

void show_tree(Tree_Node *node){

    if(node != NULL){

        show_tree(node->left);
        printf("%d (%d) ", node->key, node->height);
        show_tree(node->right);
    }
}

void update_height(Tree_Node *node, int heigth){

    if(node != NULL){
        node->height = heigth;
        heigth++;

        update_height(node->left, heigth);
        update_height(node->right, heigth);
    }
}

void tree_free(Tree_Node *node){

    if(node != NULL){
        tree_free(node->left);
        tree_free(node->right);
        free(node);
    }
}