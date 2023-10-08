/*
    gcc RL0Q2.c -o RL0Q2 -lm
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LINE_MAX 600
#define MAX_QTD 100
#define MAX_CARACTER 50
const char *separador = " ";

typedef struct line{
    int num_int[MAX_QTD], qtd_int; 
    char strings[MAX_QTD][MAX_CARACTER]; int qtd_string;
    float points[MAX_QTD][2]; int qtd_points;
    float num_float[MAX_QTD]; int qtd_float; 
}line;

void sort_points(line *p);
void sort_string(line *p);
float cal_distance(line *p, int i);
void identify(char *token, line *p);
void getpoint(char string[], line *p);
void transfer_files(line *p, int ctrl);
void sort_float_int(int option, line *p);

int main(){
    FILE* arq_in; arq_in = fopen("L0Q2.in", "r");
    FILE* arq_out; arq_out = fopen("L0Q2.out", "w");
    char* token;
    line types[1];
    int i=0;

    if(arq_in == NULL){
        fprintf(arq_out, "Arquivo de Entrada Não Encontrado!");
        return EXIT_FAILURE;
    }

    char* line = malloc(LINE_MAX * sizeof(char));

    do{
        types->qtd_float=0;
        types->qtd_int=0;
        types->qtd_points=0;
        types->qtd_string=0;

        fgets(line, LINE_MAX, arq_in);
        token = strtok(line, separador);

        while(token != NULL){
            identify(token, types);
            token = strtok(NULL, separador);
        }
        
        sort_points(types);
        sort_string(types);
        sort_float_int(1, types);
        sort_float_int(2, types);

        transfer_files(types, i);
        if(i==0)
            i++;
    }while(!feof(arq_in));

    // printf("Inteiros: ");
    // for(i=0; i < types->qtd_int; i++){
    //     printf("%d ", types->num_int[i]);
    // }
    // printf("\n");
    // printf("Float: ");
    // for(i=0; i < types->qtd_float; i++){
    //     printf("%.2f ", types->num_float[i]);
    // }
    // printf("\n");
    // printf("Coordenadas: ");
    // for(i=0; i < types->qtd_points; i++){
    //     printf("(%.2f,%.2f) ", types->points[i][0], types->points[i][1]);
    // }
    // printf("\n");
    // printf("String: ");
    // for(i=0; i < types->qtd_string; i++){
    //     printf("%s ", types->strings[i]);
    // }
    // printf("\n");

    free(line);
    fclose(arq_in);
    fclose(arq_out);
}

void identify(char *token, line *p){
    int i, j, aux;

    for(i=0, aux=0; token[i]!='\0'; i++)
    {
    //É UMA COORDENADA
        if(token[0]=='(')
        {
            //FUNÇAÕ SEPARAR X Y
            getpoint(token, p);
            p->qtd_points++;
            return;
        }
    //É NÚMERO E É NEGATIVO
        else if(token[0]=='-')
        { 
            //FUNÇÃO IDENTIFICAR SE É INT OU FLOAT
            for(j=0; token[j]!='\0'; j++)
            {
                if(token[j] == '.'){
                    p->num_float[p->qtd_float] = atof(token);
                    p->qtd_float++;
                    return;
                }
                else if(token[j+1] == '\0'){
                    p->num_int[p->qtd_int] = atoi(token);
                    p->qtd_int++;
                    return;
                }
            }
        }
    //NÃO É NÚMERO PELA TABELA ASCII
        else if((token[i]<48 || token[i]>57) && token[i]!='.'){
            strcpy(p->strings[p->qtd_string], token);
            p->qtd_string++;
            return;
        }
    }

    //É NÚMERO E POSITIVO, IDENTIFICAR SE É FLOAT OU INT
    if(aux==0) 
    {
        for(j=0; token[j]!='\0'; j++)
        {
            if(token[j] == '.'){
                p->num_float[p->qtd_float] = atof(token);
                p->qtd_float++;
                return;
            }
            else if(token[j+1] == '\0'){
                p->num_int[p->qtd_int] = atoi(token);
                p->qtd_int++;
                return;
            }
        }
    }

}

void getpoint(char string[], line *p){
  int i, j;
  char aux[30];

  for(i=1, j=0; string[i] != ')'; i++)
  {
    aux[j] = string[i];
    j++;
    if(string[i+1] == ','){
      aux[j] = '\0';
      p->points[p->qtd_points][0] = atof(aux);
      j=0;
      i++;
      continue;
    }
    else if (string[i+1] == ')'){
      aux[j] = '\0';
      p->points[p->qtd_points][1] = atof(aux);
      break;
    }
  }
}

void sort_points(line *p){
    int i, j, menor; 
    float sup, aux;

    for(i=0; i<p->qtd_points; i++)
    {
        for(j=i+1, menor=i; j<p->qtd_points; j++)
        {
            sup = cal_distance(p, j);
            aux = cal_distance(p, menor);
            if(sup < aux)
                menor = j;
        }
            
        sup = cal_distance(p, i);
        aux = cal_distance(p, menor);
        if(aux != sup){
            sup = p->points[i][0];
            p->points[i][0] = p->points[menor][0];
            p->points[menor][0] = sup;

            sup = p->points[i][1];
            p->points[i][1] = p->points[menor][1];
            p->points[menor][1] = sup;
        }
    }
}

void sort_float_int(int option, line *p){
    int i, j, aux_i;
    float aux_f;

    if(option==1)
        for(i=1; i<p->qtd_float; i++)
        {
            aux_f=p->num_float[i];
            j = i-1;

            while(j>=0 & aux_f<p->num_float[j]){
                p->num_float[j+1] = p->num_float[j];
                j--;
            }
            p->num_float[j+1]=aux_f;
        }
    else if(option==2)
        for(i=1; i<p->qtd_int; i++)
        {
            aux_i=p->num_int[i];
            j = i-1;

            while(j>=0 & aux_i<p->num_int[j]){
                p->num_int[j+1] = p->num_int[j];
                j--;
            }
            p->num_int[j+1]=aux_i;
        }
}

void sort_string(line *p){
    int i, j, x, menor;
    char sup[MAX_CARACTER];

    for(i=0; i<p->qtd_string - 1; i++)
    {
        x = 0;
        menor = i;
        for(j=i+1; j<p->qtd_string; j++)
        {
            x = 0;
            while(p->strings[menor][x] == p->strings[j][x])
                x++;

            if(p->strings[menor][x] > p->strings[j][x])
                menor = j;

        }
        if(menor != i)
        {
            strcpy(sup, p->strings[menor]);
            strcpy(p->strings[menor], p->strings[i]);
            strcpy(p->strings[i], sup);
        }
    }
}

float cal_distance(line *p, int i){
  float distance;

  distance = pow((p->points[i][0] - 0), 2) + pow((p->points[i][1] - 0), 2);
  distance = sqrt(distance);
    //printf("%.2f \n", distance);
  return distance;
}

void transfer_files(line *p, int ctrl){
    FILE *arq_out; arq_out = fopen("L0Q2.out", "a");
    int i;

    if(ctrl!=0)
        fputc('\n', arq_out);

    fprintf(arq_out, "%s", "str:");
    for(i=0; i<p->qtd_string; i++)
        fprintf(arq_out, "%s ", p->strings[i]);

    fprintf(arq_out, "%s", "int:");
    for(i=0; i<p->qtd_int; i++)
        fprintf(arq_out, "%d ", p->num_int[i]);

    fprintf(arq_out, "%s", "float:");
    for(i=0; i<p->qtd_float; i++)
        fprintf(arq_out, "%g ", p->num_float[i]);
    
    fprintf(arq_out, "%s", "p:");
    for(i=0; i<p->qtd_points; i++)
        fprintf(arq_out, "(%g,%g) ", p->points[i][0], p->points[i][1]);
    
    fclose(arq_out);
}