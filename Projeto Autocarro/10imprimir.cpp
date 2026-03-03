//
// Created by franc on 16/04/2025.
//
#include <iostream>
#include <fstream>
#include "2estruturas.h"
#include "10imprimir.h"
#include <iomanip>
//------------------------------------------
/**
 * Imprime o estado atual do terminal de autocarros, incluindo a fila de espera, as paragens e os autocarros.
 * Esta função apresenta na consola:
 * - A lista de passageiros na fila de espera, com nome e número do bilhete.
 * - Para cada paragem da rota:
 *     - O nome da paragem.
 *     - Os dados do autocarro que lá se encontra (matrícula e motorista).
 *     - A lista de passageiros dentro desse autocarro, com nome e número do bilhete.
 *
 * @param terminal Referência para a estrutura que contém a informação do terminal, incluindo fila de espera, rota e autocarros ativos.
 */
void imprime_estado(fila &terminal) {
    cout << "\n============================= Terminal de Autocarros EDA =============================\n";

    cout << "\n-------------------------- Fila de Espera --------------------------\n";
    if (terminal.fila_espera == nullptr) {
        cout << "Sem passageiros na fila de espera." << endl;
    } else {
        passageiro* passFila = terminal.fila_espera;
        int col = 0;
        while (passFila != nullptr) {
            cout << left << setw(25) << (passFila->Nome_passageiro + " - " + to_string(passFila->bilhete));
            col++;
            if (col == 3) {
                cout << endl;
                col = 0;
            }
            passFila = passFila->proximo;
        }
        if (col != 0) cout << endl;
    }
    cout << "\n-------------------------------------------------------------------\n";
    paragem* pAtual = terminal.rota;
    while (pAtual != nullptr) {
        cout << "\nParagem: " << pAtual->nome << endl;

        if (pAtual->Paragem_auto != nullptr) {
            autocarro* aAtual = pAtual->Paragem_auto;
            cout << "Autocarro: " << aAtual->matricula << " | Motorista: " << aAtual->condutor.Pnome_motorista << " " << aAtual->condutor.Unome_motorista << endl;
            cout << "Passageiros: ";
            passageiro* passAtual = aAtual->passageiros;
            if (passAtual == nullptr) {
                cout << "Nenhum passageiro a bordo.";
            } else {
                while (passAtual != nullptr) {
                    cout << passAtual->Nome_passageiro << " (" << passAtual->bilhete << ")";
                    if (passAtual->proximo != nullptr) cout << ", ";
                    passAtual = passAtual->proximo;
                }
            }
            cout << endl;
        } else {
            cout << "Nenhum autocarro nesta paragem." << endl;
        }
        cout << endl;
        pAtual = pAtual->proxima;
    }
    cout << "\n======================================================================================\n";
}
//------------------------------------------
/**
 * Faz uma travessia a árvore infixa para imprimir todos os bilhetes,
 * separados por " | ".
 *
 * @param raiz Apontador para o nó raiz da árvore BST de bilhetes.
 */
void imprimir_bilhetes_arvore(noBST* raiz) {
    if (raiz == nullptr) return;
    imprimir_bilhetes_arvore(raiz->esquerda);
    cout << raiz->bilhete << " | ";
    imprimir_bilhetes_arvore(raiz->direita);
}



