//
// Created by franc on 16/04/2025.
//

#ifndef PARAGEM_H
#define PARAGEM_H
#include "2estruturas.h"

paragem* criar_paragem(string paragens[], int quantidade);
void apagar_arvore_bilhetes(noBST* raiz);
void apagar_passageiros(passageiro* p);
bool remover_paragem_por_nome(paragem*& rota, const string& nome);
#endif //PARAGEM_H
