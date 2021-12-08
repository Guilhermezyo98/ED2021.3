// ED2.cpp: define o ponto de entrada para o aplicativo.
//
#include <fstream>

#include "Leitura.h"
#include "Timer.h"
#include <iostream>

#include "Parametros.h"

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
				fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
				vector<Review> ordenado(retonaNumeroAleatorio(0, reviews_totais));
				for (unsigned int i = 0; i < ordenado.size(); i++)
				{
					ordenado[i] = retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario);
					imprimeReviewEspecifica(ordenado[i]);
				}
				//* HeapSort :
				heapSort(ordenado, ordenado.size());
				//* QuickSort:
				// TODO: quicksort
				//
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
