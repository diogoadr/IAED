#ifndef UTILS_PROJECT_H
#define UTILS_PROJECT_H

typedef struct listaCarreiras{
    char *nomeCarreira;
    struct listaCarreiras *next;
} ListaCarreiras;

typedef struct paragem {
    char *nome;
    double latitude, longitude;
    ListaCarreiras *headListaCarreiras;
    int numCarreiras;
    struct paragem *prev, *next;
} Paragem;

typedef struct ligacao {
    Paragem *paragemOrigem, *paragemDestino;
    double custo, duracao;
    struct ligacao *prev, *next;
} Ligacao;

typedef struct carreira {
    char *nome;
    double custo, duracao;
    Ligacao *headLigacoes, *ultimaLigacao;
    int numParagens;
    struct carreira *prev, *next;
} Carreira;

/*PARAGENS*/
Paragem *encontrarUltimaParagem(Paragem *headParagens);
void printTodasParagens(Paragem *headParagens);
Paragem *encontrarParagem(Paragem *headParagens, char *palavra);
Paragem *criarParagem(Paragem *headParagens, char palavra[MAX]);
Paragem *comandoParagem(Paragem *headParagens);
void apagaListaCarreira(ListaCarreiras *headListaCarreira);
void apagaParagem(Paragem *paragem);
void apagaParagens(Paragem *headParagens);
int encontrarCarreiraEmParagem(char *nomeCarreira, ListaCarreiras *listaHeadCarreiras);
void adicionaCarreiraAParagem(char *nomeCarreira, Paragem *paragem);
void printListaCarreiras(ListaCarreiras *headListaCarreiras);
void comandoIntersecao(Paragem *headParagens);
void apagaCarreiraEmListaCarreiras(Paragem *headParagens, char *nomeCarreira);
void apagaCarreiraEmParagens(Paragem *headParagens, char *carreira);
Paragem *eliminaParagem(Carreira *headCarreiras, Paragem *headParagem);

/*CARREIRAS*/
Carreira *encontrarCarreira(Carreira *headCarreiras, char *palavra);
Carreira *encontrarUltimaCarreira(Carreira *headCarreiras);
void printCarreira(Carreira *carreira);
void printTodasCarreiras(Carreira *headCarreiras);
Carreira *criaCarreira(Carreira *headCarreiras, char *palavra);
void printParagensDeCarreira(Carreira *headCarreiras);
void printParagensDeCarreiraInverso(Carreira *headCarreiras);
Carreira *comandoCarreira(Carreira *headCarreiras);
void apagaCarreira(Carreira *carreira);
void apagaCarreiras(Carreira *headCarreiras);
Carreira *eliminaCarreira(Carreira *headCarreiras, Paragem *headParagens);
void atualizarParagemEmCarreira(Carreira *carreira, Paragem *paragem);

/*LIGACOES*/
Ligacao *criarLigacao(Paragem *ParagemOrigem, Paragem *ParagemDestino, 
                        double custo, double duracao);
void comandoLigacoes(Paragem *headParagens, Carreira *headCarreiras);
void apagaLigacoes(Ligacao *headLigacoes);

/*END PROGRAM*/
void noMemory();

#endif