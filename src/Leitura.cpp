#include <cassert>
#include <iostream>
#include <fstream>
#include <memory>
#include <strstream>
#include <cstdlib>
#include "Leitura.h"
#include "Parametros.h"
#include <memory>

streampos inline tamanhoArquivo(fstream& arq)
{
	arq.seekg(0, arq.end);
	streampos tam = arq.tellg();
	arq.seekg(0);
	return tam;
}

void lerArquivoCSV(string pathCSV, vector<Review>& reviews)
{
	if (reviews.size() == reviews_totais)
	{
		cerr << "\n\n\t\tacredito que voce tenha selecionado para ler arquivo csv 2x, cuidado!\n\n";
		return;
	}
	reviews.reserve(reviews_totais);
	fstream entradaCSV(pathCSV, ios::in);
	if (!entradaCSV.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto \n\t lerArquivoCSV";
		assert(false);
	}
	auto bufferSize = tamanhoArquivo(entradaCSV);
	entradaCSV.seekg(54, ios::beg);
	unique_ptr<char[]> buffer(new char[bufferSize]);
	entradaCSV.read(buffer.get(), bufferSize);

	istrstream lines((buffer.get()), static_cast<int>(bufferSize));
	entradaCSV.close();

	Review review;
	review.review_id.resize(TAMANHO_MAX_ID);
	review.app_version.resize(TAMANHO_MAX_APP_VERSION);
	review.upvotes.resize(TAMANHO_MAX_UPVOTES);
	review.posted_date.resize(TAMANHO_MAX_DATE);
	string linha;
	for (unsigned long i = 0; i < reviews_totais; ++i)
	{
		getline(lines, linha, ',');
		review.review_id = linha;

		if (lines.get() == '"')
		{
			while (true)
			{
				getline(lines, linha, '"');
				review.review_text += linha;
				if (lines.get() != '"')
				{
					break;
				}
			}
		}
		else
		{
			lines.seekg(-1, ios::cur);
			getline(lines, linha, ',');
			review.review_text = linha;
		}

		getline(lines, linha, ',');
		review.upvotes = linha;

		getline(lines, linha, ',');
		review.app_version = linha;

		getline(lines, linha);
		review.posted_date = linha;

		review.review_text.resize(TAMANHO_MAX_TEXT);

		reviews.push_back(review);
	}
}

void escreverSaidaBinaria(vector<Review>& reviews)
{
	if (reviews.size() == 0)
	{
		cerr << "\n\n\t\tvoce deveria ler o arquivo antes de tentar escrever, cuidado!\n\n";
		return;
	}

	fstream saidaBinaria("./saidaBinaria.bin", ios::binary | ios::trunc | ios::in | ios::out);
	if (!saidaBinaria.is_open())
	{
		cerr <<
			"ERRO: arquivo nao pode ser aberto \n\t escreveBin() \n\t provavelmente nao foi possivel criar o arquivo, peco que crie manualmente se for o caso\n";
		assert(false);
	}

	for (unsigned long i = 0; i < reviews.size(); i++)
	{
		saidaBinaria.write(reviews[i].review_id.c_str(), TAMANHO_MAX_ID);
		saidaBinaria.write(reviews[i].review_text.c_str(), TAMANHO_MAX_TEXT);
		saidaBinaria.write(reviews[i].upvotes.c_str(), TAMANHO_MAX_UPVOTES);
		saidaBinaria.write(reviews[i].app_version.c_str(), TAMANHO_MAX_APP_VERSION);
		saidaBinaria.write(reviews[i].posted_date.c_str(), TAMANHO_MAX_DATE);
	}
	reviews.clear(); // forcando o desalocamento previo
}

