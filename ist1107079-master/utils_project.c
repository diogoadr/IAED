/*Ficheiro com todos os comandos possíveis pelo utilizador*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "argumentos.h"
#include "utils_project.h"

#define NAO_EXISTEM_MAIS_ARGUMENTOS 2
#define EXISTEM_MAIS_ARGUMENTOS 1
#define ZERO_ARGUMENTOS 0

#define STRING_IGUAL 0

#define ENCONTRADO 0
#define NAO_ENCONTRADO 1


Paragem *encontrarUltimaParagem(Paragem *headParagens){
    /*Função que encontra a última paragem na lista das paragens*/

    if(headParagens == NULL){
        return NULL;
    }

    while(headParagens->next != NULL){
        headParagens = headParagens->next;
    }

    return headParagens;
}
/* Função que imprime todas as paragens, com as suas devidas informações*/
void printTodasParagens(Paragem *headParagens){
    headParagens = encontrarUltimaParagem(headParagens);
    
    while(headParagens != NULL){
        printf("%s: %16.12f %16.12f %d\n", 
            headParagens->nome, headParagens->latitude, 
            headParagens->longitude, headParagens->numCarreiras);
        headParagens = headParagens->prev;
    }
}

/* 
    Função que retorna o ponteiro da paragem que se quer encontrar através do seu nome.
    Retorna NULL caso não encontre.
*/
Paragem *encontrarParagem(Paragem *headParagens, char *palavra){

    while(headParagens != NULL){
        if(strcmp(palavra, headParagens->nome) == STRING_IGUAL){
            return headParagens;
        }

        headParagens = headParagens->next;
    }

    return NULL;
}

/*Função que cria e adiciona no início da lista uma nova paragem*/
Paragem *criarParagem(Paragem *headParagens, char palavra[MAX]){
    Paragem *novaParagem;
    if((novaParagem = (Paragem*) malloc (sizeof(Paragem))) == NULL){
        noMemory();
    }
    if((novaParagem->nome = (char*) malloc (sizeof(char) * (strlen(palavra)+1))) == NULL){
        noMemory();
    }
    strcpy(novaParagem->nome, palavra);

    novaParagem->headListaCarreiras = NULL;
    novaParagem->numCarreiras = 0;
    
    leArgumento(palavra);
    novaParagem->latitude = strtod(palavra, NULL);
    leArgumento(palavra);
    novaParagem->longitude = strtod(palavra, NULL);
    novaParagem->prev = NULL;

    /*primeira paragem a ser criada*/
    if(headParagens == NULL){
        novaParagem->next = NULL;
    }

    else{
        novaParagem->next = headParagens;
        headParagens->prev = novaParagem;
    }
    return novaParagem;
}

/*Função que comanda grande parte das funções sobre paragens*/
Paragem *comandoParagem(Paragem *headParagens){
    Paragem *paragem;
    char palavra[MAX];
    int status = leArgumento(palavra);

    /*print a todas as paragens existentes*/
    if(status == ZERO_ARGUMENTOS){
        printTodasParagens(headParagens);
        return headParagens;
    }

    /*encontra paragem e dá print à latitude e longitude*/

    paragem = encontrarParagem(headParagens, palavra);

    if(status == NAO_EXISTEM_MAIS_ARGUMENTOS){ 

        if (paragem == NULL){
            printf("%s: no such stop.\n", palavra);
        }
        else {
            printf("%16.12f %16.12f\n", paragem->latitude, paragem->longitude);
        }
    }

    /*cria uma nova paragem*/
    else {

        if(paragem != NULL){
            printf("%s: stop already exists.\n", palavra);
            leAteFimLinha();
            return headParagens;
        }

        headParagens = criarParagem(headParagens, palavra);
    }

    return headParagens;
}

