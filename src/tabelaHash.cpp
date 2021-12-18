#include <iostream>
#include <cmath>
#include "tabelaHash.h"
#include "leitura.h"
#include "parametros.h"
#include <fstream>
#include <cassert>

using namespace std;

int const PRIME1 = 151;
int const PRIME2 = 157;

tabelaHash::tabelaHash(int tam)
	: tam(tam), insertionsFails(0), colisoes(0)
{
	vetor.resize(tam);

	for (int i = 0; i < tam; i++)
	{
		vetor[i].first = "";
		vetor[i].second = 0;
	}
}

tabelaHash::~tabelaHash() = default;

int tabelaHash::ht_hash(string str, int prime, int tam)
{
	long hash = 0;
	const int lengthStr = str.length();

	for (int i = 0; i < lengthStr; i++)
	{
		hash += (long)pow(prime, lengthStr - (i + 1)) * str[i];
		hash = ((((hash) % tam) + (i * (((hash) % tam)))) % tam);
	}
	return (int)hash;
}

int tabelaHash::hash(string s, int i)
{
	const int hash_a = ht_hash(s, PRIME1, tam);
	const int hash_b = ht_hash(s, PRIME2, tam);
	return (hash_a + (i * (hash_b + 1))) % tam;
}

void tabelaHash::insertion(string key)
{
	for (int i = 0; i < tam; i++)
	{
		unsigned long index = hash(key, i);

		if (vetor[index].first.empty() || vetor[index].first == key) // ou espaco esta disponivel ou a chave eh identica
		{
			vetor[index].first = key;
			vetor[index].second ++;
			return;
		}
		else
		{
			colisoes++;
		}
	}
	cerr << "\n[WARNING] fail in insertion element\n";
	insertionsFails++;
}

void tabelaHash::txtFrequentes(int numImpressao, vector<pair<string, int>>& vetor, int tamTabela)
{
	ofstream arquivotxt("saixaTabelaHash.txt", ios::app);
	arquivotxt << "*** Tabela Hash ***" << endl;

	for (int i = tamTabela; i >= numImpressao; i--)
	{
		arquivotxt << i + 1 << ": " << vetor[i].first << "  Número de repetições: " << vetor[i].second << endl;
	}
}

void quickSortHash(vector<pair<string, int>>& vetor, int inicio, int fim)
{
	if (inicio < fim)
	{
		int pivo = quickSortHashAux(vetor, inicio, fim);
		quickSortHash(vetor, inicio, pivo - 1);
		quickSortHash(vetor, pivo + 1, fim);
	}
}

int quickSortHashAux(vector<pair<string, int>>& vet, int inicio, int final)
{
	int pivot = vet[final].second; // pivot
	int i = (inicio - 1); // Index of smaller element

	for (int j = inicio; j <= final - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (vet[j].second >= pivot)
		{
			i++; // increment index of smaller element
			std::swap(vet[i], vet[j]);
		}
	}
	std::swap(vet[i + 1], vet[final]);
	return (i + 1);
}

vector<pair<string, int>> tabelaHash::retornaApenasElementosPreenchidosVetor()
{
	vector<pair<string, int>> temp;
	for (int i = 0; i < vetor.size(); ++i)
	{
		if (!vetor[i].first.empty())
		{
			temp.push_back(vetor[i]);
		}
	}
	return temp;
}

void tabelaHash::imprimeVetor() // util para visualizar distribuicao
{
	for (int i = 0; i < vetor.size(); ++i)
	{
		cout << vetor[i].first << " : " << vetor[i].second << ",\t";
		if ((i + 1) % 10 == 0)
		{
			cout << endl;
		}
	}
}

void imprimeVetor(vector<pair<string, int>>& vetor) // util para visualizar distribuicao
{
	for (int i = 0; i < vetor.size(); ++i)
	{
		cout << vetor[i].first << " : " << vetor[i].second << ",\t";
		if ((i + 1) % 10 == 0)
		{
			cout << endl;
		}
	}
}

void desempenhoHash(int hashSize, int parametro)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
	if (!arquivoBinario.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao desempenhoHash()";
		assert(false);
	}

	tabelaHash tabela(hashSize * 1.3f);
	string app_version;
	for (int i = 0; i < hashSize; i++)
	{
		app_version = retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario).app_version;
		if (app_version.empty())
		{
			--i;
			continue;
		}
		tabela.insertion(app_version);
	}
	vector<pair<string, int>> ordenados = tabela.retornaApenasElementosPreenchidosVetor();

	cout << "\nvetor original:\n";
	imprimeVetor(ordenados);

	quickSortHash(ordenados, 0, ordenados.size() - 1);

	// tabela.txtFrequentes(parametro, tabela.retornaApenasElementosPreenchidosVetor(), hashSize - 1);

	cout << "\nvetor ordenado:\n";
	imprimeVetor(ordenados);
}
