/*
* Jennifer Marques de Brito - 569710
* João Guilherme Lira dos Santos - 566419
*/

// estrutura Node que representa um elemento em uma matriz esparsa.
// armazena um valor e referências para os próximos nós na mesma linha e coluna.
#ifndef NODE_H
#define NODE_H

struct Node {
    double value; // variavel que guarda o valor
    Node *direita; 
    Node *abaixo;
    int linha;
    int coluna;

    // construtor do node
    Node(int linha, int coluna, double value, Node* direita, Node* abaixo) {
        this->linha = linha;
        this->coluna = coluna;
        this->value = value;
        this->direita = direita;
        this->abaixo = abaixo;
    }
};

#endif 