/*Função que apaga toda a lista de carreiras de uma paragem*/
void apagaListaCarreira(ListaCarreiras *headListaCarreira){

    ListaCarreiras *aux;

    while(headListaCarreira != NULL){

        aux = headListaCarreira->next;

        free(headListaCarreira->nomeCarreira);
        free(headListaCarreira);

        headListaCarreira = aux;
    }
}

/*Função que apaga toda a paragem dada*/
void apagaParagem(Paragem *paragem){
    free(paragem->nome);
    apagaListaCarreira(paragem->headListaCarreiras);
    free(paragem);
}

/*Função que apaga todas as paragens criadas*/
void apagaParagens(Paragem *headParagens){
    Paragem *aux;

    while(headParagens != NULL){
        aux = headParagens->next;
        apagaParagem(headParagens);
        headParagens = aux;
    }   
}

/*
    Função que encontra carreira na lista de carreiras através do seu nome.
    Retorna NULL caso não encontre.
*/
Carreira *encontrarCarreira(Carreira *headCarreiras, char *palavra){
    while(headCarreiras != NULL){
        if(strcmp(headCarreiras->nome, palavra) == STRING_IGUAL){
            return headCarreiras;
        }
        headCarreiras = headCarreiras->next;
    }

    return NULL;
}

/*
    Função que encontra ultima carreira na lista de carreiras criadas
    Retorna NULL caso não encontre
*/
Carreira *encontrarUltimaCarreira(Carreira *headCarreiras){
    if(headCarreiras == NULL){
        return NULL;
    }

    while (headCarreiras->next != NULL){
        headCarreiras = headCarreiras->next;
    }
    return headCarreiras;
}

/*Função que imprime uma carreira, com as suas devidas informações*/
void printCarreira(Carreira *carreira){
    printf("%s ", carreira->nome);

    if (carreira->numParagens > 1){
        printf("%s %s ", carreira->headLigacoes->paragemOrigem->nome, 
            carreira->ultimaLigacao->paragemDestino->nome);
    }

    printf("%d %.2f %.2f\n", carreira->numParagens, carreira->custo, carreira->duracao);

}

/*Função que imprime todas as carreiras, com as suas devidas informações*/
void printTodasCarreiras(Carreira *headCarreiras){
    headCarreiras = encontrarUltimaCarreira(headCarreiras);

    while (headCarreiras != NULL){
        printCarreira(headCarreiras);
        headCarreiras = headCarreiras->prev;
    }
}

/*Função que cria e adiciona no início da lista uma nova carreira*/
Carreira *criaCarreira(Carreira *headCarreiras, char *palavra){
    Carreira *novaCarreira;
    if((novaCarreira = (Carreira*) malloc(sizeof(Carreira))) == NULL){
        noMemory();
    }
    if((novaCarreira->nome = (char*) malloc(sizeof(char) * (strlen(palavra)+1))) == NULL){
        noMemory();
    }
    strcpy(novaCarreira->nome, palavra);

    novaCarreira->custo = 0;
    novaCarreira->duracao = 0; 
    novaCarreira->numParagens = 0;
    novaCarreira->headLigacoes = novaCarreira->ultimaLigacao = NULL;
    novaCarreira->prev = NULL;

    if(headCarreiras == NULL){
        novaCarreira->next = NULL;
    }

    else{
        novaCarreira->next = headCarreiras;
        headCarreiras->prev = novaCarreira;
    }

    return novaCarreira;
}

/*Função que imprime as paragens de uma carreira*/
void printParagensDeCarreira(Carreira *headCarreiras){

    Ligacao *aux = headCarreiras->headLigacoes;

    if (aux == NULL){
        return;
    }
    while(aux->next != NULL){
        printf("%s, ", aux->paragemOrigem->nome);
        aux = aux->next;
    }
    
    if(aux->next == NULL){
        printf("%s, %s\n", aux->paragemOrigem->nome, aux->paragemDestino->nome);
    }
}

