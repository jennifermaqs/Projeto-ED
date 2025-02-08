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
    cout<<"|1.Exit.........................................close the program|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|2.Create m n........create new matrix whith m rows and n columns|"<<endl;
    cout<<"|                                                                |"<<endl;
    cout<<"|3.Show i......................print the matrix i in the terminal|"<<endl;
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



int main() {
    
    cout<<"|================================================================|"<<endl;
    cout<<"|---------------------------- Bem vindo! ------------------------|"<<endl;
    cout<<"|================================================================|"<<endl;
    cout<<"|Digite:                          |Para:                         |"<<endl;
    cout<<"|_________________________________|______________________________|"<<endl;
    cout<<"|-Help                            |Abrir painel de comandos      |"<<endl;
    cout<<"|-Exit                            |Fechar programa               |"<<endl;
    cout<<"|_________________________________|______________________________|"<<endl;
    
    cout<<endl;
    
    string comando;
    cout<<"Digite a acao:"<<endl;
    getline(cin, comando);
    //cin.ignore();
    cout<<endl;
    
    cout<<endl;
    
    while(true){
        //lembrar de limpar o buffer antes de chamar qualquer entrada
        
        cout<<"Digite a acao:"<<endl;
        getline(cin, comando);
        //cin.ignore();
        cout<<endl;
        
        if(comando == "help" || comando == "Help"){
            help();
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