void imprimeReviewEspecifica(int indice, fstream& entradaBinaria)
{
	if (!entradaBinaria.is_open())
	{
		cerr <<
			"ERRO: arquivo nao pode ser aberto \n\t imprimeReviewEspecifica()\n  \n\t provavelmente nao foi possivel criar o arquivo, peco que crie manualmente se for o caso\n";
		assert(false);
	}

	int const pos = (indice) * TAMANHO_MAX_STRUCT;
	entradaBinaria.seekg(pos);

	Review review;

	char id[TAMANHO_MAX_ID];
	entradaBinaria.read(id, TAMANHO_MAX_ID);
	review.review_id = id;

	char review_text[TAMANHO_MAX_TEXT];
	entradaBinaria.read(review_text, TAMANHO_MAX_TEXT);
	review.review_text = review_text;

	char upvotes[TAMANHO_MAX_UPVOTES];
	entradaBinaria.read(upvotes, TAMANHO_MAX_UPVOTES);
	review.upvotes = upvotes;

	char app_version[TAMANHO_MAX_APP_VERSION];
	entradaBinaria.read(app_version, TAMANHO_MAX_APP_VERSION);
	review.app_version = app_version;

	char posted_date[TAMANHO_MAX_DATE];
	entradaBinaria.read(posted_date, TAMANHO_MAX_DATE);
	review.posted_date = posted_date;

	imprimeReviewEspecifica(review);
}

void imprimeReviewEspecifica(Review review)
{
	cout << endl;
	cout << "review_id: " << review.review_id << endl;
	cout << "review_text: " << review.review_text << endl;
	cout << "upvotes: " << review.upvotes << endl;
	cout << "app_version: " << review.app_version << endl;
	cout << "posted_date: " << review.posted_date << endl;
	cout << endl;
}

Review retornaReviewEspecifica(int indice, fstream& arquivoBinario)
{
	if (!arquivoBinario.is_open())
	{
		cerr <<
			"ERRO: arquivo nao pode ser aberto \n\t retornaReviewEspecifica()  \n\t provavelmente nao foi possivel criar o arquivo, peco que crie manualmente se for o caso\n";
		assert(false);
	}
	const int pos = (indice) * TAMANHO_MAX_STRUCT;
	arquivoBinario.seekg(pos);
	Review review;

	char id[TAMANHO_MAX_ID];
	arquivoBinario.read(id, TAMANHO_MAX_ID);
	review.review_id = id;

	char review_text[TAMANHO_MAX_TEXT];
	arquivoBinario.read(review_text, TAMANHO_MAX_TEXT);
	review.review_text = review_text;

	char upvotes[TAMANHO_MAX_UPVOTES];
	arquivoBinario.read(upvotes, TAMANHO_MAX_UPVOTES);
	review.upvotes = upvotes;

	char app_version[TAMANHO_MAX_APP_VERSION];
	arquivoBinario.read(app_version, TAMANHO_MAX_APP_VERSION);
	review.app_version = app_version;

	char posted_date[TAMANHO_MAX_DATE];
	arquivoBinario.read(posted_date, TAMANHO_MAX_DATE);
	review.posted_date = posted_date;

	return review;
}

int retonaNumeroAleatorio(int min, int max)
{
	static constexpr double fraction{1.0 / (RAND_MAX + 1.0)};
	return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}

void escreverSaidaTxt(fstream& saidaTxt, vector<Review>& reviews)
{
	if (!saidaTxt.is_open())
	{
		cerr <<
			"ERRO: arquivo nao pode ser aberto \n\t escreveTexto()  \n\t provavelmente nao foi possivel criar o arquivo, peco que crie manualmente se for o caso\n";
		assert(false);
	}

	for (unsigned long i = 0; i < reviews.size(); i++)
	{
		saidaTxt << reviews[i].review_id << ',';
		saidaTxt << reviews[i].review_text << ',';
		saidaTxt << reviews[i].upvotes << ',';
		saidaTxt << reviews[i].app_version << ',';
		saidaTxt << reviews[i].posted_date << ',';
		saidaTxt << "\n";
	}
}

