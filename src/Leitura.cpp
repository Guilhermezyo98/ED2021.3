#include "Leitura.h"

#include <sstream>

#include "Parametros_constantes.h"

void apagar_sub_str(std::string &main_str, const std::string &apagar)
{
    size_t pos;
    if (apagar == ",")
    {
        pos = main_str.find_last_of(apagar);
    } else
    {
        pos = main_str.find(apagar);
    }

    if (pos != std::string::npos)
    {
        main_str.erase(pos, apagar.length());
    }
}

void peekline(fstream &arquivo, string &str)
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

void trataUltimaLinha(const fstream &fstream, vector<Review> &reviews, string &str, long i)
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

void lerArquivoCSV(const char *path, vector<Review> &reviews)
{
    fstream arquivo;
    arquivo.open(path, ios::in);
    if (!arquivo.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto";
        assert(false);
    }
    constexpr size_t bufferSize = 543'022'558;
    unique_ptr<char[]> buffer(new char[bufferSize]);
    string token;

    arquivo.seekg(54, ios::beg); // pula primeira linha
    arquivo.read(buffer.get(), bufferSize);
    istringstream lines(buffer.get());

    arquivo.close();

    Review review;
    string linha;
    for (unsigned long i = 0; i < tam_linhas; ++i)
    {
        getline(lines, linha, ',');
        review.review_id = linha;
        
        if (lines.get() == '"')
        {
            review.review_text.clear();
            while (true)
            {
                getline(lines, linha, '"');
                review.review_text += linha;
                if (lines.get() != '"')
                {
                    break;
                }
            }
        } else
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

        reviews.push_back(review);
    }

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
void escreveBin(Review *reviews)
{
    fstream arqBin;
    arqBin.open(arquivo_path, ios::out | ios::binary | ios::app);
    //Abrir arquivo out: saída, binário, app:add no final
    if (!arqBin.good())
    {
        cerr << "ERRO: arquivo nao pode ser aberto";
        assert(false);
    }

    arqBin.write((char *) &reviews, sizeof(Review));

    //arqBin.flush(); //Encerrar inserção.
    arqBin.close(); //Fechar arquivo
}

void leBin(Review *reviews)
{
    fstream arqBin;
    arqBin.open(arquivo_path, ios::binary); //Abrir arquivo
    if (!arqBin.good())
    {
        cerr << "ERRO: arquivo nao pode ser aberto";
        assert(false);
    }
    arqBin.read(reinterpret_cast<char *>(&reviews), sizeof(Review));
    arqBin.close(); //Fechar arquivo
}

void imprimeReviewEspecifica(int n, vector<Review> &reviews)
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

vector<Review> *importarReviewsAleatorios(int qtd)
{
    // TODO: otimar para ler de maneira aleatoria a qtd necessaria do arquivo bin

    fstream arqBin;
    arqBin.open(arquivo_path, ios::binary); //Abrir arquivo
    if (!arqBin.good())
    {
        cerr << "ERRO: arquivo nao pode ser aberto";
        assert(false);
    }
    auto *aux = new vector<Review>;
    aux->resize(tam_linhas);

    auto *aleatorio = new vector<Review>;
    aleatorio->resize(qtd);

    string str;
    while (std::getline(arqBin, str))
    {
        arqBin.read(reinterpret_cast<char *>(&aux), sizeof(Review)); //ler arquivo e armazenar no vetor auxiliar
    }
    for (int i = 0; i < qtd; i++)
    {
        int numAleatorio = (rand() % tam_linhas); // Gerando numeros aleatorios
        aleatorio[i] = aux[numAleatorio];
        //vetor de reviews aleatorios recebe reviews das posições sorteadas
    }

    delete aux;
    arqBin.close(); //Fechar arquivo
    return aleatorio;
}
