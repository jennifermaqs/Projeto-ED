#include <iostream>
#include "SparseMatrix.h"
using namespace std;

int main() {
    
    //MAIN DE TESTE APENAS 
    
    int n=3;
    int v;
    
    cout<<"criei a matriz 3x3";
    
    SparseMatrix m (3, 3);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cout<<"valor (" << i <<", "<< j <<"): ";
            cin>>v;
            m.insert(i, j, v);
        }
    }
    
    cout<<endl;
    cout<<"Print da matriz:"<<endl;
    m.print();
    
    cout<<endl;
    
    cout<<"GET(1, 2): " << m.get(1, 2) << endl;

    return 0;
}