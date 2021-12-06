#ifndef LEITURA_H
#define LEITURA_H

#include <vector>
#include <string>

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

void lerArquivoCSV(string pathCSV, vector<Review>& reviews);
int retonaNumeroAleatorio(int min, int max);

void imprimeReviewEspecifica(int pos, fstream& entradaBinaria);
void imprimeReviewEspecifica(Review review);

Review retornaReviewEspecifica(int indice, fstream& arquivoBinario);
void testeImportacao();

void escreverSaidaBinaria(vector<Review>& reviews);
void escreverSaidaTxt(vector<Review>& reviews);
void lerBinario();

#endif // !LEITURA_H
