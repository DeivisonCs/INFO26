/*
    gcc RL2Q2.c -o q2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 600
#define separador " "

int maior_Atual_Tree;

typedef struct tree{
    struct tree *father;
    struct tree *right;
    struct tree *left;
    int key;
}Node_tree;

typedef struct root{
    Node_tree *root;
}Root_tree;

void init(Root_tree *root);
int get_soma(Node_tree *node);
void clear_tree(Node_tree *node);
Node_tree* create_node(int value);
void transfer_2_file(Root_tree *root);
// int get_soma_right(Node_tree *node);
void transfer_sum_2_file(Node_tree *node, FILE *arq);
void insert_node(Root_tree *root, Node_tree *new_node);

int main(){
    FILE *arq_in; arq_in = fopen("L2Q2.in", "r");
    FILE *arq_out; arq_out = fopen("L2Q2.out", "w");

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de entrada não encontrado!");

        fclose(arq_in);
        fclose(arq_out);
    }

    char *token;
    char *line = malloc(MAX_LINE * sizeof(char));
    Root_tree *__Root = malloc(sizeof(Root_tree));

    do{
        fgets(line, MAX_LINE, arq_in);
        token = strtok(line, separador);

        init(__Root);
        maior_Atual_Tree = 0;
        while(token != NULL)
        {
            insert_node(__Root, create_node(atoi(token)));

            token = strtok(NULL, separador);
        }
        transfer_2_file(__Root);
        clear_tree(__Root->root);

    }while(!feof(arq_in));

    free(line);
    free(__Root);
    fclose(arq_in);
    fclose(arq_out);
}

void init(Root_tree *root) {
    root->root = NULL;
}

Node_tree* create_node(int value) {
    Node_tree *new_node = malloc(sizeof(Node_tree));

    new_node->key = value;
    new_node->father = new_node->right = new_node->left = NULL;

    return new_node;
}

void insert_node(Root_tree *root, Node_tree *new_node) {
    Node_tree *y = root->root;
    Node_tree *x = NULL;

    while(y != NULL)
    {
        x = y;

        if(new_node->key < x->key) y = y->left;
        else if(new_node->key > x->key) y = y->right;
        else {
            free(new_node);  //Caso já exista um elemento correspondente
            return;
        }
    }
    if(new_node->key > maior_Atual_Tree) maior_Atual_Tree = new_node->key;

    new_node->father = x;

    if(x == NULL) root->root = new_node;
    else if(new_node->key < x->key) x->left = new_node;
    else x->right = new_node;
}

// int get_soma(Root_tree *root) {
//     Node_tree *node = root->root;
//     int right_sum = 0;
//     int left_sum = 0;

//     while(node != NULL){
//         right_sum += node->key;

//         node = node->right;
//     }

//     node = root->root;

//     while(node != NULL){
//         left_sum += node->key;

//         node = node->left;
//     }

//     return right_sum - left_sum;
// } 

int get_soma(Node_tree *node) {
    int sum = 0;

    if(node != NULL){
        sum = node->key;
        sum += get_soma(node->left);
        sum += get_soma(node->right);
    }

    return sum;
} 
/*Hint - Usar a função recursiva de imprimir para pegar a soma do nós em cada lado*/

void transfer_sum_2_file(Node_tree *node, FILE *arq) {

    if(node != NULL){

        transfer_sum_2_file(node->left, arq);

        int result = get_soma(node->right) - get_soma(node->left);
        fprintf(arq, "%d (%d)", node->key, result);

        if(node->key != maior_Atual_Tree)
            fprintf(arq, " ");

        transfer_sum_2_file(node->right, arq);

    } 

}

void transfer_2_file(Root_tree *root) {
    FILE *arq_out; arq_out = fopen("L2Q2.out", "a");

    transfer_sum_2_file(root->root, arq_out);
    fprintf(arq_out, "\n");

    fclose(arq_out);
}

void clear_tree(Node_tree *node) {

    if(node != NULL){
        clear_tree(node->left);
        clear_tree(node->right);
        free(node);
    }
}
