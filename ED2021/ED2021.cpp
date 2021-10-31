// ED2.cpp: define o ponto de entrada para o aplicativo.
//

#include "ED2021.h"
#include <cassert>
#include <fstream>
#include <memory>
#include <string>
#include <iostream>

using namespace std;

struct Review;
void eraseSubStr();
void lerArquivoCSV();
void imprimeReviewEspecifica();
int _TAM_LINHAS = 3'660'725;
auto reviews = make_unique<Review[]>(_TAM_LINHAS);

struct Review
{
	string review_id;
	string review_text;
	string upvotes;
	string app_version;
	string posted_date;
};

void eraseSubStr(std::string& mainStr, const std::string& toErase)
{
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);
	if (pos != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}

void lerArquivoCSV(const char* path)
{
	fstream arquivo;
	arquivo.open(path, ios::in);
	if (!arquivo.good())
	{
		cerr << "ERRO: arquivo nao pode ser aberto";
		assert(false);
	}

	string str;
	arquivo.seekg(54, ios::cur); // pula primeira linha
	int i = 0;

	while (getline(arquivo, str))
	{
		if (str.find("gp:") != string::npos)
			// evita linhas ferradas,com quebra no meio do comentario, etc. Mas n ignora todas as ferradas
		{
			auto pos = str.find_first_of(',');
			if (pos != string::npos)
			{
				auto id = str.substr(0, pos);
				eraseSubStr(str, id);
				reviews[i].review_id = id;
				str.erase(0, 1); // remove virgula
				if (id.find("AOqpTOGzIxvnB1T6rW8cQKtWDx4v4Z3SpIVlg3s_6gIYpvhFB_OX") != string::npos)
				{
					__debugbreak();
				}
			}

			pos = str.find_last_of(',');
			if (pos != string::npos)
			{
				auto date = str.substr(pos);
				eraseSubStr(str, date);
				reviews[i].posted_date = date;
			}
			pos = str.find_last_of(',');
			if (pos != string::npos)
			{
				auto version = str.substr(pos);
				eraseSubStr(str, version);
				reviews[i].app_version = version;
			}
			pos = str.find_last_of(',');
			if (pos != string::npos)
			{
				auto upvotes = str.substr(pos);
				eraseSubStr(str, upvotes);
				reviews[i].upvotes = upvotes;
			}
			reviews[i].review_text = str;

			i++;
		}
		else
		{
			auto atual = ios::cur;
			string novaLinha;
			getline(arquivo, novaLinha);
			if (novaLinha.find("gp:") != string::npos)
			{
				auto pos = str.find_last_of(',');
				if (pos != string::npos)
				{
					auto date = str.substr(pos);
					eraseSubStr(str, date);
					reviews[--i].posted_date = date;
				}
				pos = str.find_last_of(',');
				if (pos != string::npos)
				{
					auto version = str.substr(pos);
					eraseSubStr(str, version);
					reviews[--i].app_version = version;
				}
				pos = str.find_last_of(',');
				if (pos != string::npos)
				{
					auto version = str.substr(pos);
					eraseSubStr(str, version);
					reviews[--i].app_version = version;
				}
			}
			reviews[--i].review_text += str;
			arquivo.seekg(0, atual);
		}
	}
}

void imprimeReviewEspecifica(int n)
{
	if (n < 0 || n > 3660725)
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

int main()
{
	auto arquivoPath = "C:/workspace/DCC012/ED2/input/tiktok_app_reviews.csv";

	lerArquivoCSV(arquivoPath);

	int entrada = 0;
	while (true)
	{
		cout << "digite entrada, -1 interrompe" << endl;

		cin >> entrada;
		if (entrada == -1)
		{
			break;
		}
		imprimeReviewEspecifica(entrada);
	}
}
