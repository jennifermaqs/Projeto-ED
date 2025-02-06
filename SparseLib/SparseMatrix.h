#ifndef SPARSEMATRIX_H
#define SPARCEMATRIX_H
#include "Node.h"
#include <stdexcept>
#include <iostream>


class SparseMatrix {
private:
	Node* sentinela; // sentinela central
	Node* linSentinela;
	Node* colSentinela;
	int colunas;
	int linhas;

	//funcao aux para limpar memória
	void clear();

public:
	// construtor
	SparseMatrix(int n, int m);

	//destrutor
	~SparseMatrix();

	void insert(int i, int j, double valor);

	double get(int i, int j) const;
	
	void print() const;

	friend SparseMatrix sum(const SparseMatrix& A, const SparseMatrix& B);
	friend SparseMatrix multiply(const SparseMatrix& A, const SparseMatrix& B);




};

SparseMatrix sum(const SparseMatrix& A, const SparseMatrix& B);
SparseMatrix multiply(const SparseMatrix& A, const SparseMatrix& B);

#endif