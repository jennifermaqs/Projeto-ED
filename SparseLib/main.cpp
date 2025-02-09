/*
* Jennifer Marques de Brito - 569710
* João Guilherme Lira dos Santos - 566419
*/

#include <iostream>
#include "SparseMatrix.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;


//funcao para exibir um menu de ajuda com os comandos disponiveis no programa
void help(){
    
    cout<<"|================================================================|"<<endl;
    cout<<"|---------------------------- HELP ------------------------------|"<<endl;
    cout<<"|================================================================|"<<endl;
    cout<<"|___________________________COMANDOS:____________________________|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|1.Exit........................................encerra o programa|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|2.Create m n.......cria uma nova matriz com m linhas e n colunas|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|3.Show <i>....................print the matrix i in the terminal|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|4.Showidx...................show all the indexes of rhe matrices|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|5.Sum i j...............................sum the matrices i and j|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|6.Clear i.....................................clear the matrix i|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|7.Read 'mtx.txt'.........read the matrix from the file 'mtx.txt'|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|8.Update m i j......valueupdate the value of the cell(i,j) int m|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|9.Erase all.....erase all the matrices currently int the program|"<<endl;
    cout<<"|________________________________________________________________|"<<endl;
    
}

//funcao que le uma matriz esparsa a partir de um arquivo
void readSparseMatrix(SparseMatrix& m, const string& nomeDoArquivo) {
    ifstream arquivo(nomeDoArquivo);
    // verifica se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo " + nomeDoArquivo);
    }

    int numLinhas, numColunas;
    arquivo >> numLinhas >> numColunas; // le as dimensoes da matriz

    //validacao das dimensoes da matriz
    if(numLinhas <= 0 || numColunas <= 0) {
        throw invalid_argument("Dimensoes da matriz invalidas.");
    }
    m.clear(); // limpa qualquer dado anterior

    //inicializa a matriz com as dimensoes lidas
    m = SparseMatrix(numLinhas, numColunas);
    int i, j;
    double valor;

    //le os valores nao nulos da matriz
    while (arquivo >> i >> j >> valor) {
        m.insert(i, j, valor); // insere valor na celula especifica
    }
    arquivo.close();
}

//funcao que soma duas matrizes esparsas e retorna o resultado
SparseMatrix* sum(const SparseMatrix* A, const SparseMatrix* B) {
    
	if(A->getLinhas() != B->getLinhas()  || A->getColunas()  != B->getColunas()) {
		throw std::invalid_argument("Matrizes com dimencoes incompativeis para soma");
	}
    
    int n = A->getLinhas(); // numero de linhas da matriz resultante
    int m = B->getColunas();// numero de linhas da matriz resultante
    
    SparseMatrix* C = new SparseMatrix(n, m);
	
    //percorre todas as celulas e realiza a soma elemento por elemento
	for(int i=1; i<=A->getLinhas(); i++){
	    for(int j=1; j<=A->getColunas(); j++){
            //soma e insere no resultado
	        C->insert(i, j, (A->get(i, j) + B->get(i, j)));
	    }
	}

	return C;
}

//funcao que multiplica duas matrizes esparsas e retorna o resultado
SparseMatrix* multiply(const SparseMatrix* A, const SparseMatrix* B) {
    if(A->getColunas() != B->getLinhas()) {
        throw std::invalid_argument("Dimensoes das matrizes incompativeis para multiplicacao");
    }

    int linhasC = A->getLinhas();//numero de linhas da matriz resultante
    int colunasC = B->getColunas();//numero de linhas da matriz resultante
    SparseMatrix* C = new SparseMatrix(linhasC, colunasC);

    //realiza a multiplicacao tradicional de matrizes
    for(int i = 1; i <= linhasC; i++) {
        for(int j = 1; j <= colunasC; j++) {
            double soma = 0.0; // acumula o valor 
            for(int k = 1; k <= A->getColunas(); k++) {
                soma += A->get(i,k) * B->get(k,j); // soma dos produtos correspodentes
            }
            if(soma != 0.0) {
                C->insert(i, j, soma);
            }
        }
    }

    return C;
}


 int main() {
    //cabecalho inicial do programa
    
    cout<<"|================================================================|"<<endl;
    cout<<"|---------------------------- Bem-vindo(a)! ---------------------|"<<endl;
    cout<<"|================================================================|"<<endl;
    cout<<"|Digite:                          |Para:                         |"<<endl;
    cout<<"|_________________________________|______________________________|"<<endl;
    cout<<"|-Help                            |Abrir painel de comandos      |"<<endl;
    cout<<"|-Exit                            |Fechar programa               |"<<endl;
    cout<<"|_________________________________|______________________________|"<<endl;
    
    string comando;
    while(true){
        //acao do usuario        
        cout<<"Digite a acao:"<<endl;
        getline(cin, comando);
        cout<<endl;

        istringstream cc(comando);
        
        //verifica os comandos e chama a funcao correspondente
        if(comando == "help" || comando == "Help"){
            help();
        }
        else if(comando == "exit" || comando == "Exit"){
            cout<<"...FECHANDO PROGRAMA..."<<endl;
            break;
        }
        else if(comando == ""){
            //nao faz nada caso a entrada seja vazia
        }
        else{
            cout<<"*COMANDO INVALIDO!"<<endl;
        }
    }
    

	return 0;
}