void heapSort(vector<Review>& reviews, int n)
{
	for (int i = n - 1; i >= 0; i--)
	{
		heapify(reviews, n, i);
	}

	for (int i = n - 1; i >= 0; i--)
	{
		swap(reviews[0], reviews[i]);
		heapify(reviews, i, 0);
	}
}

void heapify(vector<Review>& reviews, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && reviews[l].upvotes > reviews[largest].upvotes)
		largest = l;

	if (r < n && reviews[r].upvotes > reviews[largest].upvotes)
		largest = r;

	if (largest != i)
	{
		swap(reviews[i], reviews[largest]);
		heapify(reviews, n, largest);
	}
}

enum Saidas
{
	consoleN = 'c',
	arquivoN = 'a',
	imprime_Review_Especifica = 'i',
	sair = 's'
};

void testeImportacao()
{
	cout << "\t\ttesteImportacao()\n:" << endl;
	cout << "\t\t\tDigite 1 para exporta N registros para o console," << endl;
	cout << "\t\t\tDigite 2 para exportar N registros para arquivo texto" << endl;
	cout << "\t\t\tDigite 3 para: imprimeReviewEspecifica(i)\n";
	cout << "\t\t\tDigite 4 para sair " << endl;
	cout << "\t\t\t";

	char input = '\0';
	cin >> input;

	switch (input)
	{
	case consoleN:
		{
			cout << "\n Digite o valor para N";
			int N = -1;
			cin >> N;
			fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
			for (int i = 0; i < N; i++)
			{
				imprimeReviewEspecifica(
					retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario));
			}
			break;
		}
	case arquivoN:
		{
			cout << "\n Digite o valor para N";
			int N = -1;
			cin >> N;
			vector<Review> reviews(N);
			fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
			fstream arquivoTexto("./saidaTxt.txt", ios::in | ios::trunc | ios::out);
			for (int i = 0; i < N; i++)
			{
				reviews[i] = (retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario));
			}
			escreverSaidaTxt(arquivoTexto, reviews);
			cout << "\n\n-------------Exportacao finalizada!-------------\n\n";
			break;
		}
	case imprime_Review_Especifica:
		{
			cout << "\nDigite o numero da review a ser impressa: ";
			int nReview = -1;
			cin >> nReview;
			fstream saidaBinaria("./saidaBinaria.bin", ios::in | ios::binary);
			imprimeReviewEspecifica(nReview, saidaBinaria);
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

//////////quick///////
void quickSort(vector<Review>& v,int inicio,int fim,desempenho *desempenho){
    int pivo;

    if(inicio < fim){
        pivo = quickAux(v,inicio,fim,desempenho);
        quickSort(v,inicio,pivo-1,desempenho);
        quickSort(v,pivo+1,fim,desempenho);
    }

}
int quickAux(vector<Review>& v,int inicio ,int final,desempenho *desempenho){
    Review aux;                                // review auxiliar
    int esq = inicio;                           // Inteiro que mostra onde inicia o vetor
    int dir = final;                            // Final que guarda a ultima posição do vetor

    Review pivo = v[inicio];           // Pivo a chave que sera comparada

    while(esq < dir){
        while(esq <= dir && v[esq].upvotes <= pivo.upvotes){
            esq ++;
            desempenho->numComparacoes = desempenho->numComparacoes + 1;
        }

        desempenho->numComparacoes = desempenho->numComparacoes + 1;

        while(dir >= 0 && v[dir].upvotes > pivo.upvotes){
            desempenho->numComparacoes = desempenho->numComparacoes + 1;
            dir --;
        }
        desempenho->numComparacoes = desempenho->numComparacoes + 1;
        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
            desempenho->numTrocas = desempenho->numTrocas + 1;
        }
    }
    v[inicio] = v[dir];
    v[dir] = pivo;
    desempenho->numTrocas = desempenho->numTrocas + 1;
    return dir;
}