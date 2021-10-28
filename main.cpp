#include "includes.h"
#include "leitura.h"
#include "structs.h"
#define TAM 3660725
//#include <iostream>
//#define TAM 3660724
//using namespace std;



int main()
{
    int i;
    string caminho;
    cout << "Iniciando" << endl;
    review *dados = new review[TAM];
    cout << "Alocacao finalizada" << endl;
    cout<<"caminho:"<<endl;
    cin>>caminho;
    leArquivo(caminho,dados);
    cout << "LEITURA FINALIZADA" << endl;
    while(i!=-1){
        cout<<"qual registro imprimir? (-1 para sair)";
        cin>>i;
        imprimeReview(&dados[i]);
    }
    return 0;
}