/*Função que imprime as paragens de uma carreira inversamente*/
void printParagensDeCarreiraInverso(Carreira *headCarreiras){
    Ligacao *aux;

    if (headCarreiras == NULL){
        return;
    }

    aux = headCarreiras->ultimaLigacao;

    if (aux == NULL){
        return;
    }

    while(aux->prev != NULL){
        printf("%s, ", aux->paragemDestino->nome);
        aux = aux->prev;
    }
    
    if(aux->prev == NULL){
        printf("%s, %s\n", aux->paragemDestino->nome, aux->paragemOrigem->nome);
    }
}

/*Função que comanda todas as funções relacionadas a uma carreira*/
Carreira *comandoCarreira(Carreira *headCarreiras){
    Carreira *carreira;
    char palavra[MAX];
    int status = leArgumento(palavra);

    if(status == ZERO_ARGUMENTOS){
        printTodasCarreiras(headCarreiras);
        return headCarreiras;
    }

    carreira = encontrarCarreira(headCarreiras, palavra);

    if (status == NAO_EXISTEM_MAIS_ARGUMENTOS){

        if(carreira == NULL)
            headCarreiras = criaCarreira(headCarreiras, palavra);

        else{
            printParagensDeCarreira(carreira);
        }
    }  

    else if (status == EXISTEM_MAIS_ARGUMENTOS){
        leArgumento(palavra);

        if(strncmp(palavra, "inverso", strlen(palavra)) == STRING_IGUAL && strlen(palavra) >= 3){
                printParagensDeCarreiraInverso(carreira);
        }else{
                printf("incorrect sort option.\n");
        }
    }

    return headCarreiras;
}

/*Cria a ligacao, com as respetivas paragens, custo e duração */
Ligacao *criarLigacao(Paragem *ParagemOrigem, Paragem *ParagemDestino, 
                        double custo, double duracao){
    Ligacao *novaLigacao;
    if ((novaLigacao = (Ligacao*) malloc(sizeof(Ligacao))) == NULL){
        noMemory();
    }
    novaLigacao->paragemOrigem = ParagemOrigem;
    novaLigacao->paragemDestino = ParagemDestino;
    novaLigacao->custo = custo;
    novaLigacao->duracao = duracao;

    return novaLigacao;    
}

/*Função que verifica se a paragem faz parte de uma carreira especifica ou não*/
int encontrarCarreiraEmParagem(char *nomeCarreira, ListaCarreiras *listaHeadCarreiras){
    while(listaHeadCarreiras != NULL){
        if(strcmp(nomeCarreira, listaHeadCarreiras->nomeCarreira) == STRING_IGUAL){
            return ENCONTRADO;
        }
        listaHeadCarreiras = listaHeadCarreiras->next;
    }
    return NAO_ENCONTRADO;
}   

/*Função que adiciona alfabeticamente o ponteiro da carreira à paragem*/
void adicionaCarreiraAParagem(char *nomeCarreira, Paragem *paragem){
    ListaCarreiras *aux, *prev, *novaCarreiraParagem;

    if (encontrarCarreiraEmParagem(nomeCarreira, paragem->headListaCarreiras) == ENCONTRADO){
        return;
    }

    if((novaCarreiraParagem = (ListaCarreiras*) malloc(sizeof(ListaCarreiras))) == NULL){
        noMemory();
    }
    if((novaCarreiraParagem->nomeCarreira = (char*) malloc(sizeof(char) * (strlen(nomeCarreira) + 1))) == NULL){
        noMemory();
    }
    strcpy(novaCarreiraParagem->nomeCarreira, nomeCarreira);
    paragem->numCarreiras++;

    if (paragem->headListaCarreiras == NULL){
        paragem->headListaCarreiras = novaCarreiraParagem;
        novaCarreiraParagem->next = NULL;
        return;
    }
    
    /*adicionar carreira por ordem alfabetica*/
    aux = paragem->headListaCarreiras;
    prev = NULL;
    
    while(aux != NULL){
        /*adiciona antes do ponteiro / adicionar à esquerda da struct*/
        if(strcmp(novaCarreiraParagem->nomeCarreira, aux->nomeCarreira) < STRING_IGUAL){
            if(aux == paragem->headListaCarreiras){ /*adicionar na primeira posicao*/
                novaCarreiraParagem->next = paragem->headListaCarreiras;
                paragem->headListaCarreiras = novaCarreiraParagem;
                return;
            }
            else {
                prev->next = novaCarreiraParagem;
                novaCarreiraParagem->next = aux;
                return;
            }


        }
        /*adiciona carreira ao fim da lista*/
        if(aux->next == NULL){
            aux->next = novaCarreiraParagem;
            novaCarreiraParagem->next = NULL;
            return;
        }

        prev = aux;
        aux = aux->next;
    }
}

