#include <iostream>

#include "SparseMatrix.h"
using namespace std;

SparseMatrix sum(const SparseMatrix& A, const SparseMatrix& B) {
    if(A.linhas != B.linhas || A.colunas != B.colunas) {
        throw std::invalid_argument("Matrizes com dimensões incompatíveis para soma");
    }
    
    SparseMatrix C(A.linhas, A.colunas); // matriz resultado

    //itera por todas as linhas das matrizes
    for (int i = 1; i <= A.linhas; i++) {
        //encontrar linha i em A
        Node* linhaA = A.sentinela->abaixo;
        while (linhaA->linha != i) {
            linhaA = linhaA->abaixo;
            if(linhaA == A.sentinela) break;
        }
        //linha i em B
        Node* linhaB = B.sentinela->abaixo;
        while (linhaB->linha != i) {
            linhaB = linhaB->abaixo;
            if(linhaB == B.sentinela) break;
        }

        //ponteiros p percorrer as linhas
        Node* noA = linhaA->direita;
        Node* noB = linhaB->direita;

        while(noA != linhaA && noB != linhaB) {
            if (noA->coluna < noB->coluna) {
                C.insert(noA->linha, noA->coluna, noA->value);
                noA = noA->direita;
            } else if (noB->coluna < noA->coluna) {
                C.insert(noB->linha, noB->coluna, noB->value);
                noB = noB->direita;
            } else {
                double soma = noA->value + noB->value;
                if(soma != 0) {
                    C.insert(noA->linha, noA->coluna, soma);
                }
                noA = noA->direita;
                noB = noB->direita;
            }
        }
        // Elementos restantes de A
        while (noA != linhaA) {
         C.insert(noA->linha, noA->coluna, noA->value);
         noA = noA->direita;
    }
        // Elementos restantes de B
        while (noB != linhaB) {
         C.insert(noB->linha, noB->coluna, noB->value);
         noB = noB->direita;
    }
}

   return C;
}

int main() {
   
SparseMatrix m(2, 2);
SparseMatrix mm(2, 2);

m.insert(1, 1, 10);
mm.insert(1, 1, 20);

sum(m, mm);
    
}