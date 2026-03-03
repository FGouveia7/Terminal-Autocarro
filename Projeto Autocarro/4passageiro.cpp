//
// Created by franc on 16/04/2025.
//
#include "2estruturas.h"
#include "3nomes.h"
#include "4passageiro.h"
#include "time.h"
#include <fstream>
#include <iostream>
#include "7arvorebinaria.h"
#include "8paragem.h"
using namespace std;
//------------------------------------------
/**
* Função que cria dinamicamente um novo passageiro com um nome aleatório e um bilhete único.
*
* @param Pnomes - array de strings com possíveis nomes para o passageiro
* @param fila - apontador para a fila de passageiros já existentes, usada para verificar se o bilhete gerado é único
* @return - apontador para o novo passageiro criado
*/
passageiro* cria_passageiros(string Pnomes[], passageiro* fila) {
    passageiro* p = new passageiro;
    p->Nome_passageiro = criar_nomes(Pnomes,44);
    int bilhete;
    do {
        bilhete = rand() % 2000 + 100;
    } while(existe_bilhete(fila, bilhete));
    p->bilhete = bilhete;
    p->proximo = nullptr;

    return p;
}
//------------------------------------------
/**
 * Percorre a lista ligada de passageiros e verifica se algum deles possui o bilhete indicado.
 *
 * @param fila Apontador para o  passageiro da fila.
 * @param bilhete Número do bilhete a procurar na fila.
 * @return bool Retorna true se o bilhete for encontrado; caso contrário, retorna false.
 */
bool existe_bilhete(passageiro* fila, int bilhete) {
    while (fila != nullptr) {
        if (fila->bilhete == bilhete)
            return true;
        fila = fila->proximo;
    }
    return false;
}
//------------------------------------------
/**
 * Adiciona um passageiro ao final da fila de espera.
 * Esta função insere um novo passageiro no fim de uma lista ligada que representa
 * a fila de espera. Se a fila estiver vazia, o novo passageiro será o primeiro elemento.
 * @param fila_espera Apontador para o primeiro passageiro da fila de espera (pode ser nulo).
 * @param novo Apontador para o novo passageiro a adicionar à fila.
 */
void adicionar_passageiro_fila(passageiro*& fila_espera, passageiro* novo) {
    novo->proximo = nullptr;
    if (fila_espera == nullptr) {
        fila_espera = novo;
    } else {
        passageiro* aux = fila_espera;
        while (aux->proximo != nullptr) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
}
//------------------------------------------
/**
 * Procura na lista ligada de passageiros do autocarro um passageiro com o bilhete indicado e remove-o.
 * Após a remoção, regista o bilhete na árvore de bilhetes que saíram da paragem atual.
 *
 * @param pAtual Apontador para a paragem atual onde se regista a saída dos bilhetes.
 * @param aut Apontador para o autocarro que contém a lista de passageiros.
 * @param bilhete Número do bilhete do passageiro a remover.
 * @return bool Retorna true se o passageiro com o bilhete foi encontrado e removido; false caso contrário.
 */
bool remover_passageiro_por_bilhete(paragem* pAtual, autocarro* aut, int bilhete) {
    if (aut == nullptr || aut->passageiros == nullptr) return false;

    passageiro* atual = aut->passageiros;
    passageiro* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->bilhete == bilhete) {
            int bilhete_removido = atual->bilhete;

            if (anterior == nullptr) {
                aut->passageiros = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            delete atual;
            inserir_na_arvore(pAtual->bilhetes_Qsairam, bilhete_removido); // Correto agora
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return false;
}


