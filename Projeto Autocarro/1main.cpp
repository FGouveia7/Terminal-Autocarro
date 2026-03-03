#include <iostream>
#include <time.h>
#include <fstream>
#include "2estruturas.h"
#include "3nomes.h"
#include "4passageiro.h"
#include "5autocarros.h"
#include "10imprimir.h"
#include "9menus.h"
using namespace std;

int main() {
    srand(time(nullptr));

    fila fila_inicial;
    fila_inicial.fila_espera = nullptr;
    fila_inicial.rota = nullptr;
    fila_inicial.autocarros_ativos = nullptr;
    string Pnomes[44];
    string Unomes[97];
    string Nparagens[54];
    ler_nomes(Pnomes, Unomes, 44);
    ler_paragens(Nparagens, 54);
    criar_percurso_random(fila_inicial, Nparagens, 44);
    for (int i = 0; i < 30; i++) {
        passageiro* novo = cria_passageiros(Pnomes, fila_inicial.fila_espera);
        adicionar_passageiro_fila(fila_inicial.fila_espera, novo);
    }
    autocarro* novo_autocarro = criar_autocarro(Pnomes, Unomes);
    if (fila_inicial.rota != nullptr) {
        novo_autocarro->paragem_atual = fila_inicial.rota;
        fila_inicial.rota->Paragem_auto = novo_autocarro;
    }
    adicionar_autocarro_fila(fila_inicial.autocarros_ativos, novo_autocarro);
    adicionar_passageiros_autocarro(novo_autocarro, fila_inicial.fila_espera);
    imprime_estado(fila_inicial);

    string opcao;

    while (true) {
        cout << "\nEscolha uma opcao: (s) Seguinte, (o) Opcoes: ";
        cin >> opcao;

        if (opcao == "s") {
            menu_s(fila_inicial, fila_inicial.autocarros_ativos, fila_inicial.fila_espera, Pnomes, Unomes);
        } else if (opcao == "o") {
            menu_o(fila_inicial);
        } else {
            cout << "Opcao invalida!" << endl;
        }

    }
    return 0;
}

