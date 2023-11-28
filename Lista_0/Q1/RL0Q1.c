/*
gcc RL0Q1.c -o RL0Q1 -lm
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 100
#define Precisao 10
#define LINE_MAX 600
const char * separador = " ";
 
typedef struct x_y{
   float xy[2];
}coord;


void sort_points(coord *p, int cont);
void getpoint(char *token, int qtd, coord *p);
float cal_distance(coord *p, int p1, int p2);
void tranfer_files(int qtd, coord *p, float distance, float shortcut, int ctrl);

int main(){
  FILE *arq_in;
  arq_in = fopen("L0Q1.in", "r");
  FILE *arq_out;
  arq_out = fopen("L0Q1.out", "w");
  coord points[LINE_MAX];
  float distance, shortcut;
  char *token;
  int cont, ctrl=0, i;

  if (arq_in == NULL) {
    fprintf(arq_out, "Arquivo de Entrada Não Encontrado!");
    return EXIT_FAILURE;
  }

  char *line = malloc(LINE_MAX * sizeof(char));
  do {
    cont = 0;

    fgets(line, Max, arq_in);
    token = strtok(line, separador);

    while (token != NULL)
    {
      if (strcmp(token, "points") == 0) {
        token = strtok(NULL, separador);
      continue;
      }

      getpoint(token, cont, points);
      cont++;
  
      token = strtok(NULL, separador);
    }

    shortcut = cal_distance(points, 0, cont-1);

    for(i=0, distance=0.0; i<cont-1; i++)
      distance += cal_distance(points, i, i+1);

    sort_points(points, cont);
  
    tranfer_files(cont, points, distance, shortcut, ctrl);
    if(ctrl==0)
      ctrl++;
  } while (!feof(arq_in));

  free(line);
  fclose(arq_in);
  fclose(arq_out);
}

float cal_distance(coord *p, int p1, int p2){
  float distance;
 
  if(p2==0){
    distance = pow((p[p1].xy[0] - 0), 2) + pow((p[p1].xy[1] - 0), 2);
    distance = sqrt(distance);
  }
  else{
    distance = pow((p[p2].xy[0] - p[p1].xy[0]), 2) + pow((p[p2].xy[1] - p[p1].xy[1]), 2);
    distance = sqrt(distance);
  }

  return distance;
}

void getpoint(char *token, int qtd, coord *p){
  int i, j;
  char aux[30];

  for (i = 1, j = 0; token[i] != '\0'; i++)
  {
    aux[j] = token[i];
    j++;

    if (token[i + 1] == ',') {
      aux[j] = '\0';
      p[qtd].xy[0] = atof(aux);
      j=0;
      i++;
    }
    else if (token[i + 1] == ')'){
      aux[j] = '\0';
      p[qtd].xy[1] = atof(aux);
      break;
    }
  }
}

void sort_points(coord *p, int cont){
    int i, j, menor; 
    float sup, aux;

    for(i=0; i < cont-2; i++)
    {
        for(j=i+1, menor=i; j < cont-1; j++)
        {
            sup = cal_distance(p, j, 0);
            aux = cal_distance(p, menor, 0);
            if(sup < aux)
                menor = j;
        }
            
        sup = cal_distance(p, i, 0);
        aux = cal_distance(p, menor, 0);
        if(aux != sup){
            sup = p[i].xy[0];
            p[i].xy[0] = p[menor].xy[0];
            p[menor].xy[0] = sup;

            sup = p[i].xy[1];
            p[i].xy[1] = p[menor].xy[1];
            p[menor].xy[1] = sup;
        }
    }
}

void tranfer_files(int qtd, coord *p, float distance, float shortcut, int ctrl) {
  FILE *arq_out;
  arq_out = fopen("L0Q1.out", "a");
  int i, j;
  char aux[10];

  // char *line = malloc(15 * sizeof(char));

  // fgets(line, 10, arq_out);
  // line = strtok(line, " ");

  if (ctrl != 0)
    fputc('\n', arq_out);

  fprintf(arq_out, "%s", "points ");
  for (i = 0; i < qtd; i++) 
    fprintf(arq_out, "(%g,%g) ", p[i].xy[0], p[i].xy[1]);

  fprintf(arq_out, "%s ", "distance");
  sprintf(aux, "%.2f", distance);
  for (j = 0; aux[j] != '\0'; j++)
  {
    if ((aux[j] == '.') && (aux[j + 2] != '0')){
      fprintf(arq_out, "%.2f ", distance);
      break;
    }
    else if ((aux[j] == '.') && (aux[j + 1] != '0')) {
      fprintf(arq_out, "%.1f ", distance);
      break;
    }
    else if (aux[j] == '.') {
      fprintf(arq_out, "%.0f ", distance);
      break;
    }
  }

  fprintf(arq_out, "%s ", "shortcut");
  sprintf(aux, "%.2f", shortcut);
  for (j = 0; aux[j] != '\0'; j++) {
    if ((aux[j] == '.') && (aux[j + 2] != '0')) {
      fprintf(arq_out, "%.2f", shortcut);
      break;
    }

    else if ((aux[j] == '.') && (aux[j + 1] != '0')) {
      fprintf(arq_out, "%.1f", shortcut);
      break;
    }

    else if (aux[j] == '.') {
      fprintf(arq_out, "%.0f", shortcut);
      break;
    }
  }

  //free(line);
  fclose(arq_out);
  // fprintf(arq_out, "%s %.2f ", "distance", distance);
  // fprintf(arq_out, "%s %.2f\n", "shortcut", shortcut);
}