/*Função que adiciona uma ligacao a uma carreira*/
void juntaLigacaoACarreira(Carreira *carreira, Ligacao *novaLigacao){

    if(carreira->headLigacoes == NULL){
        carreira->headLigacoes = novaLigacao;
        carreira->ultimaLigacao = novaLigacao;
        novaLigacao->next = NULL;
        novaLigacao->prev = NULL;
        carreira->numParagens += 2;
        adicionaCarreiraAParagem(carreira->nome, novaLigacao->paragemOrigem);
        adicionaCarreiraAParagem(carreira->nome, novaLigacao->paragemDestino); 
        return;
    }

    else{
        /*adicionar em ultimo*/
        if(strcmp(carreira->ultimaLigacao->paragemDestino->nome, 
                        novaLigacao->paragemOrigem->nome) == STRING_IGUAL){
            carreira->ultimaLigacao->next = novaLigacao;
            novaLigacao->prev = carreira->ultimaLigacao;
            novaLigacao->next = NULL;
            carreira->ultimaLigacao = novaLigacao;
            adicionaCarreiraAParagem(carreira->nome, novaLigacao->paragemDestino);
        }

        /*adicionar em primeiro*/
        else if (strcmp(carreira->headLigacoes->paragemOrigem->nome,
                            novaLigacao->paragemDestino->nome) == STRING_IGUAL){
            carreira->headLigacoes->prev = novaLigacao;
            novaLigacao->next = carreira->headLigacoes;
            novaLigacao->prev = NULL;
            carreira->headLigacoes = novaLigacao;

            adicionaCarreiraAParagem(carreira->nome, novaLigacao->paragemOrigem);
        }

        carreira->numParagens += 1;
    }
}

/*Função que comanda todas as ligações relacionadas com as carreiras*/
void comandoLigacoes(Paragem *headParagens, Carreira *headCarreiras){
    double custo, duracao;
    char palavra[MAX];
    Carreira *carreira;
    Paragem *ParagemOrigem, *ParagemDestino;
    Ligacao *novaLigacao;

    leArgumento(palavra);
    carreira = encontrarCarreira(headCarreiras, palavra);

    if(carreira == NULL){
        printf("%s: no such line.\n", palavra);
        leAteFimLinha();
        return;
    }
    leArgumento(palavra);
    ParagemOrigem = encontrarParagem(headParagens, palavra);

    if (ParagemOrigem == NULL){
        printf("%s: no such stop.\n", palavra);
        leAteFimLinha();
        return;
    }
    leArgumento(palavra);
    ParagemDestino = encontrarParagem(headParagens, palavra);

    if (ParagemDestino == NULL){
        printf("%s: no such stop.\n", palavra);
        leAteFimLinha();
        return;
    }

    else if (carreira->headLigacoes != NULL && 
        strcmp(ParagemOrigem->nome, carreira->ultimaLigacao->paragemDestino->nome) != STRING_IGUAL
            && strcmp(ParagemDestino->nome, carreira->headLigacoes->paragemOrigem->nome) != STRING_IGUAL){
        printf("link cannot be associated with bus line.\n");
        leAteFimLinha();
        return;
    }

    leArgumento(palavra);
    custo = strtod(palavra, NULL);
    leArgumento(palavra);
    duracao = strtod(palavra, NULL);

    if (custo < 0 || duracao < 0){
        printf("negative cost or duration.\n");
        return;
    }

    novaLigacao = criarLigacao(ParagemOrigem, ParagemDestino, custo, duracao);
    juntaLigacaoACarreira(carreira, novaLigacao);

    carreira->custo += custo;
    carreira->duracao += duracao;
}

