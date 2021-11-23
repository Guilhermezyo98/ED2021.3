// ED2.cpp: define o ponto de entrada para o aplicativo.
//

#include "cabecalhos_basicos.h"
#include "Leitura.h"
#include "Timer.h"
#include "Parametros_constantes.h"

using namespace std;

enum EscolhasChamada
{
    lerCSV = 1,
    escreverBinario = 2,
    teste_Importacao = 3,
    imprime_Review_Especifica = 4,
    sair = 5
};

void menu (string caminhoEntrada,string caminhoBinario,string caminhoTexto, vector<Review>& reviews)
{
    while (true)
    {
        cout << "**************\tMENU\t**************";
        cout << "\nEscolhe entre usar as funcoes:\n";
        cout << "\tDigite 1 para: lerCSV() \n";
        cout << "\tDigite 2 para: escreverBinario()\n";
        cout << "\tDigite 3 para: testeImportacao() \n";
        cout << "\tDigite 4 para: imprimeReviewEspecifica()\n";
    	cout << "\tDigite 5 para sair " << endl;

        int entrada = -1;
        cin >> entrada;

        switch (entrada)
        {
        case lerCSV:
        {
            {
                Timer timer("Tempo para lerArquivoCSV()");
                lerArquivoCSV(caminhoEntrada, reviews);
                break;
            }
        }
        case escreverBinario:
        {
            {
                Timer timer("Tempo para escreveBin():");
                escreveBin(caminhoBinario, reviews);
                break;
            }
        }
        case teste_Importacao:
            {
                testeImportacao(caminhoEntrada,caminhoBinario,caminhoTexto);
                break;
            }
        case imprime_Review_Especifica:
            {
            cout << "\nDigite o numero da review a ser impressa: ";
                int nReview = -1;
                cin >> nReview;
                imprimeReviewEspecifica(nReview, caminhoBinario);
                break;
            }
        case sair:
        {
            return;
        }
        default:
        {
            break;
        }
        }
    }
}


int main(int argc, char* argv[])
{
    vector <Review> reviews;

      menu(arquivo_path, saidaBinaria_path, saidaTexto_path,reviews);
     // menu(argv[1],argv[2],argv[3],reviews);

    return 0;
}
