// ED2.cpp: define o ponto de entrada para o aplicativo.
//
#include "leitura.h"
#include "Timer.h"
#include <iostream>

#include "parametros.h"

using namespace std;

enum EscolhasChamada
{
	lerCSV = 'l',
	escreverBinario = 'e',
	teste_Importacao = 't',
	ordenacao = 'o',
	sair = 's'
};

void menu(string caminhoEntrada, vector<Review>& reviews)
{
	while (true)
	{
		cout << "**************\tMENU\t**************";
		cout << "\nEscolhe entre usar as funcoes:\n";
		cout << "\tDigite 'l' para: lerCSV() \n";
		cout << "\tDigite 'e' para: escreverBinario()\n";
		cout << "\tDigite 't' para: testeImportacao() \n";
		cout << "\tDigite 'o' para: ordenacao() \n";
		cout << "\tDigite 's' para sair " << endl;

		char entrada = '\0';
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
		case ordenacao:
			{
				Timer timer("HeapSort");
				timer.benchHeapSort(3);
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
	srand(static_cast<unsigned int>(time(nullptr)));
	vector<Review> reviews;

	menu(arquivo_path, reviews);
	// menu(argv[1], reviews);

	return 0;
}
