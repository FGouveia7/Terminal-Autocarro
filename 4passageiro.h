//
// Created by franc on 16/04/2025.
//

#ifndef INC_4FILA_H
#define INC_4FILA_H
#include <string>
passageiro* cria_passageiros(string Pnomes[], passageiro* fila);
bool existe_bilhete(passageiro* fila, int ticket);
void adicionar_passageiro_fila(passageiro*& fila_espera, passageiro* novo);
bool remover_passageiro_por_bilhete(paragem* pAtual, autocarro* aut, int bilhete);
#endif //INC_4FILA_H