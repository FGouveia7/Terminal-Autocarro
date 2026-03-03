//
// Created by franc on 16/04/2025.
//

#ifndef INC_2ESTRUTURAS_H
#define INC_2ESTRUTURAS_H
#include <string>
using namespace std;

struct noBST {
    int bilhete;
    noBST* esquerda;
    noBST* direita;
};
struct no_arvore {
    int bilhete;
    no_arvore* esq;
    no_arvore* dir;
};
//---------------------------------------------------------------------------------------
struct motorista {
    string Pnome_motorista;
    string Unome_motorista;
};
//---------------------------------------------------------------------------------------
struct passageiro {
    string Nome_passageiro;
    int bilhete;
    passageiro* proximo;
};
struct paragem;
//--------------------------------------------------------------------------------------------
struct autocarro {
    string matricula;
    int capacidade;
    passageiro* passageiros;
    autocarro* proximo;
    motorista condutor;
    paragem* paragem_atual;
};
//--------------------------------------------------------------------------------------------
struct paragem {
    string nome;
    autocarro* Paragem_auto;
    passageiro* P_sairam;
    noBST *bilhetes_Qsairam;
    paragem* proxima;
};

//----------------------------------------------------------------------------------------------
struct fila {
    passageiro* fila_espera;
    autocarro* autocarros_ativos;
    paragem* rota;
};
//--------------------------------------------------------------------------------------------

#endif //INC_2ESTRUTURAS_H
