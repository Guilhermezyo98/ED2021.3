// ED2.cpp: define o ponto de entrada para o aplicativo.
//

#include "cabecalhos_basicos.h"
#include "Leitura.h"
#include "Timer.h"
#include "Parametros_constantes.h"

using namespace std;

int main(int argc, char* argv[])
{

	vector<Review> reviews;
	reviews.resize(120);
	{
		Timer timer;
		lerArquivoCSV(argv[1],argv[2]);
	}

    //reviews = importarReviewsAleatorios(100,argv[2]);
	
	int entrada = 0;
	while (true)
	{
		cout << "digite entrada, -1 interrompe" << endl;

		cin >> entrada;
		if (entrada == -1)
		{
			break;
		}
		//imprimeReviewEspecifica(entrada, *reviews);
	}
}
