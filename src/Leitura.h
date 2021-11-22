#ifndef LEITURA_H
#define LEITURA_H

#include "cabecalhos_basicos.h"

using namespace std;

struct Review
{
    string review_id;
    string review_text;
    string upvotes;
    string app_version;
    string posted_date;
};

struct Review;

void lerArquivoCSV(string path, vector<Review>& reviews);
int retonaNumeroAleatorio(int min, int max);

void imprimeReviewEspecifica(int reviewN, string caminhoBinario);
void imprimeReviewEspecifica(int reviewN, fstream arquivoBinario);
void imprimeReviewEspecifica(Review review);

Review retornaReviewEspecifica(int reviewN, fstream& arquivoBinario);
void testeImportacao(string caminhoEntrada, string caminhoBinario, string caminhoTexto);

void escreveBin(string caminhoSaida, vector<Review>& reviews);
void escreveTexto(vector<Review>& reviews);
void leBin(string caminho);

#endif // !LEITURA_H