#ifndef SPARSEMATRIX_H
#define SPARCEMATRIX_H
#include "Node.h"
#include <stdexcept>

//@brief classe implementa uma matriz esparsa com sentinelas circulares

class SparseMatrix {
  private:
    Node* sentinela; // sentinela central
    Node* linSentinela;
    Node* colSentinela;
    int colunas;
    int linhas;
    
  public:
  // construtor
  SparseMatrix(int n, int m){
    
    // verificação
    if(n<=0 || m<=0){
      throw std::invalid_argument("número de linha ou coluna inválidos");
    }
    
    //inicia o sentinela principal e deixa circular
    sentinela = new Node(0, 0, 0, nullptr, nullptr);
    sentinela->direita = sentinela;
    sentinela->abaixo = sentinela;
    //AQUI JA TA CIRCULAR

    //inicializa apontando para o sentinela antes de entrar no laço
    linSentinela = sentinela;
    colSentinela = sentinela;
    
    //atualiza o nummero de linhas e de colunas
    linhas = n;
    colunas = m;
    
    //sentinelas das linhas
    sentinela->abaixo = linSentinela;
    for(int i=0; i<n; i++) {
        linSentinela->abaixo = new Node(0, i+1, 0, nullptr, nullptr);
        linSentinela = linSentinela->abaixo;
    }
    linSentinela->abaixo = sentinela; //deixei circular
    
    
    //sentinelas das colunas
    sentinela->direita = colSentinela;
    for(int i=0; i<m; i++) {
        colSentinela->direita = new Node(i+1, 0, 0, nullptr, nullptr);
        colSentinela = colSentinela->direita;
    }
    colSentinela->direita = sentinela;
  
  
  //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
  //KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK calma jao
  }
};

#endif