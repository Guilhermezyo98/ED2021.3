#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED

#include "leitura.h"

using namespace std;

class tabelaHash
{
private:
	vector<pair<string, int>> vetor;
	int tam;

	int hash(string chave, int i);
	bool adicionaAux(int ind, string info, int tentativa);
	long int StringToInt(string x);
	int ht_hash(string str, int prime, int tam);

public:
	int insertionsFails;
	int colisoes;

	tabelaHash(int tam);
	~tabelaHash();

	vector<pair<string, int>> retornaApenasElementosPreenchidosVetor();

	void imprimeVetor();
	string get(int index);
	void insertion(string x);
	int index(string);
	void txtFrequentes(int numImpressao, vector<pair<string, int>>& vetor, int tamTabela);
};

void quickSortHash(vector<pair<string, int>>& vetor, int inicio, int fim);
int quickSortHashAux(vector<pair<string, int>>& vet, int inicio, int final);
void desempenhoHash(int hashSize, int parametro);

#endif
