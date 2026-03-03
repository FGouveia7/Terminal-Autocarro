//
// Created by franc on 16/04/2025.
//
#include "2estruturas.h"
#include "7arvorebinaria.h"
#include <iostream>
using namespace std;
/**
 * Insere recursivamente o bilhete na posição correta da árvore binária,
 * criando um novo nó caso o local esteja vazio.
 * Ignora a inserção se o bilhete já existir na árvore.
 *
 * @param raiz Apontador para o apontador da raiz da árvore onde será feita a inserção.
 * @param bilhete Valor do bilhete a inserir na árvore.
 * @return void
 */
void inserir_na_arvore(noBST*& raiz, int bilhete) {
    if (raiz == nullptr) {
        raiz = new noBST{bilhete, nullptr, nullptr};
    } else if (bilhete < raiz->bilhete) {
        inserir_na_arvore(raiz->esquerda, bilhete);
    } else if (bilhete > raiz->bilhete) {
        inserir_na_arvore(raiz->direita, bilhete);
    }
}
//------------------------------------------
/**
 * Procura o bilhete na árvore e, caso o encontre, remove o nó correspondente
 * usando a função auxiliar remover_noBST_com_pai.
 * Se o bilhete não existir, imprime uma mensagem de aviso.
 *
 * @param raiz Apontador para a raiz da árvore onde será feita a remoção.
 * @param bilhete Valor do bilhete a remover.
 * @return Apontador para a raiz da árvore após a remoção (pode ser alterada).
 */
noBST* remover_bilhete_arvoreBST(noBST* raiz, int bilhete) {
    noBST* atual = raiz;
    noBST* pai = nullptr;

    while (atual != nullptr) {
        if (bilhete == atual->bilhete) {
            return remover_noBST_com_pai(raiz, atual, pai);
        } else if (bilhete < atual->bilhete) {
            pai = atual;
            atual = atual->esquerda;
        } else {
            pai = atual;
            atual = atual->direita;
        }
    }

    cout << "Bilhete " << bilhete << " nao encontrado na arvore.\n";
    return raiz;
}
//------------------------------------------
/**
 * Remove um bilhete da árvore BST associada a uma paragem específica.
 * Esta função procura na lista ligada de paragens a paragem com o nome indicado e,
 * se encontrada, remove o bilhete especificado da sua árvore BST de bilhetes.
 * Caso a paragem não exista, é apresentada uma mensagem de erro.
 *
 * @param rota Apontador para o início da lista ligada de paragens (rota).
 * @param nome_paragem Nome da paragem onde o bilhete deve ser removido.
 * @param bilhete Número do bilhete a remover da árvore BST da paragem.
 */
void remover_bilhete_em_paragem(paragem* rota, const string& nome_paragem, int bilhete) {
    paragem* atual = rota;

    while (atual != nullptr) {
        if (atual->nome == nome_paragem) {
            atual->bilhetes_Qsairam = remover_bilhete_arvoreBST(atual->bilhetes_Qsairam, bilhete);
            cout << "Bilhete " << bilhete << " removido da paragem \"" << nome_paragem << "\".\n";
            return;
        }
        atual = atual->proxima;
    }

    cout << "Paragem \"" << nome_paragem << "\" nao encontrada.\n";
}
//------------------------------------------
/**
 * Trata casos em que o nó a remover tem zero, um ou dois filhos.
 * Caso o nó tenha dois filhos, encontra o predecessor em ordem (máximo da subárvore esquerda),
 * troca os valores e remove o predecessor.
 *
 * @param raiz Apontador para a raiz da árvore (pode ser alterada se o nó a remover for a raiz).
 * @param no Apontador para o nó que deve ser removido.
 * @param pai Apontador para o pai do nó a remover (nullptr se for a raiz).
 * @return Apontador para a raiz da árvore após a remoção (pode ser alterada).
 */
noBST* remover_noBST_com_pai(noBST* raiz, noBST* no, noBST* pai) {
    if (pai == nullptr) {
        if (no->esquerda == nullptr && no->direita == nullptr) {
            raiz = nullptr;
        } else if (no->esquerda != nullptr && no->direita == nullptr) {
            raiz = no->esquerda;
        } else if (no->esquerda == nullptr && no->direita != nullptr) {
            raiz = no->direita;
        } else {
            noBST* temp = no->esquerda;
            pai = no;
            while (temp->direita != nullptr) {
                pai = temp;
                temp = temp->direita;
            }
            swap(no->bilhete, temp->bilhete);
            if (pai == no) {
                pai->esquerda = temp->esquerda;
            } else {
                pai->direita = temp->esquerda;
            }
            delete temp;
            return raiz;
        }

        delete no;
        return raiz;
    }

    // Caso geral: nó tem 0 ou 1 filho
    if (no->esquerda == nullptr && no->direita == nullptr) {
        if (pai->esquerda == no) pai->esquerda = nullptr;
        else pai->direita = nullptr;
    } else if (no->esquerda != nullptr && no->direita == nullptr) {
        if (pai->esquerda == no) pai->esquerda = no->esquerda;
        else pai->direita = no->esquerda;
    } else if (no->esquerda == nullptr && no->direita != nullptr) {
        if (pai->esquerda == no) pai->esquerda = no->direita;
        else pai->direita = no->direita;
    } else {
        noBST* temp = no->esquerda;
        pai = no;
        while (temp->direita != nullptr) {
            pai = temp;
            temp = temp->direita;
        }
        swap(no->bilhete, temp->bilhete);
        if (pai == no) {
            pai->esquerda = temp->esquerda;
        } else {
            pai->direita = temp->esquerda;
        }
        delete temp;
        return raiz;
    }

    delete no;
    return raiz;
}

