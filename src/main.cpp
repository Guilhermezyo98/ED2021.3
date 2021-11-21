// ED2.cpp: define o ponto de entrada para o aplicativo.
//

#include "cabecalhos_basicos.h"
#include "Leitura.h"
#include "Timer.h"
#include "Parametros_constantes.h"

using namespace std;

enum EscolhasChamada
{
    teste_Importacao = 1, 
    imprime_Review_Especifica = 2

};

void menu (string caminhoEntrada,string caminhoBinario,string caminhoTexto)
{
    while (true)
    {
        cout << "**************";
        cout << "\tMENU\t";
        cout << "**************";

        cout << "\nEscolhe entre usar as funcoes:\n";
        cout << "\tDigite 1 para: testeImportacao() \n\tDigite 2 para: imprimeReviewEspecifica()\n\tDigite 0 para sair "<<endl;
        int entrada = -1;
        cin >> entrada;

        switch (entrada)
        {
        case teste_Importacao:
            {
                testeImportacao(caminhoTexto);
                break;
            }
        case imprime_Review_Especifica:
            {
            cout << "\nDigite o numero da review a ser impressa: ";
                int nReview = -1;
                cin >> nReview;
                imprimeReviewEspecifica(nReview);
            }
        case 0:
        {
            return;
            break;
        }
        }
    }

    

}


int main(int argc, char* argv[])
{   
    //arquivo_path =argv[1];
    //saidaBinaria_path =argv[2];
    //saidaTexto_path = argv[3];
    vector <Review> reviews;
    reviews.reserve(tam_linhas);

    {
        Timer timer("Tempo para lerArquivoCSV(): ");
    	lerArquivoCSV(argv[1], reviews);
    }

    {
        Timer timer("Tempo para escreveBin(): ");
    	escreveBin(argv[2],reviews);
    }

   
    menu(argv[1],argv[2],argv[3]);
    
    
    
    return 0;
}
