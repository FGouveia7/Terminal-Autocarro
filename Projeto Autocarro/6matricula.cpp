//
// Created by franc on 16/04/2025.
//
#include "2estruturas.h"
using namespace std;
#include "6matricula.h"

//------------------------------------------
/**
 * Cria uma nova matrícula aleatória composta por 4 caracteres hexadecimais.
 * Garante que a matrícula não existe já na lista global de matrículas.
 * Armazena a nova matrícula no array global, caso haja espaço disponível.
 *
 * @return string Matrícula criada e única.
 */

const int MAX_MATRICULAS = 200;
string matrículas[MAX_MATRICULAS];
int numMatrículas = 0;
string cria_matricula() {
    string matricula = "";
    const char hex[] = "0123456789ABCDEF";
    do {
        matricula = "";
        for (int i = 0; i < 4; i++) {
            int valor = rand() % 16;
            matricula += hex[valor];
        }
    } while (matricula_existe(matricula));
    if (numMatrículas < MAX_MATRICULAS) {
        matrículas[numMatrículas++] = matricula;
    }
    return matricula;
}
//------------------------------------------
/**
 * Verifica se uma matrícula já existe num conjunto de matrículas registadas.
 * Esta função pesquisa num array global de matrículas para determinar se a
 * matrícula fornecida já está registada.
 *
 * @param matricula Matrícula a verificar.
 * @return true se a matrícula existir no array, false caso contrário.
 */
bool matricula_existe(string matricula) {
    for (int i = 0; i < numMatrículas; i++) {
        if (matrículas[i] == matricula) {
            return true;
        }
    }
    return false;
}