/*Função que imprime as carreiras de uma paragem*/
void printListaCarreiras(ListaCarreiras *headListaCarreiras){
    while(headListaCarreiras != NULL){
        printf(" %s", headListaCarreiras->nomeCarreira);

        if(headListaCarreiras->next == NULL){
            putchar('\n');
        }

        headListaCarreiras = headListaCarreiras->next;
    }
}

/*Função que comanda as interseções*/
void comandoIntersecao(Paragem *headParagens){
    Paragem *paragem = encontrarUltimaParagem(headParagens);

    while(paragem != NULL){
        /*se tiver mais que uma carreira*/
        if(paragem->numCarreiras > 1){
            printf("%s %d:", paragem->nome, paragem->numCarreiras);

            printListaCarreiras(paragem->headListaCarreiras);
        }
        
        paragem = paragem->prev;
    }
}

/*Função que apaga todas as ligações criadas*/
void apagaLigacoes(Ligacao *headLigacoes){
    Ligacao *aux;

    while(headLigacoes != NULL){
        aux = headLigacoes->next;

        free(headLigacoes);

        headLigacoes = aux;
    }

}

/*Função que apaga uma carreira, incluido toda a memória alocada nessa mesma carreira*/
void apagaCarreira(Carreira *carreira){
    free(carreira->nome);
    apagaLigacoes(carreira->headLigacoes);
    free(carreira);
}

/*Função que apaga todas as carreiras criadas*/
void apagaCarreiras(Carreira *headCarreiras){
    Carreira *aux;

    while(headCarreiras != NULL){
        aux = headCarreiras->next;
        apagaCarreira(headCarreiras);
        headCarreiras = aux;
    }
}

/*Função que apaga de uma paragem um ponteiro de uma carreira dada*/
void apagaCarreiraEmListaCarreiras(Paragem *headParagens, char *nomeCarreira){
    ListaCarreiras *prev = NULL, *aux = headParagens->headListaCarreiras;

    while(aux != NULL){
        if(strcmp(aux->nomeCarreira, nomeCarreira) == STRING_IGUAL){
            if(aux == headParagens->headListaCarreiras){
                headParagens->headListaCarreiras = aux->next;           
            
            }else{
                prev->next = aux->next; 
            }

            headParagens->numCarreiras--;
            free(aux->nomeCarreira);
            free(aux);
            return;
        }
        prev = aux;
        aux = aux->next;
    }

}

/*Função que apaga os ponteiros das carreiras de todas as paragens*/
void apagaCarreiraEmParagens(Paragem *headParagens, char *carreira){

    while(headParagens != NULL){
        apagaCarreiraEmListaCarreiras(headParagens, carreira);
        headParagens = headParagens->next;
    }
}

/*Função que elimina uma carreira*/
Carreira *eliminaCarreira(Carreira *headCarreiras, Paragem *headParagens){
    char palavra[MAX];
    Carreira *carreira;

    leArgumento(palavra);

    carreira = encontrarCarreira(headCarreiras, palavra);

    if(carreira == NULL){
        printf("%s: no such line.\n", palavra);
        return headCarreiras;
    }

    apagaCarreiraEmParagens(headParagens, carreira->nome);

    /*se for a primeira*/
    if(carreira == headCarreiras){
        headCarreiras = carreira->next;
        /*se houverem mais carreiras a seguir*/
        if(carreira->next != NULL){
            carreira->next->prev = NULL;
        }
    }

    /*se for a ultima carreira e não é única*/
    else if(carreira->next == NULL){
        carreira->prev->next = NULL;
    }

    /*se estiver no meio de duas carreiras*/
    else{
        carreira->prev->next = carreira->next;
        carreira->next->prev = carreira->prev;
    }

    apagaCarreira(carreira);

    return headCarreiras;
}

