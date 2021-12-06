// ED2.cpp: define o ponto de entrada para o aplicativo.
//
#include "Leitura.h"
#include "Timer.h"
#include <iostream>

#include "parametros.h"

using namespace std;

enum EscolhasChamada
{
	lerCSV = 1,
	escreverBinario = 2,
	teste_Importacao = 3,
	sair = 4
};

void menu(string caminhoEntrada, vector<Review>& reviews)
{
	while (true)
	{
		cout << "**************\tMENU\t**************";
		cout << "\nEscolhe entre usar as funcoes:\n";
		cout << "\tDigite 1 para: lerCSV() \n";
		cout << "\tDigite 2 para: escreverBinario()\n";
		cout << "\tDigite 3 para: testeImportacao() \n";

		cout << "\tDigite 4 para sair " << endl;

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
					escreverSaidaBinaria(reviews);
					break;
				}
			}
		case teste_Importacao:
			{
				testeImportacao();
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
	vector<Review> reviews;

	// menu(arquivo_path, reviews);
	menu(argv[1], reviews);

	return 0;
}
