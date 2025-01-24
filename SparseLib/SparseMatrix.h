#ifndef SPARSEMATRIX_H
#define SPARCEMATRIX_H
#include "Node.h"
#include <stdexcept>

/**
 * @brief Classe implementa uma matriz esparsa com sentinelas circulares
 * 
*/
class SparseMatrix {
  private:
    Node* sentinela; // sentinela central
    Node* linSentinela;
    Node* colSentinela;
    int colunas;
    int linhas;
    
  public:
  // construtor
  SparseMatrix(int n, int m) {
    
    // verificação
    if(n<=0 || m<=0) {
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
    
    //atualiza o número de linhas e de colunas
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
  }

  //destrutor
  ~SparseMatrix() {    
    //desalocando as memórias das linhas
    Node* linAtual = sentinela->abaixo; // primeira linha
    while (linAtual != sentinela) {
      Node* nextLin = linAtual->abaixo;

      Node* nodolinAtual = linAtual->direita;
      while(nodolinAtual != linAtual) {
        Node* proximoNo = nodolinAtual->direita;
        delete nodolinAtual; // deletando nó

        nodolinAtual = proximoNo; // vai pro próximo nó
      }
      delete linAtual; // deletando sentinela da linha
      linAtual = nextLin; // vai pra próxima linha
    }
    //desalocando as memórias das colunas
    Node* colAtual = sentinela->direita; //primeira coluna
    while(colAtual != sentinela) {
      Node* nextCol = colAtual->direita;
      delete colAtual; // deletando sentinela da coluna
      colAtual = nextCol; // proxima coluna
    }

    delete sentinela; // liberando nó sentinela principal
  }


};

  //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
  //KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK calma jao
  //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
#endif