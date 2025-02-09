/*
* Jennifer Marques de Brito - 569710
* João Guilherme Lira dos Santos - 566419
*/
#include <iostream>
#include "SparseMatrix.h"
#include <string>
#include <sstream>
#include <fstream>
#include<vector>
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
    m.clear();  // limpa qualquer dado anterior

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
    int m = B->getColunas(); // numero de colunas da matriz resultante
    
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

    int linhasC = A->getLinhas(); //numero de linhas da matriz resultante
    int colunasC = B->getColunas();//numero de colunas da matriz resultante
    SparseMatrix* C = new SparseMatrix(linhasC, colunasC);

    //realiza a multiplicacao tradicional de matrizes
    for(int i = 1; i <= linhasC; i++) {
        for(int j = 1; j <= colunasC; j++) {
            double soma = 0.0; // acumula o valor
            for(int k = 1; k <= A->getColunas(); k++) {
                soma += A->get(i,k) * B->get(k,j);  // soma dos produtos correspodentes
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
    
    cout<<endl;

    vector<SparseMatrix*> vetorDeMatrizes;
    string entrada;

    while(true){
        //acao do usuario       
        cout<< endl << "\nDigite a acao: ";
        getline(cin, entrada);
        istringstream cc(entrada);
        string comando;
        cc>>comando;
        //verifica os comandos e chama a funcao correspondente


        if(comando == "exit" || comando == "Exit"){
            cout<<"...FECHANDO PROGRAMA..."<<endl;
            break;
        } else if(comando == "help" || comando == "Help"){
            help();
        }  if (comando == "create" || comando == "Create") {
            int i, j;
            if (cc >> i >> j) {
                vetorDeMatrizes.push_back(new SparseMatrix(i, j));
                cout << "Matriz criada com " << i << " linhas e " << j << " colunas." << endl;
            } else {
                cout << "COMANDO ESCRITO INCORRETAMENTE" << endl;
            }
        } else if(comando == "show" || comando == "Show"){
            int idc;
            if(cc >> idc){
                if(idc >= 0 && idc < vetorDeMatrizes.size()){
                    cout << "Mostrando matriz de indice " << idc << ":" << endl;
                    vetorDeMatrizes[idc]->print();
                } else {
                    cout << "Indice de matriz invalido." << endl;
                }
            } else {
                cout << "COMANDO INVALIDO!" << endl;
            }
        } else if (comando == "showidx" || comando == "Showidx") {
            if (vetorDeMatrizes.empty()) {
                cout << "Nenhuma matriz indexada." << endl;
            } else {
                cout << "Indices das matrizes: " << endl;
                for (int i = 0; i < vetorDeMatrizes.size(); i++) {
                    cout << " [" << i << "] ";
                }
                cout << endl;
            }
        }  else if(comando == "sum" || comando == "Sum"){
            int i;
            int j;
            if(cc >> i >> j){
                if(i>=0 && i < vetorDeMatrizes.size() && j < vetorDeMatrizes.size() && j>=0){
                    SparseMatrix* c = sum(vetorDeMatrizes[i], vetorDeMatrizes[j]);
                        cout<<"Matrizes somadas com sucesso!"<<endl;
                        cout<<"Voce gostaria de armazenar essa soma de matriz?[s/n] ";
                        string resposta;
                        getline(cin, resposta);
                        if(resposta == "s" || resposta == "S"){
                            vetorDeMatrizes.push_back(c);
                            cout<<"Matriz armazenada com sucesso!"<<endl;
                        } else{
                            c->clear();
                            delete c;
                            cout<<"Matriz descartada"<<endl;
                        }
                } else {
                    cout<<"Valores nao correspondem a matrizes armazenadas"<<endl;
                }
            } else{
                cout<<"Matrizes indicadas invalidas";
            }
        } else if(comando == "Multiply" || comando == "multiply"){
            int i;
            int j;
            if(cc >> i >> j){
                if(i>=0 && i < vetorDeMatrizes.size() && j < vetorDeMatrizes.size() && j>=0){
                    SparseMatrix* c = multiply(vetorDeMatrizes[i], vetorDeMatrizes[j]);
                        cout<<"Matrizes multiplicadas com sucesso!"<<endl;
                        cout<<"Voce gostaria de armazenar esse produto de matrizes?[s/n] ";
                        string resposta;
                        getline(cin, resposta);
                        if(resposta == "s" || resposta == "S"){
                            vetorDeMatrizes.push_back(c);
                            //delete c;
                            cout<<"Matriz armazenada com sucesso!"<<endl;
                        } else{
                            delete c;
                            cout<<"Matriz descartada"<<endl;
                        }
                } else {
                    cout<<"Valores nao correspondem a matrizes armazenadas"<<endl;
                }
            } else{
                cout<<"Matrizes indicadas invalidas";
            }
        } else if(comando == "clear" || comando == "Clear"){
            int idc;
            if(cc >> idc){
                if(idc >= 0 && idc < vetorDeMatrizes.size()){
                    vetorDeMatrizes[idc]->clear();
                    cout << "Matriz " << idc << " limpa." << endl;
                } else {
                    cout << "Indice de matriz invalido." << endl;
                }
                }
            }   else if (comando == "read" || comando == "Read") {
                string arquivo;
                if (cc >> arquivo) {
                    SparseMatrix* novaMatriz = new SparseMatrix();
                    try {
                    readSparseMatrix(*novaMatriz, arquivo);   // supondo que a função retorna sucesso ou falha
                        vetorDeMatrizes.push_back(novaMatriz);
                        cout << "Matriz lida do arquivo " << arquivo 
                             << " e armazenada no indice " << vetorDeMatrizes.size() - 1 << endl;
                    } catch (const exception& e) {
                        cout << "Erro ao ler a matriz do arquivo: " << e.what() << endl;
                        delete novaMatriz;  // liberar memória manualmente
                    }
                } else {
                    cout << "COMANDO INVALIDO!" << endl;
                }
            } else if(comando == "Update" || comando == "update"){
                int idc, linha, coluna;
                double valor;
                if(cc >> idc >> linha >> coluna >> valor){
                    if(idc >= 0 && idc < vetorDeMatrizes.size()){
                    vetorDeMatrizes[idc]->insert(linha, coluna, valor);
                    cout << "Matriz " << idc << " atualizada: pos(" 
                         << linha << "," << coluna << ") = " << valor << endl;
                } else {
                    cout << "Indice de matriz invalido." << endl;
                }
            }
         } else if(comando == "erase" || comando == "Erase"){
            for(int i = (vetorDeMatrizes.size()-1); i>=0; --i){
                delete vetorDeMatrizes[i];
                vetorDeMatrizes.pop_back();
            }
            cout << "Todas as matrizes foram apagadas." << endl;
        } else {
            cout<<"COMANDO INVALIDO!" << endl;
        }
    }
    

	return 0;
}
 




