// ED2.cpp: define o ponto de entrada para o aplicativo.
//
#include "leitura.h"
#include "Timer.h"
#include <iostream>
#include "tabelaHash.h"
#include "parametros.h"

using namespace std;

enum EscolhasChamada
{
	lerCSV = 'l',
	escreverBinario = 'e',
	teste_Importacao = 't',
	ordenacao = 'o',
	sair = 's',
	tabela_Hash = 'h'
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
		cout << "\tDigite 'h' para: tabelaHash() \n";
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
				//Timer timer("HeapSort");
				////timer.benchHeapSort(3);
				//Timer timerQuick("QuickSort");
				//timerQuick.benchQuickSort(3);
				break;
			}
		case tabela_Hash:
			{
				tabelaHash tabela(10000);
				while (true){
					cout << "1-modulo de teste para desenvolverdor\n2-atividade\n3-sair\n";
					int escolha;
					cin>>escolha;
					if(escolha==1){
						while (true){
						cout << "1-Adicionar string\n2-ver se uma string esta na lista\n3-sair\n";
						int escolha2;
						cin>>escolha2;
						string aux;
						if(escolha2==1){
							cin>>aux;
							tabela.adiciona(aux);
						}
						if(escolha2==2){
							cin>>aux;
							if(tabela.verificaChave(aux))
								cout << "chave presente\n";
							else{
								cout << "chave não presente\n";
							}
						}
						if(escolha2==3){
							return;
					}

				}
					}
					if(escolha==2)
					{
						int valores,quantidades;
						cout << "Digite quantos valores deveram ser importados para a tabela Hashs: " ;
						cin >> valores;
						cout << "Digite a quantidade de mais frequentes: " ;
						cin >> quantidades;
						cout << "Executando o desempenho da tabela Hash! " << endl;
						desempenhoHash(valores,quantidades,0,valores);
						break;
					}
					if(escolha==3){
						return;
					}

				}
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
