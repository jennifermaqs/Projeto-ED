#include "SparseMatrix.h"
#include<iostream>

/**
 * @brief implementacao das funcoes da matriz esparsa com sentinelas circulares
 *
*/
SparseMatrix::SparseMatrix(int n, int m) : linhas(n), colunas(m) {
		// verificacao
		if(n<=0 || m<=0) {
			throw std::invalid_argument("numero de linha ou coluna invalidos");
		}
        //inicia o sentinela principal e deixa circular
		sentinela = new Node(0, 0, 0, nullptr, nullptr);
		sentinela->direita = sentinela;
		sentinela->abaixo = sentinela;
		//AQUI JA TA CIRCULAR
		//atualiza o numero de linhas e de colunas
		linhas = n;
		colunas = m;

		//sentinelas das linhas
		this->linSentinela = new Node(1, 0, 0, nullptr, nullptr);
		linSentinela->direita = linSentinela; //deixa circular horizontalmente
		sentinela->abaixo = linSentinela;
		for(int i=2; i<=n; i++) {
			linSentinela->abaixo = new Node(i, 0, 0, nullptr, nullptr);
			linSentinela = linSentinela->abaixo;
			linSentinela->direita = linSentinela;
		}
		linSentinela->abaixo = sentinela; //deixei circular

        std::cout<<std::endl;

		//sentinelas das colunas
		this->colSentinela = new Node(0, 1, 0, nullptr, nullptr);
		colSentinela->abaixo = colSentinela;
		sentinela->direita = colSentinela;
		for(int i=2; i<=m; i++) {
			colSentinela->direita = new Node(0, i, 0, nullptr, nullptr);
			colSentinela = colSentinela->direita;
			colSentinela->abaixo = colSentinela;
		}
		colSentinela->direita = sentinela;
	}

void SparseMatrix::clear() {
    //desalocando as memorias das linhas
		Node* linAtual = sentinela->abaixo; // primeira linha
		while (linAtual != sentinela) {
			Node* noAtual = linAtual->direita;
			while(noAtual != linAtual) {
				Node* temp = noAtual;
				noAtual = noAtual -> direita;
				delete temp; // deletando no
			}
			Node* nextLin = linAtual->abaixo;
			delete linAtual; // deletando sentinela da linha
			linAtual = nextLin; // vai pra proxima linha
		}
		//desalocando as memorias das colunas
		Node* colAtual = sentinela->direita; //primeira coluna
		while(colAtual != sentinela) {
			Node* nextCol = colAtual->direita;
			delete colAtual; // deletando sentinela da coluna
			colAtual = nextCol; // proxima coluna
	}
}

SparseMatrix::~SparseMatrix() {
		clear();
		delete sentinela; // liberando no sentinela principal
	}

void SparseMatrix::insert(int i, int j, double valor) {

		if(valor==0) {
			return;
		}

		if(i<=0 || j<=0 || i > linhas || j > colunas) {
			throw std::invalid_argument("numero de linha ou coluna invalidos"); //não pode acentuar :(
		}

		//vou achar o sentinela da linha que a gente esta procurando
		Node* auxlinha = sentinela->abaixo;

		while(auxlinha->linha != i) {
			auxlinha = auxlinha->abaixo;
		}


		Node *lAnterior = auxlinha; //esse aqui vai achar o anterior
		Node *lCerto = lAnterior->direita;//("lCerto de linhaCerta") //esse vai navegar sempre um a frente do auxlinha

		//impede que fique em loop ao comparar com o sentinela(auxlinha) e acha o anterior do procurado
		while(lCerto != auxlinha && lCerto->coluna < j) {
			lAnterior = lCerto;
			lCerto = lCerto->direita;
		}

		//vamo verificar se essa posicao ja existe
		if(auxlinha != lCerto && lCerto->coluna == j) {
			lCerto->value = valor;
			return;
		} else {
			//caso posicao nao exista

			Node* noAtual = new Node(i, j, valor, nullptr, nullptr);

			//inserindo na linha que a gente achou ali e em seguida vamos achar a coluna, igual
			//fizemos com a linha

			noAtual->direita = lCerto;
			lAnterior->direita = noAtual;

			Node* auxColuna = sentinela->direita;
			while(auxColuna->coluna != j) {
				auxColuna = auxColuna->direita;
			}

			Node* cAnterior = auxColuna;
			Node* cCerto = cAnterior->abaixo; // "c de coluna e "certo" de certo

			while(cCerto != auxColuna && cCerto->linha < i) {
				cAnterior = cCerto;
				cCerto = cCerto->abaixo;
			}


			//agora vamo ajustar os ponteiros
			noAtual->abaixo = cCerto;
			cAnterior->abaixo = noAtual;
		}

	}

double SparseMatrix::get(int i, int j) const {
		if(i<=0 || j<=0 || i > linhas || j > colunas) {
			throw std::invalid_argument("numero de linha ou coluna invalidos");
		}

		Node* aux = sentinela;

		while(aux->linha != i) { 
			aux = aux->abaixo;
		}
		
		while(aux->coluna != j){
		    aux = aux->direita;
		    if(aux->linha == 0){
		        return 0; //nao sei se essa logica ta certa, mas se a linha for 0 signica que deu a volta
		    }            //e que voltou pro sentinela, logo, o valor nao tava armazenado pois era 0 e n foi armazenado
		}
		
		return aux->value;

	}

void SparseMatrix::print() const {
	    
	    if(linhas == 0 || colunas == 0){
	        throw std::invalid_argument("numero de linha ou coluna invalidos");
	    }
	    
	    Node* aux = sentinela->abaixo;
	    
	    for(int i=1; i<=linhas; i++){
	        Node* auxColuna = aux->direita;
	        for(int j=1; j<=colunas; j++){
	            
	            if(auxColuna == sentinela) break;
	            
	            if(auxColuna->coluna == j){
	                std::cout<<" " << auxColuna->value <<" ";
	                auxColuna = auxColuna->direita;
	            } else{
	                std::cout<<" 0 ";
	            }
	        }
	        std::cout<<std::endl;
	        aux = aux->abaixo;
	    }
	}

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