/*Função que atualiza a paragem na carreira, caso esta exista*/
void atualizarParagemEmCarreira(Carreira *carreira, Paragem *paragem){
    Ligacao *ligacao = carreira->headLigacoes, *aux;

    while(ligacao != NULL){
        aux = ligacao->next;

        /*se for a primeira ligação*/
        if((ligacao->paragemOrigem == paragem || ligacao->paragemDestino == paragem) &&
                carreira->headLigacoes == ligacao && ligacao->next == NULL){
            carreira->headLigacoes = NULL;
            carreira->ultimaLigacao = NULL;
            carreira->custo = 0;
            carreira->duracao = 0;
            carreira->numParagens = 0;
            if(ligacao->paragemOrigem == paragem){
                apagaCarreiraEmListaCarreiras(ligacao->paragemDestino, carreira->nome);
            }
            else{
                apagaCarreiraEmListaCarreiras(ligacao->paragemOrigem, carreira->nome);
            }
            free(ligacao);
            /*não existe mais ligações para verificar*/
        }

        else if(ligacao->paragemOrigem == paragem && carreira->headLigacoes == ligacao 
                && ligacao->next != NULL){
            carreira->headLigacoes = ligacao->next;
            carreira->custo -= ligacao->custo;
            carreira->duracao -= ligacao->duracao;     
            carreira->numParagens--;
            ligacao->next->prev = NULL;
            free(ligacao);
        }

        else if(ligacao->paragemDestino == paragem){
            /*se for a ultima paragem de destino*/
            if(ligacao->next == NULL){
                carreira->ultimaLigacao = ligacao->prev;
                ligacao->prev->next = NULL;
                carreira->custo -= ligacao->custo;
                carreira->duracao -= ligacao->duracao;
                carreira->numParagens--;
                free(ligacao);

            }
            /*a paragem estará no meio de duas ligações*/
            else{
                ligacao->next->custo += ligacao->custo;
                ligacao->next->duracao += ligacao->duracao;
                ligacao->next->paragemOrigem = ligacao->paragemOrigem;

                if(ligacao == carreira->headLigacoes){
                    carreira->headLigacoes = ligacao->next;
                    ligacao->next->prev = NULL;
                }
                else{
                    ligacao->prev->next = ligacao->next;
                    ligacao->next->prev = ligacao->prev;
                }
                carreira->numParagens--;
                free(ligacao);
            }
            
        }

        ligacao = aux;
        
    }
}

/*Função que elimina paragens*/
Paragem *eliminaParagem(Carreira *headCarreiras, Paragem *headParagem){
    char palavra[MAX];
    Paragem *paragem;

    leArgumento(palavra);
    paragem = encontrarParagem(headParagem, palavra);

    /*se não encontrar a paragem a ser eliminada*/
    if(paragem == NULL){
        printf("%s: no such stop.\n", palavra);
        return headParagem;
    }

    while(headCarreiras != NULL){
        atualizarParagemEmCarreira(headCarreiras, paragem);

        headCarreiras = headCarreiras->next;
    }
    /*primeira paragem*/
    if(paragem == headParagem){
        headParagem = paragem->next;
        if (paragem->next != NULL)
            paragem->next->prev = NULL;
    }
    /*ultima paragem e existe mais que uma paragem*/
    else if(paragem->next == NULL){
       paragem->prev->next = NULL; 
    }
    /*qualquer paragem no meio*/
    else{
        paragem->prev->next = paragem->next;
        paragem->next->prev = paragem->prev;
    }

    apagaParagem(paragem);

    return headParagem;
}

void noMemory(){

    printf("No memory.");
    exit(0);
}