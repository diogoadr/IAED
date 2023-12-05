/*Ficheiro com as funções que manipulam o output do utilizador*/

#include <stdio.h>
#include "argumentos.h"

#define NAO_EXISTEM_MAIS_ARGUMENTOS 2
#define EXISTEM_MAIS_ARGUMENTOS 1
#define ZERO_ARGUMENTOS 0

int leArgumento(char palavra[MAX]){
    /*
        return 2 -> leu uma palavra mas não existe mais para ler
        return 1 -> leu uma palavra e ainda existe mais para ler
        return 0 -> não existe mais nada para ler 
    */

    int i;
    char c = getchar();

    if (c == '\n'){
        return ZERO_ARGUMENTOS;
    }
    while(c == ' ')
        c = getchar();

    if (c == '"'){

        for (i = 0; (c = getchar()) != '"'; i++){
            palavra[i] = c;
        }
        palavra[i] = '\0';

        if((c = getchar()) == '\n'){
            return NAO_EXISTEM_MAIS_ARGUMENTOS;
        }

    } else { 

        for (i = 0; c != ' '; i++){
            if (c == '\n'){ 
                palavra[i] = '\0';
                return NAO_EXISTEM_MAIS_ARGUMENTOS;
            }
            palavra[i] = c;
            c = getchar();
        }

        palavra[i] = '\0';
    }

    return EXISTEM_MAIS_ARGUMENTOS;
}

/*
    Função que lê até ao fim da linha para passar para o comando seguinte.
    Utilizado nos casos em que a função imprime um erro antes de chegar ao 
    fim do argumento passado.
*/
void leAteFimLinha(){
    char palavra[MAX];

    while(leArgumento(palavra) != NAO_EXISTEM_MAIS_ARGUMENTOS);
}