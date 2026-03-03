//
// Created by franc on 16/04/2025.
//

#ifndef INC_5AUTOCARROS_H
#define INC_5AUTOCARROS_H
#include "2estruturas.h"

autocarro* criar_autocarro(string Pnomes[], string Unomes[]);
void adicionar_autocarro_fila(autocarro*& fila, autocarro* novo);
autocarro* remover_autocarro_fila(autocarro*& fila);
void criar_percurso_random(fila& terminal, string Nparagens[], int total_paragens);
void adicionar_passageiros_autocarro(autocarro*& autocarro, passageiro*& fila_espera);
void remover_passageiros_autocarro(autocarro& autocarro,paragem* atual);
void mover_autocarro_para_proxima_paragem(autocarro*& aut, fila& terminal);
void apagar_autocarro(autocarro* aut);
void alterar_motorista(autocarro* autocarros_ativos, const string& matricula, const string& novoPnome, const string& novoUnome);
#endif //INC_5AUTOCARROS_H

