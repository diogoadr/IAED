/* iaed-23 - ist1107079 - project2 */

/*
 * File:  proj2.c
 * Author:  Diogo Afonso Duarte Rodrigues
 * Description: Um sistema de gestão de carreiras de transportes públicos.
*/

#include <stdio.h>
#include <stdlib.h>

#include "argumentos.h"
#include "utils_project.h"

int main(){
    char c;

    Paragem *headParagens = NULL;
    Carreira *headCarreiras = NULL;

    while((c = getchar()) != 'q'){
        switch (c)
        {
            case 'p':
                headParagens = comandoParagem(headParagens);
                break;

            case 'c':
                headCarreiras = comandoCarreira(headCarreiras);
                break;

            case 'l':
                comandoLigacoes(headParagens, headCarreiras);
                break;

            case 'i':
                comandoIntersecao(headParagens);
                break;

            case 'r':
                headCarreiras = eliminaCarreira(headCarreiras, headParagens);
                break;

            case 'e':
                headParagens = eliminaParagem(headCarreiras,headParagens);
                break;

            case 'a':
                apagaCarreiras(headCarreiras);
                apagaParagens(headParagens);
                headCarreiras = NULL;
                headParagens = NULL;
                break;
            
        }
    }

    apagaCarreiras(headCarreiras);
    apagaParagens(headParagens);
    
    return 0;
}