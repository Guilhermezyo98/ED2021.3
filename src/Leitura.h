#ifndef LEITURA_H
#define LEITURA_H

#include <vector>
#include <string>
using namespace std;

struct Review
{
	string review_id;
	string review_text;
	int upvotes;
	string app_version;
	string posted_date;
};

struct desempenho{
    string nome_algoritimo;           // Nome do algoritmo (Nome)
    int numComparacoes;               // Guarda a quantidade de comparacoes feitas em cada uma das repeticoes        
    int numTrocas;                    // Guarda a quantidade de trocas feitas em cada uma das repeticoes    
    double tempo;                        // Guarda o tempo de execucao            
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
