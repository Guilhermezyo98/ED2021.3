#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED

#include "leitura.h"

using namespace std;

void imprimeNMaisFrequentes(vector<pair<string, int>> &vetor, int nPrimeiros);

void escreveNMaisFrequentes(vector<pair<string, int>> &vetor, int nPrimeiros, string saidaPath = "teste.txt");

vector<pair<string, int>> testaTabelaHash(int hashSize);

class tabelaHash
{
private:
    vector<pair<string, int>> vetor;
    int m_tam;
    int m_insertionsFails;
    int m_colisoes;

private:
    int hash(string chave, int i);

    int ht_hash(string str, int prime, int tam);

public:
    tabelaHash(int tam);

    ~tabelaHash();

    void insertion(string x);

    vector<pair<string, int>> retornaApenasElementosPreenchidosVetor();

    void escreveTabelaHash();
};

#endif
