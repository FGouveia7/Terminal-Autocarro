#include <fstream>
#include <iostream>
#include "2estruturas.h"
#include "5autocarros.h"
#include "4passageiro.h"
#include "8paragem.h"
#include "7arvorebinaria.h"
#include "9menus.h"
#include "10imprimir.h"

using namespace std;
/**
 * Move cada autocarro ativo para a sua próxima paragem,
 * cria um novo autocarro na primeira paragem se possivel,
 * adiciona passageiros ao autocarro e à fila de espera,
 * e imprime o estado atual do terminal.
 * @param terminal Referência à estrutura do terminal com a rota e filas.
 * @param fila_autocarros_ativos Apontador para a lista ligada dos autocarros ativos.
 * @param fila_espera Apontador para a fila de espera de passageiros.
 * @param Pnomes Array com nomes próprios para criação de passageiros e condutores.
 * @param Unomes Array com apelidos para criação de passageiros e condutores.
 */
void menu_s(fila& terminal, autocarro*& fila_autocarros_ativos, passageiro*& fila_espera, string Pnomes[], string Unomes[]) {
    autocarro* atual = fila_autocarros_ativos;
    autocarro* anterior = nullptr;


    while (atual != nullptr) {
        mover_autocarro_para_proxima_paragem(atual, terminal);
        if (atual == nullptr) {
            if (anterior == nullptr) {
                fila_autocarros_ativos = fila_autocarros_ativos->proximo;
            } else {
                anterior->proximo = atual;
            }
        } else {
            anterior = atual;
        }
        atual = (anterior != nullptr) ? anterior->proximo : fila_autocarros_ativos;
    }
    if (terminal.rota->Paragem_auto == nullptr) {
        autocarro* novo = criar_autocarro(Pnomes, Unomes);
        novo->paragem_atual = terminal.rota;
        terminal.rota->Paragem_auto = novo;
        adicionar_passageiros_autocarro(novo, fila_espera);
        adicionar_autocarro_fila(fila_autocarros_ativos, novo);

    }
    for (int i = 0; i < 15; i++) {
        passageiro* novo = cria_passageiros(Pnomes, terminal.fila_espera);
        adicionar_passageiro_fila(terminal.fila_espera, novo);
    }
    imprime_estado(terminal);
}


//------------------------------------------------------------
/**
 * Apresenta um menu interativo com várias opções para gerir passageiros, bilhetes, motoristas e paragens.
 * Esta função permite ao utilizador executar várias operações relacionadas com a gestão
 * dos autocarros e das paragens, nomeadamente remover passageiros, consultar bilhetes,
 * alterar motorista, remover bilhetes ou paragens, entre outras.
 *
 * @param terminal Estrutura que contém a rota e os autocarros ativos.
 */
void menu_o(fila& terminal) {
    int opcao;
    do {
        cout << "\n _______________________________"  << endl;
        cout << "[         *** Opcoes ***        ]" << endl;
        cout << " _______________________________" << endl;
        cout << "[ 1. Remover Passageiro         ]" << endl;
        cout << "[ 2. Ver Bilhetes por Paragem   ]" << endl;
        cout << "[ 3. Alterar Motorista          ]" << endl;
        cout << "[ 4. Remover Bilhete BST        ]" << endl;
        cout << "[ 5. Remover Paragem            ]" << endl;
        cout << "[ 6. Adicionar Entrada Interm.  ]" << endl;
        cout << "[ 0. Voltar                     ]" << endl;
        cout << " _______________________________" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cout << endl;

        switch (opcao) {
            case 1: {
                int bilhete;
                cout << "Escreva o numero do bilhete que quer remover: ";
                cin >> bilhete;

                bool encontrado = false;
                autocarro* aut = terminal.autocarros_ativos;
                while (aut != nullptr) {
                    if (remover_passageiro_por_bilhete(terminal.rota, aut, bilhete)) {
                        cout << "Passageiro com bilhete " << bilhete << " foi removido do autocarro " << aut->matricula << ".\n";
                        encontrado = true;
                        break;
                    }
                    aut = aut->proximo;
                }

                if (!encontrado) {
                    cout << "Passageiro com bilhete " << bilhete << " nao foi encontrado em nenhum autocarro.\n";
                }
                break;
            }

            case 2: {
                string nome_paragem;
                cin.ignore();
                cout << "Escreva o nome da paragem: ";
                getline(cin, nome_paragem);

                paragem* p = terminal.rota;
                bool encontrada = false;

                while (p != nullptr) {
                    if (p->nome == nome_paragem) {
                        cout << "\nBilhetes que sairam na paragem '" << nome_paragem << "':\n";
                        if (p->bilhetes_Qsairam == nullptr) {
                            cout << "Nenhum bilhete registado nesta paragem.\n";
                        } else {
                            imprimir_bilhetes_arvore(p->bilhetes_Qsairam);
                        }
                        encontrada = true;
                        break;
                    }
                    p = p->proxima;
                }

                if (!encontrada) {
                    cout << "Paragem '" << nome_paragem << "' nao foi encontrada na rota.\n";
                }
                break;
            }

            case 3: {
                string matricula, novoPnome, novoUnome;
                cout << "Escreva a matricula do autocarro: ";
                cin >> matricula;
                cout << "Novo primeiro nome do motorista: ";
                cin >> novoPnome;
                cout << "Novo ultimo nome do motorista: ";
                cin >> novoUnome;

                alterar_motorista(terminal.autocarros_ativos, matricula, novoPnome, novoUnome);
                break;
            }

            case 4: {
                string nome_paragem;
                int bilhete;

                cin.ignore();
                cout << "Nome da paragem onde quer remover o bilhete: ";
                getline(cin, nome_paragem);

                cout << "Numero do bilhete que quer remover: ";
                cin >> bilhete;

                remover_bilhete_em_paragem(terminal.rota, nome_paragem, bilhete);
                break;
            }

            case 5: {
                string nome;
                cin.ignore();
                cout << "Nome da paragem que quer remover: ";
                getline(cin, nome);

                remover_paragem_por_nome(terminal.rota, nome);
                break;
            }

            case 6: {
                cout<<"Indisponivel";
                break;
            }

            case 0:
                imprime_estado(terminal);
                break;

            default:
                cout << "Opcao invalida!\n";
        }
    } while (opcao != 0);
}


