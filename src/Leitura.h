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


void lerArquivoCSV(const char* path, vector<Review>& reviews);
int getRandomNumber(int min, int max);
void imprimeReviewEspecifica(int reviewN);
Review retornaReviewEspecifica(int reviewN);
void imprimeReviewEspecifica(Review review);
void testeImportacao();

void escreveBin(vector<Review>& reviews);
void escreveTexto(vector<Review> reviews);


void leBin(string caminho);

#endif // !LEITURA_H