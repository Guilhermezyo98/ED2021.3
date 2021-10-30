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
int _TAM_LINHAS = 3660725;
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
	arquivo.seekg(57, ios::cur); // pula primeira linha
	int i = 0;

	while (getline(arquivo, str))
	{
		if (str.find("gp:") == 0)
			// evita linhas ferradas,com quebra no meio do comentario, etc. Mas n ignora todas as ferradas
		{
			// pega ultima parte da string
			auto date = str.substr(str.find_last_of(','));
			eraseSubStr(str, date); // remove data coletada da linha
			date.erase(0, 1); // remove virgula da data
			reviews[i].posted_date = date;
			cout << "posted_date: " << reviews[i].posted_date << "\n ";

			// idem
			auto version = str.substr(str.find_last_of(','));
			eraseSubStr(str, version);
			version.erase(0, 1);
			reviews[i].app_version = version;
			cout << "app_version: " << reviews[i].app_version << "\n ";

			auto upvotes = str.substr(str.find_last_of(','));
			eraseSubStr(str, upvotes);
			upvotes.erase(0, 1);
			reviews[i].upvotes = upvotes;
			cout << "upvotes: " << reviews[i].upvotes << "\n ";

			str.erase(0, 3); // remove gpa:
			auto id = str.substr(0, str.find_first_of(','));
			reviews[i].review_id = id;
			cout << "review_id: " << reviews[i].review_id << "\n ";

			// no fim a linha, str, so vai conter o review_text 
			eraseSubStr(str, id);
			str.erase(0, 1);
			reviews[i].review_text = str;
			cout << "review_text: " << reviews[i].review_text << "\n ";
		}
	}
}

void imprimeReviewEspecifica(int n)
{
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
