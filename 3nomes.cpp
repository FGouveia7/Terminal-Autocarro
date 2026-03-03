//
// Created by franc on 12/04/2025.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "3nomes.h"
#include "2estruturas.h"
using namespace std;
//------------------------------------------
/**
* Função que lê nomes de dois ficheiros de texto
* e armazena-os em dois arrays de strings.
*
* @param Pnomes - array onde serão guardados os primeiros nomes lidos
* @param Unomes - array onde serão guardados os últimos nomes lidos
* @param tamanho - número máximo de nomes a serem lidos dos ficheiros
*/

void ler_nomes(string Pnomes[], string Unomes[], int tamanho) {
    ifstream primeiro("primeiro_nome.txt");
    ifstream ultimo("ultimo_nome.txt");
    if (!primeiro.is_open() || !ultimo.is_open()) {
        cout << "Erro ao abrir os ficheiros. Verifique o caminho e as permissoes." << endl;
        exit(1);
    }
    string linhaPnome, linhaUnome;
    int i = 0;
    while (getline(primeiro, linhaPnome) && getline(ultimo, linhaUnome) && i < tamanho) {
        Pnomes[i] = linhaPnome;
        Unomes[i] = linhaUnome;
        i++;
    }
    primeiro.close();
    ultimo.close();
}
//------------------------------------------
/**
 *Lê os nomes das paragens de um ficheiro e armazena-os num array.
 * Esta função abre o ficheiro "paragens.txt", lê linha a linha e armazena o conteúdo
 * no array fornecido até atingir o número máximo de elementos definido por `tamanho`.
 * Caso o ficheiro não consiga ser aberto, a função termina o programa com um código de erro.
 * @param Nparagens Array de strings onde serão armazenados os nomes das paragens.
 * @param tamanho Número máximo de paragens a ler do ficheiro.
 */
void ler_paragens(string Nparagens[], int tamanho) {
    ifstream paragens("paragens.txt");
    if (!paragens.is_open()) {
        cout << "Erro ao abrir os ficheiros. Verifique o caminho e as permissoes." << endl;
        exit(1);
    }
    string linhaParagens;
    int i = 0;
    while (getline(paragens, linhaParagens) && i < tamanho) {
        Nparagens[i] = linhaParagens;
        i++;
    }
    paragens.close();
}
//------------------------------------------
/**
* Função que seleciona aleatoriamente um nome de um array de nomes.
*
* @param nomes - array de strings que contém os nomes possíveis
* @param tamanho - número total de nomes disponíveis no array
* @return - nome seleccionado aleatoriamente do array
*/

string criar_nomes(string nomes [], int tamanho) {
    return nomes[rand() % tamanho];
}
//------------------------------------------
/**
 *Verifica se existe uma paragem com o nome indicado na lista ligada.
 * Esta função percorre uma lista ligada de paragens e verifica se existe uma paragem
 * cujo nome corresponde ao nome fornecido.
 * @param nome Nome da paragem a procurar.
 * @param inicio Apontador para o primeiro elemento da lista ligada de paragens.
 * @return true se o nome existir na lista, false caso contrário.
 */

bool nome_existe(string nome, paragem* inicio) {
    while (inicio != nullptr) {
        if (inicio->nome == nome) return true;
        inicio = inicio->proxima;
    }
    return false;
}