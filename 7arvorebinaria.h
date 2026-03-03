//
// Created by franc on 16/04/2025.
//

#ifndef INC_7SISTEMABST_H
#define INC_7SISTEMABST_H
void inserir_na_arvore(noBST*& raiz, int bilhete);
noBST* remover_bilhete_arvoreBST(noBST* raiz, int bilhete);
void remover_bilhete_em_paragem(paragem* rota, const string& nome_paragem, int bilhete);
noBST* remover_noBST_com_pai(noBST* raiz, noBST* no, noBST* pai);
#endif //INC_7SISTEMABST_H
