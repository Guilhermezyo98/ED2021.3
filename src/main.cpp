// ED2.cpp: define o ponto de entrada para o aplicativo.
//

#include "cabecalhos_basicos.h"
#include "Leitura.h"
#include "Timer.h"
#include "Parametros_constantes.h"

using namespace std;

int main()
{
	vector<Review> reviews;
	reviews.resize(tam_linhas);

	{
		Timer timer;
		lerArquivoCSV(arquivo_path, reviews);
	}

	int entrada = 0;
	while (true)
	{
		cout << "digite entrada, -1 interrompe" << endl;

		cin >> entrada;
		if (entrada == -1)
		{
			break;
		}
		imprimeReviewEspecifica(entrada, reviews);
	}
}
