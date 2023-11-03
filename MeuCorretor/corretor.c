#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 600

int main(){
    FILE *gabarito; gabarito = fopen("gabarito.out", "r");
    FILE *resposta; resposta = fopen("resposta.in", "r");  //Sua Resposta

    if(resposta == NULL || gabarito == NULL){
        fclose(resposta);
        fclose(gabarito);
        return EXIT_FAILURE;
    }

    int cont=1;
    char *line_resp = malloc(MAX_CHAR * sizeof(char));
    char *line_gab = malloc(MAX_CHAR * sizeof(char));

    do{
        fgets(line_resp, MAX_CHAR, resposta);
        fgets(line_gab, MAX_CHAR, gabarito);

        if(strcmp(line_resp, line_gab) != 0)
            printf("Erro linha: %d\n", cont);

        cont++;
    }while(!feof(resposta));

    free(line_gab);
    free(line_resp);
    fclose(resposta);
    fclose(gabarito);
}