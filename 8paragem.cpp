//
// Created by franc on 16/04/2025.
//
#include <iostream>
#include "8paragem.h"
#include "3nomes.h"
using namespace std;
//------------------------------------------
/**
 * Aloca memória para uma nova paragem e define os seus campos iniciais.
 * O nome da paragem é criado a partir de um array de nomes disponíveis.
 *
 * @param paragens Array de strings contendo nomes possíveis para as paragens.
 * @param quantidade Número total de nomes disponíveis no array.
 * @return Apontador para a nova paragem criada e iniciada.
 */
paragem* criar_paragem(string paragens[], int quantidade) {
    paragem* nova = new paragem;
    nova->nome = criar_nomes(paragens,quantidade);
    nova->Paragem_auto = nullptr;
    nova->P_sairam = nullptr;
    nova->bilhetes_Qsairam = nullptr;
    nova->proxima = nullptr;
    return nova;
}
//------------------------------------------
/**
 * Procura na lista ligada da rota a paragem com o nome indicado e remove-a.
 * Liberta também a memória associada à árvore de bilhetes e aos passageiros dessa paragem.
 *
 * @param rota Apontador para a lista ligada da rota (pode ser alterado se a primeira paragem for removida).
 * @param nome Nome da paragem a remover.
 * @return true se a paragem foi removida com sucesso, false caso contrário.
 */
bool remover_paragem_por_nome(paragem*& rota, const string& nome) {
    paragem* atual = rota;
    paragem* anterior = nullptr;

    while (atual) {
        if (atual->nome == nome) {
            if (anterior) anterior->proxima = atual->proxima;
            else rota = atual->proxima;

            apagar_arvore_bilhetes(atual->bilhetes_Qsairam);
            apagar_passageiros(atual->P_sairam);

            delete atual;
            cout << "Paragem \"" << nome << "\" removida com sucesso.\n";
            return true;
        }
        anterior = atual;
        atual = atual->proxima;
    }

    cout << "Paragem \"" << nome << "\" nao encontrada.\n";
}
//------------------------------------------
/**
 * Liberta a memória de uma lista ligada de passageiros.
 * Esta função percorre a lista ligada de passageiros e elimina todos os nós,
 * libertando a memória associada a cada passageiro.
 *
 * @param p Apontador para o primeiro passageiro da lista.
 */
void apagar_passageiros(passageiro* p) {
    while (p) {
        passageiro* temp = p;
        p = p->proximo;
        delete temp;
    }
}
//------------------------------------------
/**
 * Liberta a memória de todos os nós de uma árvore binária de busca (BST) de bilhetes.
 * Esta função elimina recursivamente todos os nós da árvore BST começando pela raiz,
 * libertando a memória alocada para cada nó.
 *
 * @param raiz Apontador para a raiz da árvore BST de bilhetes.
 */
void apagar_arvore_bilhetes(noBST* raiz) {
    if (!raiz) return;
    apagar_arvore_bilhetes(raiz->esquerda);
    apagar_arvore_bilhetes(raiz->direita);
    delete raiz;
}