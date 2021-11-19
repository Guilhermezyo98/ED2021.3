#include <string>
#include <vector>
#include "Parametros_constantes.h"
#include "Leitura.h"

using namespace std;

void apagar_sub_str(std::string& main_str, const std::string& apagar)
{
    size_t pos;
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

void peekline(std::fstream& arquivo, std::string& str)
{
    auto pos = arquivo.tellg();
    getline(arquivo, str);
    arquivo.seekg(pos);
}

void trataLinhasQuebradas(std::fstream& arquivo, std::vector<Review>& reviews, string& str, long& i)
{
    string nova_linha;
    peekline(arquivo, nova_linha);

    if (nova_linha.find("p:") != string::npos)
    {
        auto pos = str.find_last_of(',');
        if (pos != string::npos)
        {
            reviews[i].posted_date = str.substr(pos);
            apagar_sub_str(str, reviews[i].posted_date);
            reviews[i].posted_date.erase(0, 1);
        }
        pos = str.find_last_of(',');
        if (pos != string::npos)
        {
            reviews[i].app_version = str.substr(pos);
            apagar_sub_str(str, reviews[i].app_version);
            reviews[i].app_version.erase(0, 1);
        }
        pos = str.find_last_of(',');
        if (pos != string::npos)
        {
            reviews[i].upvotes = str.substr(pos);
            apagar_sub_str(str, reviews[i].upvotes);
            reviews[i].upvotes.erase(0, 1);
        }
        reviews[i].review_text += str;
        reviews[i].review_text.erase(0, 1);

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

    }
    pos = str.find_last_of(',');
    if (pos != string::npos)
    {
        reviews[i].posted_date = str.substr(pos);
        apagar_sub_str(str, reviews[i].posted_date);
        reviews[i].posted_date.erase(0, 1);
    }
    pos = str.find_last_of(',');
    if (pos != string::npos)
    {
        reviews[i].app_version = str.substr(pos);
        apagar_sub_str(str, reviews[i].app_version);
        reviews[i].app_version.erase(0, 1);
    }
    pos = str.find_last_of(',');
    if (pos != string::npos)
    {
        reviews[i].upvotes = str.substr(pos);
        apagar_sub_str(str, reviews[i].upvotes);
        reviews[i].upvotes.erase(0, 1);
    }
    reviews[i].review_text = move(str);
}



/// <summary>
///
/// CODIGO LEGADO PARA LEITURA DE ARQUIVO, MENOS VELOZ, MAS CONFIAVEL
///  - MANTIDO POR JA TER SIDO BASTANTE TESTADO E CONFIAVEL
///  - MAIS LENTO QUE A VERSAO NOVA
///
/// </summary>
/// <param name="path"></param>
/// <param name="reviews"></param>
void lerArquivoCSV_Legacy(const char* path, vector<Review>& reviews)
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
                reviews[i].review_id = str.substr(0, pos);
                apagar_sub_str(str, reviews[i].review_id);
            }

            string novaLinha;
            peekline(arquivo, novaLinha);
            if (novaLinha.find("p:") != string::npos)
            {
                auto pos = str.find_last_of(',');
                if (pos != string::npos)
                {
                    reviews[i].posted_date = str.substr(pos);
                    apagar_sub_str(str, reviews[i].posted_date);
                    reviews[i].posted_date.erase(0, 1);
                }
                pos = str.find_last_of(',');
                if (pos != string::npos)
                {
                    reviews[i].app_version = str.substr(pos);
                    apagar_sub_str(str, reviews[i].app_version);
                    reviews[i].app_version.erase(0, 1);
                }
                pos = str.find_last_of(',');
                if (pos != string::npos)
                {
                    reviews[i].upvotes = str.substr(pos);
                    apagar_sub_str(str, reviews[i].upvotes);
                    reviews[i].upvotes.erase(0, 1);
                }
                reviews[i].review_text = move(str);
                reviews[i].review_text.erase(0, 1);

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