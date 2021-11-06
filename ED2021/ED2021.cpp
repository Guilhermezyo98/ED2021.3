// ED2.cpp: define o ponto de entrada para o aplicativo.
//

#include "ED2021.h"
#include <cassert>
#include <fstream>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "Timer.h"

using namespace std;
//
struct Review;
void apagar_sub_str(std::string& main_str, const std::string& apagar);
void lerArquivoCSV(const char* path, Review* reviews);
void trataLinhasQuebradas(fstream& arquivo, Review* reviews, string& str, long& i);
void imprimeReviewEspecifica(int n, Review* reviews);
void escreveBin(Review* reviews);
void leBin(Review* reviews);
vector<Review>* importarReviewsAleatorios(int qtd);
//
int const tam_linhas = 3'646'294;
const auto arquivo_path = "C:/workspace/DCC012/ED2/input/tiktok_app_reviews.csv";
const std::string
ultima_linha("AOqpTOEbcTyAsdBIJDmV9AgErmyPYiIHOp4QtLrq9qtudVW7DT25WgSfIc35DWSe7BSBPqwDnCjG8wfjL4LBkQ");

//
struct Review
{
	string review_id;
	string review_text;
	string upvotes;
	string app_version;
	string posted_date;
};

void apagar_sub_str(std::string& main_str, const std::string& apagar)
{
	auto pos = string::npos;
	if (apagar == ",")
	{
		pos = main_str.find_last_of(apagar);
	}
	else
	{
		pos = main_str.find(apagar);
	}

	if (pos != std::string::npos)
	{
		main_str.erase(pos, apagar.length());
	}
}

void peekline(fstream& arquivo, string& str)
{
	auto pos = arquivo.tellg();
	getline(arquivo, str);
	arquivo.seekg(pos);
}

void trataLinhasQuebradas(fstream& arquivo, vector<Review>& reviews, string& str, long& i)
{
	string nova_linha;
	peekline(arquivo, nova_linha);

	if (nova_linha.find("p:") != string::npos)
	{
		auto pos = str.find_last_of(',');
		if (pos != string::npos)
		{
			reviews[i].posted_date = move(str.substr(pos));
			apagar_sub_str(str, reviews[i].posted_date);
		}
		pos = str.find_last_of(',');
		if (pos != string::npos)
		{
			reviews[i].app_version = move(str.substr(pos));
			apagar_sub_str(str, reviews[i].app_version);
		}
		pos = str.find_last_of(',');
		if (pos != string::npos)
		{
			reviews[i].upvotes = move(str.substr(pos));
			apagar_sub_str(str, reviews[i].upvotes);
		}
		reviews[i].review_text += str;
		++i;
		return;
	}
	reviews[i].review_text += str;
}


void trataUltimaLinha(const fstream& fstream, vector<Review>& reviews, string& str, long i)
{
	auto pos = str.find_first_of(',');
	if (pos != string::npos)
	{
		reviews[i].review_id = str.substr(0, pos);
		apagar_sub_str(str, reviews[i].review_id);
		str.erase(0, 1);
	}
	pos = str.find_last_of(',');
	if (pos != string::npos)
	{
		reviews[i].posted_date = str.substr(pos);
		apagar_sub_str(str, reviews[i].posted_date);
	}
	pos = str.find_last_of(',');
	if (pos != string::npos)
	{
		reviews[i].app_version = str.substr(pos);
		apagar_sub_str(str, reviews[i].app_version);
	}
	pos = str.find_last_of(',');
	if (pos != string::npos)
	{
		reviews[i].upvotes = str.substr(pos);
		apagar_sub_str(str, reviews[i].upvotes);
	}
	reviews[i].review_text = move(str);
}

