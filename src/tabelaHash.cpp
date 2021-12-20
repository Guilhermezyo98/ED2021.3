#include <iostream>
#include <cmath>
#include <fstream>
#include <cassert>

#include "tabelaHash.h"
#include "leitura.h"
#include "parametros.h"
#include "ordenacao.h"

using namespace std;

int const PRIME1 = 151;
int const PRIME2 = 157;

tabelaHash::tabelaHash(int tam)
	: m_tam(tam), m_insertionsFails(0), m_colisoes(0)
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
	const int hash_a = ht_hash(s, PRIME1, m_tam);
	const int hash_b = ht_hash(s, PRIME2, m_tam);
	return (hash_a + (i * (hash_b + 1))) % m_tam;
}

void tabelaHash::insertion(string key)
{
	for (int i = 0; i < m_tam; i++)
	{
		unsigned long index = hash(key, i);

		if (vetor[index].first.empty() || vetor[index].first == key) // ou espaco esta disponivel ou a chave eh identica
		{
			vetor[index].first = key;
			vetor[index].second++;
			return;
		}
		else
		{
			m_colisoes++;
		}
	}
	cerr << "\n[WARNING] fail in insertion element\n";
	m_insertionsFails++;
}

void imprimeNMaisFrequentes(vector<pair<string, int>>& vetor, int nPrimeiros)
{
	cout << endl;
	for (int i = 0; i < nPrimeiros && vetor.size(); ++i)
	{
		cout << vetor[i].first << " - frequencia: " << vetor[i].second << endl;
	}
}

void escreveNMaisFrequentes(vector<pair<string, int>>& vetor, int nPrimeiros, string saidaPath)
{
	fstream saida("./" + saidaPath, ios::out | ios::app);
	if (!saida.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao escreveNMaisFrequentes()";
		assert(false);
	}
	saida << "Impressao dos versions mais frequentes\n";
	for (int i = 0; i < nPrimeiros && i < vetor.size(); ++i)
	{
		saida << vetor[i].first << " - frequencia: " << vetor[i].second << endl;
	}
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

void tabelaHash::escreveTabelaHash() // util para visualizar distribuicao
{
	fstream saidaTxt("./teste.txt", ios::app | ios::out);
	if (!saidaTxt.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao escreveTabelaHash()";
		assert(false);
	}
	for (int i = 0; i < vetor.size(); ++i)
	{
		saidaTxt << vetor[i].first << " : " << vetor[i].second << ",\t";
		if (!((i + 1) % 10))
		{
			saidaTxt << endl;
		}
	}
}

vector<pair<string, int>> testaTabelaHash(int hashSize)
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
		if (app_version.empty()) // nenhuma review sem app version sera adicionada
		{
			--i;
			continue;
		}
		tabela.insertion(app_version);
	}

	cout << "\nDeseja escrever a distribuicao da tabela no arquivo teste.txt ? [s/n] ";
	char input = '\0';
	cin >> input;
	switch (input)
	{
	case 's':
		{
			tabela.escreveTabelaHash();
			break;
		}
	default:
		break;
	}

	vector<pair<string, int>> populares = tabela.retornaApenasElementosPreenchidosVetor();
	quickSortHash(populares, 0, populares.size() - 1);

	return populares;
}
