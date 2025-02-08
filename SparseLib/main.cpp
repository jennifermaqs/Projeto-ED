#include <iostream>
#include "SparseMatrix.h"
#include <string>
#include <sstream>
#include <fstream>
using namespace std;


void help(){
    
    cout<<"|================================================================|"<<endl;
    cout<<"|---------------------------- HELP ------------------------------|"<<endl;
    cout<<"|================================================================|"<<endl;
    cout<<"|___________________________COMANDOS:____________________________|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|1.Exit........................................encerra o programa|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|2.Create...........cria uma nova matriz com m linhas e n colunas|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|3.Show..................imprime a matriz de indice i no terminal|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|4.Showidx...........mostra os indices (e dimensoes) das matrizes|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|5.Sum.........................soma as matrizes de indices i e j |"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|6.Multiply..............multiplica as matrizes de indices i e j |"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|7.Clear..............................limpa a matriz de indice i |"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|8.Read..........................le a matriz do arquivo 'mtx.txt'|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|9.Update..................atualiza o valor da celula na matriz i|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|10.Erase..........apaga todas as matrizes atualmente no programa|"<<endl;
    cout<<"|________________________________________________________________|"<<endl;
    
}

void readSparseMatrix(SparseMatrix& m, const string& nomeDoArquivo) {
    ifstream arquivo(nomeDoArquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo " + nomeDoArquivo);
    }

    int numLinhas, numColunas;
    arquivo >> numLinhas >> numColunas;

    if(numLinhas <= 0 || numColunas <= 0) {
        throw invalid_argument("Dimensoes da matriz invalidas.");
    }
    m.clear();

    m = SparseMatrix(numLinhas, numColunas);
    int i, j;
    double valor;
    while (arquivo >> i >> j >> valor) {
        m.insert(i, j, valor);
    }
    arquivo.close();
}

SparseMatrix* sum(const SparseMatrix* A, const SparseMatrix* B) {
    
	if(A->getLinhas() != B->getLinhas()  || A->getColunas()  != B->getColunas()) {
		throw std::invalid_argument("Matrizes com dimencoes incompativeis para soma");
	}
    
    int n = A->getLinhas();
    int m = B->getColunas();
    
    SparseMatrix* C = new SparseMatrix(n, m);
	//SparseMatrix C(A.getLinhas(), A.getColunas()); // matriz resultado
	
	for(int i=1; i<=A->getLinhas(); i++){
	    for(int j=1; j<=A->getColunas(); j++){
	        C->insert(i, j, (A->get(i, j) + B->get(i, j)));
	    }
	}

	return C;
}

SparseMatrix* multiply(const SparseMatrix* A, const SparseMatrix* B) {
    if(A->getColunas() != B->getLinhas()) {
        throw std::invalid_argument("Dimensoes das matrizes incompativeis para multiplicacao");
    }

    int linhasC = A->getLinhas();
    int colunasC = B->getColunas();
    SparseMatrix* C = new SparseMatrix(linhasC, colunasC);

    for(int i = 1; i <= linhasC; i++) {
        for(int j = 1; j <= colunasC; j++) {
            double soma = 0.0;
            for(int k = 1; k <= A->getColunas(); k++) {
                soma += A->get(i,k) * B->get(k,j);
            }
            if(soma != 0.0) {
                C->insert(i, j, soma);
            }
        }
    }

    return C;
}


 int main() {
    
    cout<<"|================================================================|"<<endl;
    cout<<"|---------------------------- Bem-vindo(a)! ---------------------|"<<endl;
    cout<<"|================================================================|"<<endl;
    cout<<"|Digite:                          |Para:                         |"<<endl;
    cout<<"|_________________________________|______________________________|"<<endl;
    cout<<"|-Help                            |Abrir painel de comandos      |"<<endl;
    cout<<"|-Exit                            |Fechar programa               |"<<endl;
    cout<<"|_________________________________|______________________________|"<<endl;
    
    cout<<endl;
    string comando;
    while(true){
        //lembrar de limpar o buffer antes de chamar qualquer entrada
        
        cout<<"Digite a acao:"<<endl;
        getline(cin, comando);
        //cin.ignore();
        cout<<endl;
        
        if(comando == "help" || comando == "Help"){
            help();
        }
        if(comando.empty()){
            continue;
        }
        else if(comando == "exit" || comando == "Exit"){
            cout<<"...FECHANDO PROGRAMA..."<<endl;
            break;
        }
        else if(comando == ""){
            
        }
        else{
            cout<<"*COMANDO INVALIDO!"<<endl;
        }
    }
    

	return 0;
}

