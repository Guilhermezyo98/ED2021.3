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
void apagar_sub_str(std::string& main_str, const std::string& apagar);
void lerArquivoCSV(string path,string caminhoSaida);
void trataLinhasQuebradas(fstream& arquivo, Review *reviews, string& str, long& i);
void imprimeReviewEspecifica(int n, vector<Review>& reviews);
void escreveBin(Review* reviews,string caminhoSaida,fstream *arqBin);
void leBin(Review* reviews);
vector<Review>* importarReviewsAleatorios(int qtd,string caminhoSaida);

#endif // !LEITURA_H