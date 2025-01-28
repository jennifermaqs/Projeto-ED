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
