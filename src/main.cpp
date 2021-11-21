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

void menu ()
{
    cout << "**************";
    cout << "\tMENU\t";
    cout << "**************";

    cout << "\nEscolhe entre usar as funcoes:\n";
    cout << "\tDigite 1 para: testeImportacao() \n\t Digite 2 para: imprimeReviewEspecifica()\n";
    int entrada = -1;
    cin >> entrada;

    switch (entrada)
    {
    case teste_Importacao:
	    {
			testeImportacao();
			break;
	    }
    case imprime_Review_Especifica:
	    {
        cout << "\nDigite o numero da review a ser impressa: ";
			int nReview = -1;
            cin >> nReview;
            imprimeReviewEspecifica(nReview);
	    }
    }

}


int main(int argc, char* argv[])
{

    vector <Review> reviews;
    reviews.reserve(tam_linhas);

    {
        Timer timer("Tempo para lerArquivoCSV(): ");
    	lerArquivoCSV(arquivo_path, reviews);
    }

    {
        Timer timer("Tempo para escreveBin(): ");
    	escreveBin(reviews);
    }

    while (true)
    {
        menu();
    }
    
    
    return 0;
}
