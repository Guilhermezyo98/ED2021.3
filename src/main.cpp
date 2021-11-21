// ED2.cpp: define o ponto de entrada para o aplicativo.
//

#include "cabecalhos_basicos.h"
#include "Leitura.h"
#include "Timer.h"
#include "Parametros_constantes.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector <Review> reviews;
    reviews.reserve(tam_linhas);

    {
        Timer timer;
        lerArquivoCSV(arquivo_path, reviews);
    }


    escreveBin(reviews);

    testeImportacao();
    return 0;
}
