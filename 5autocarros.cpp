//
// Created by franc on 16/04/2025.
//
#include "2estruturas.h"
#include <iomanip>
#include <iostream>
#include "3nomes.h"
#include "4passageiro.h"
#include "5autocarros.h"
#include "6matricula.h"
#include "7arvorebinaria.h"
#include "8paragem.h"
using namespace std;

/**

 * Inicia um autocarro com capacidade aleatória entre 5 e 10 passageiros,
 * lista de passageiros vazia e condutor com nome próprio e apelido criados a partir dos ficheiros txt.
 *
 * @param Pnomes Array de strings contendo possíveis nomes próprios para o condutor.
 * @param Unomes Array de strings contendo possíveis apelidos para o condutor.
 * @return autocarro* Apontador para o autocarro recém-criado.
 */
autocarro* criar_autocarro(string Pnomes[], string Unomes[]) {
    autocarro* novo = new autocarro;

    novo->matricula = cria_matricula();
    novo->capacidade = rand() % 6 + 5;
    novo->passageiros = nullptr;
    novo->proximo = nullptr;
    novo->condutor.Pnome_motorista = criar_nomes(Pnomes, 44);
    novo->condutor.Unome_motorista = criar_nomes(Unomes, 44);

    return novo;
}
//-----------------------------------------------------
/**
 * Adiciona um autocarro ao final da fila.
 * Esta função insere um novo autocarro no fim de uma lista ligada que representa
 * A fila de autocarros caso a fila esteja vazia, o novo autocarro será o primeiro elemento.
 * @param fila Apontador para o primeiro autocarro da fila (pode ser nulo).
 * @param novo Apontador para o novo autocarro a adicionar à fila.
 */
void adicionar_autocarro_fila(autocarro*& fila, autocarro* novo) {
    novo->proximo = nullptr;
    if (!fila) {
        fila = novo;
        return;
    }
    autocarro* aux = fila;
    while (aux->proximo) {
        aux = aux->proximo;
    }
    aux->proximo = novo;
}


//--------------------------------------------------
/**
 * Remove o primeiro autocarro da fila.
 * Esta função remove o primeiro autocarro de uma lista ligada que representa
 * a fila de autocarros. Se a fila estiver vazia, devolve um apontador nulo.
 * O autocarro removido é devolvido com o seu apontador para o próximo definido como nulo.
 *
 * @param fila Apontador para o primeiro autocarro da fila (pode ser modificado).
 * @return Apontador para o autocarro removido, ou nullptr se a fila estiver vazia.
 */
autocarro* remover_autocarro_fila(autocarro*& fila) {
    if (fila == nullptr) {
        return nullptr;
    }
    autocarro* removido = fila;
    fila = fila->proximo;
    removido->proximo = nullptr;
    return removido;
}

//--------------------------------------------------
/**

 * Cria um número aleatório de paragens (entre 4 e 9) e adiciona paragens únicas ao percurso do terminal,
 * garantindo que não haja nomes repetidos no percurso.
 * @param terminal Referência à fila do terminal onde será armazenado o percurso.
 * @param Nparagens Array de strings com nomes possíveis para as paragens.
 * @param total_paragens Número total de paragens disponíveis no array Nparagens.
 * @return void
 */
void criar_percurso_random(fila& terminal, string Nparagens[], int total_paragens) {
    int num_paragens = rand() % 6 + 4;
    terminal.rota = nullptr;
    paragem* atual = nullptr;

    for (int i = 0; i < num_paragens; ++i) {
        paragem* nova;
        string nome_escolhido;
        do {
            nova = criar_paragem(Nparagens, total_paragens);
            nome_escolhido = nova->nome;
        } while (nome_existe(nome_escolhido, terminal.rota));
        nova->nome = nome_escolhido;
        if (terminal.rota == nullptr) {
            terminal.rota = nova;
            atual = nova;
        } else {
            atual->proxima = nova;
            atual = nova;
        }
    }
}
//----------------------------------------------------------------------------------------
/**
 * Transfere passageiros da fila de espera para o autocarro até este atingir a capacidade máxima.
 * Esta função move passageiros da fila de espera para o autocarro, respeitando o limite de capacidade
 * do autocarro. Os passageiros são inseridos na lista ligada de passageiros do autocarro.
 * Durante o processo, são apresentados no ecrã os nomes dos passageiros que entram, bem como mensagens
 * de aviso quando o autocarro fica cheio ou quando não há mais passageiros na fila.
 *
 * @param autocarro Apontador para o autocarro onde os passageiros serão adicionados.
 * @param fila_espera Apontador para o início da fila de espera (pode ser modificada à medida que os passageiros são removidos).
 */
