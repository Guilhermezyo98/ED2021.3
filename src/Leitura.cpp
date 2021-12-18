#include <cassert>
#include <iostream>
#include <fstream>
#include <memory>
#include <strstream>
#include <cstdlib>
#include "leitura.h"
#include "parametros.h"
#include <memory>

#include "Timer.h"

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
	fstream entradaCSV(pathCSV, ios::in);
	if (!entradaCSV.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto \n\t lerArquivoCSV";
		assert(false);
	}
	reviews.reserve(reviews_totais);
	auto bufferSize = tamanhoArquivo(entradaCSV);
	entradaCSV.seekg(54, ios::beg);
	unique_ptr<char[]> buffer(new char[bufferSize]);
	entradaCSV.read(buffer.get(), bufferSize);

	istrstream lines((buffer.get()), static_cast<int>(bufferSize));
	entradaCSV.close();

	Review review;
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
		review.upvotes = atoi(linha.c_str());

		getline(lines, linha, ',');
		review.app_version = linha;

		getline(lines, linha);
		review.posted_date = linha;

		review.review_id.resize(TAMANHO_MAX_ID);
		review.app_version.resize(TAMANHO_MAX_APP_VERSION);
		review.posted_date.resize(TAMANHO_MAX_DATE);
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
		saidaBinaria.write(reinterpret_cast<char*>(&reviews[i].upvotes), sizeof(int));
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

	Review review = retornaReviewEspecifica(indice, entradaBinaria);
	imprimeReviewEspecifica(review);
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

	arquivoBinario.read(reinterpret_cast<char*>(&review.upvotes), sizeof(int));

	char app_version[TAMANHO_MAX_APP_VERSION];
	arquivoBinario.read(app_version, TAMANHO_MAX_APP_VERSION);
	review.app_version = app_version;

	char posted_date[TAMANHO_MAX_DATE];
	arquivoBinario.read(posted_date, TAMANHO_MAX_DATE);
	review.posted_date = posted_date;

	return review;
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

void inicializaVetorAleatorio(vector<Review>& reviews, int size)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
	if (!arquivoBinario.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao inicializaVetor()";
		assert(false);
	}

	for (int j = 0; j < size; j++)
	{
		reviews.resize(size);
		reviews[j] = retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario);
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
	cout << "\t\t\tDigite 'c' para exporta N registros para o console," << endl;
	cout << "\t\t\tDigite 'a' para exportar N registros para arquivo texto" << endl;
	cout << "\t\t\tDigite 'i' para: imprimeReviewEspecifica(i)\n";
	cout << "\t\t\tDigite 's' para sair " << endl;
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
				reviews[i] = retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario);
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
