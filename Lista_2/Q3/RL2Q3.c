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
    int key;
}Tree_Node;

typedef struct head {
    Tree_Node *root;
}Tree_Root;


void init(Tree_Root *root);
void tree_free(Tree_Node *node);
Tree_Node* create_node(int value);
Tree_Node* get_next(Tree_Node *node);
void insert_node(Tree_Root *root, Tree_Node *new_node);


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
                printf("%s ", token);
            }
            else if(strcmp(token, "r") == 0){
                token = strtok(NULL, separador);
                printf("%s ", token);
            }

            token = strtok(NULL, separador);
        }

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

    while(y != NULL)
    {
        x = y;

        if(new_node->key < y->key) y = y->left;
        else if(new_node->key > y->key) y = y->right;

        else {  // Não permite valores iguais
            free(new_node);
            return;
        }
    }

    new_node->father = x;

    if(x == NULL) root->root = new_node;
    if(new_node->key < x->key) x->left = new_node;
    else x->left = new_node;
}

// void remove_node(Tree_Root *Root, int value){

//     Tree_Node *node = Root->root;


// }

Tree_Node* get_next(Tree_Node *node){

    Tree_Node *min = node;
    
    if(min->right != NULL){
        min = min->right;

        while(min->left != NULL)
            min = min->left;
    }

}

void tree_free(Tree_Node *node){

    if(node != NULL){
        tree_free(node->left);
        tree_free(node->right);
        free(node);
    }
}