void adicionar_passageiros_autocarro(autocarro*& autocarro, passageiro*& fila_espera) {
    passageiro* pAtual = fila_espera;
    cout << "+--------------------------------------------------------------------+" << endl;
    while (pAtual != nullptr && autocarro->capacidade > 0) {
        passageiro* novoPassageiro = pAtual;
        pAtual = pAtual->proximo;
        fila_espera = pAtual;

        novoPassageiro->proximo = nullptr;

        if (autocarro->passageiros == nullptr) {
            autocarro->passageiros = novoPassageiro;
        } else {
            passageiro* aux = autocarro->passageiros;
            while (aux->proximo != nullptr) {
                aux = aux->proximo;
            }
            aux->proximo = novoPassageiro;
        }

        autocarro->capacidade--;

        string texto = " Passageiro " + novoPassageiro->Nome_passageiro + " entrou no autocarro " + autocarro->matricula + " com bilhete " + to_string(novoPassageiro->bilhete);
        cout << "| " << left << setw(66) << texto << "|" << endl;
    }
    cout << "+--------------------------------------------------------------------+" << endl;
    if (autocarro->capacidade == 0) {
        string texto = " O autocarro " + autocarro->matricula + " esta cheio. Nao podem entrar mais passageiros.";
        cout << "| " << left << setw(66) << texto << "|" << endl;
        cout << "+--------------------------------------------------------------------+" << endl;
    } else if (fila_espera == nullptr) {
        string texto = " Nao ha mais passageiros na fila de espera.";
        cout << "| " << left << setw(66) << texto << "|" << endl;
        cout << "+--------------------------------------------------------------------+" << endl;
    }
}
//--------------------------------------------
/**
 * Liberta a memória ocupada pela lista de passageiros do autocarro e, por fim, apaga o próprio autocarro.
 *
 * @param aut Apontador para o autocarro a apagar.
 * @return void
 */
void apagar_autocarro(autocarro* aut) {
    if (aut == nullptr) return;
    passageiro* atual = aut->passageiros;
    while (atual != nullptr) {
        passageiro* temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    delete aut;
}
//--------------------------------------------
/**
 * Move o autocarro para a próxima paragem na rota.
 * Esta função atualiza a posição de um autocarro, movendo-o da sua paragem atual
 * para a próxima na rota. Caso o autocarro esteja na última paragem, este será removido
 * do sistema. Antes de se mover, o autocarro descarrega os passageiros cuja paragem de destino
 * corresponde à paragem atual.
 *
 * @param aut Apontador para o autocarro que será movido (pode ser definido como nullptr se removido).
 * @param terminal Estrutura que contém a rota (lista ligada de paragens).
 */
void mover_autocarro_para_proxima_paragem(autocarro*& aut, fila& terminal) {
    if (aut == nullptr || aut->paragem_atual == nullptr) {
        cout << "Erro: Autocarro ou paragem invalida!" << endl;
        return;
    }
    paragem* paragem_atual = aut->paragem_atual;
    if (paragem_atual != terminal.rota) {
        remover_passageiros_autocarro(*aut, paragem_atual);
    }
    if (paragem_atual->proxima == nullptr) {
        paragem_atual->Paragem_auto = nullptr;

        apagar_autocarro(aut);
        aut = nullptr;
        return;
    }
    paragem* proxima_paragem = paragem_atual->proxima;
    paragem_atual->Paragem_auto = nullptr;
    aut->paragem_atual = proxima_paragem;
    proxima_paragem->Paragem_auto = aut;
}
//------------------------------------------
/**
 * Percorre a lista de passageiros do autocarro e remove alguns passageiros aleatoriamente.
 * Para cada passageiro removido, o respetivo bilhete é registado na árvore de bilhetes que saíram da paragem atual.
 *
 * @param autocarro Referência para o autocarro de onde os passageiros serão removidos.
 * @param atual Apontador para a paragem atual onde os bilhetes removidos serão registados.
 * @return void
 */
void remover_passageiros_autocarro(autocarro& autocarro, paragem* atual) {
    passageiro* pAnterior = nullptr;
    passageiro* pAtual = autocarro.passageiros;
    while (pAtual != nullptr) {
        if (rand() % 100 < 25) {
            if (pAnterior == nullptr) {
                autocarro.passageiros = pAtual->proximo;
            } else {
                pAnterior->proximo = pAtual->proximo;
            }
            inserir_na_arvore(atual->bilhetes_Qsairam, pAtual->bilhete);
            passageiro* temp = pAtual;
            pAtual = pAtual->proximo;
            delete temp;
        } else {
            pAnterior = pAtual;
            pAtual = pAtual->proximo;
        }
    }
}
//--------------------------------------------
/**
 * Procura na lista ligada de autocarros ativos o autocarro com a matrícula indicada e atualiza o nome e apelido do condutor.
 * Caso o autocarro não seja encontrado, exibe uma mensagem no ecrã.
 *
 * @param autocarros_ativos Apontador para o primeiro autocarro da lista de autocarros ativos.
 * @param matricula Matrícula do autocarro cujo condutor será alterado.
 * @param novoPnome Novo nome próprio do condutor.
 * @param novoUnome Novo apelido do condutor.
 * @return void
 */
void alterar_motorista(autocarro* autocarros_ativos, const string& matricula, const string& novoPnome, const string& novoUnome) {
    autocarro* aut = autocarros_ativos;
    while (aut != nullptr) {
        if (aut->matricula == matricula) {
            aut->condutor.Pnome_motorista = novoPnome;
            aut->condutor.Unome_motorista = novoUnome;
            return;
        }
        aut = aut->proximo;
    }
    cout << "Autocarro com matrícula " << matricula << " nao foi encontrado.\n";
}
//--------------------------------------------
