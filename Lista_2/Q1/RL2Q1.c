/*
    gcc RL2Q1.c -o q1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 600
#define separador " "

typedef struct node {
    struct node *father;
    struct node *right;
    struct node *left;
    int key;
}Node;

typedef struct Root {
    Node *root;
}Root;

void init(Root *root);
void clear_tree(Node *root);
Node* create_node(int value);
void output_height(int height);
void show_in_order(Node *root);
void insert_tree(Root *root, Node *node);

int main(){
    FILE *arq_in; arq_in = fopen("L2Q1.in", "r");
    FILE *arq_out; arq_out = fopen("L2Q1.out", "w");

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de entrada não encontrado!\n");

        fclose(arq_out);
        return EXIT_FAILURE;
    }
    
    Root *root = malloc(sizeof(Root));
    char *token;
    char *line = malloc(MAX_LINE * sizeof(char)); 

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, separador);

        init(root);
        while(token != NULL)
        {   
            insert_tree(root, create_node(atoi(token)));
            token = strtok(NULL, separador);
        }
        show_in_order(root->root);
        printf("\n");
        clear_tree(root->root);

    }while(!feof(arq_in));

    free(line);
    fclose(arq_in);
    fclose(arq_out);
    return EXIT_SUCCESS;
}

void init(Root *root) {
    root->root = NULL;
} 

Node* create_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->key = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert_tree(Root *root, Node *node) {
    Node *x = NULL;
    Node *y = root->root;
    int height = 0;

    while(y != NULL){
        x = y;

        if(x->key > node->key) y = y->left;
        else y = y->right;

        height++;
    }
    output_height(height);

    node->father = x;

    if(x == NULL) root->root = node;
    else if(node->key < x->key) x->left = node;  
    else x->right = node;
}

void show_in_order(Node *root) {

    if(root != NULL){
        show_in_order(root->left);
        printf("%d ", root->key);
        show_in_order(root->right);
    }
}

void clear_tree(Node *root) {

    if(root != NULL)
    {
        clear_tree(root->left);
        clear_tree(root->right);
        free(root);
    }
}

void output_height(int height) {
    FILE *arq_out; arq_out = fopen("L2Q1.out", "a");

    fprintf(arq_out, "%d ", height);

    fclose(arq_out);
}