void lerArquivoCSV(const char* path, vector<Review>& reviews)
{
	fstream arquivo;
	arquivo.open(path, ios::in);
	if (!arquivo.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto";
		assert(false);
	}

	long i = 0;
	string str;
	size_t pos;

	arquivo.seekg(54, ios::beg); // pula primeira linha
	while (getline(arquivo, str))
	{
		// cout << str << "\n";

		if (str.find(ultima_linha) != string::npos)
		{
			trataUltimaLinha(arquivo, reviews, str, i);
			break;
		}
		if (str.find("p:") != string::npos)
		{
			pos = str.find_first_of(',');
			if (pos != string::npos)
			{
				reviews[i].review_id = move(str.substr(0, pos));
				apagar_sub_str(str, reviews[i].review_id);
				str.erase(0, 1);
			}

			string novaLinha;
			peekline(arquivo, novaLinha);
			if (novaLinha.find("p:") != string::npos)
			{
				auto pos = str.find_last_of(',');
				if (pos != string::npos)
				{
					reviews[i].posted_date = move(str.substr(pos));
					apagar_sub_str(str, reviews[i].posted_date);
				}
				pos = str.find_last_of(',');
				if (pos != string::npos)
				{
					reviews[i].app_version = move(str.substr(pos));
					apagar_sub_str(str, reviews[i].app_version);
				}
				pos = str.find_last_of(',');
				if (pos != string::npos)
				{
					reviews[i].upvotes = move(str.substr(pos));
					apagar_sub_str(str, reviews[i].upvotes);
				}
				reviews[i].review_text = move(str);
				++i;
			}
			else
				trataLinhasQuebradas(arquivo, reviews, str, i);
		}
		else
		{
			trataLinhasQuebradas(arquivo, reviews, str, i);
		}
	}
}

void escreveBin(Review* reviews)
{
	fstream arqBin;
	arqBin.open(arquivo_path, ios::out | ios::binary | ios::app);
	//Abrir arquivo out: saída, binário, app:add no final
	if (!arqBin.good())
	{
		cerr << "ERRO: arquivo nao pode ser aberto";
		assert(false);
	}

	arqBin.write((char*)&reviews, sizeof(Review));

	//arqBin.flush(); //Encerrar inserção. 
	arqBin.close(); //Fechar arquivo
}

void leBin(Review* reviews)
{
	fstream arqBin;
	arqBin.open(arquivo_path, ios::binary); //Abrir arquivo
	if (!arqBin.good())
	{
		cerr << "ERRO: arquivo nao pode ser aberto";
		assert(false);
	}
	arqBin.read(reinterpret_cast<char*>(&reviews), sizeof(Review));
	arqBin.close(); //Fechar arquivo
}

void imprimeReviewEspecifica(int n, vector<Review>& reviews)
{
	if (n < 0 || n >= tam_linhas)
	{
		cout << endl << "fora do vetor" << endl;
		return;
	}
	cout << "review_id: " << reviews[n].review_id << endl;
	cout << "review_text: " << reviews[n].review_text << endl;
	cout << "upvotes: " << reviews[n].upvotes << endl;
	cout << "app_version: " << reviews[n].app_version << endl;
	cout << "posted_date: " << reviews[n].posted_date << endl;
}

vector<Review>* importarReviewsAleatorios(int qtd)
{
	// TODO: otimar para ler de maneira aleatoria a qtd necessaria do arquivo bin

	fstream arqBin;
	arqBin.open(arquivo_path, ios::binary); //Abrir arquivo
	if (!arqBin.good())
	{
		cerr << "ERRO: arquivo nao pode ser aberto";
		assert(false);
	}
	vector<Review> aux;
	aux.resize(tam_linhas);

	vector<Review> aleatorio;
	aleatorio.resize(qtd);

	string str;
	while (std::getline(arqBin, str))
	{
		arqBin.read(reinterpret_cast<char*>(&aux), sizeof(Review)); //ler arquivo e armazenar no vetor auxiliar
	}
	for (int i = 0; i < qtd; i++)
	{
		int numAleatorio = (rand() % tam_linhas); // Gerando numeros aleatorios
		aleatorio[i] = aux[numAleatorio];
		//vetor de reviews aleatorios recebe reviews das posições sorteadas                  
	}
	arqBin.close(); //Fechar arquivo
	return &aleatorio;
}

int main()
{
	
	vector<Review> reviews;
	reviews.resize(tam_linhas);
	
	{
		Timer timer;
		lerArquivoCSV(arquivo_path, reviews);
	}

	int entrada = 0;
	while (true)
	{
		cout << "digite entrada, -1 interrompe" << endl;

		cin >> entrada;
		if (entrada == -1)
		{
			break;
		}
		imprimeReviewEspecifica(entrada, reviews);
	}
}
