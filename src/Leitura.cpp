#include "Leitura.h"
#include "Parametros_constantes.h"

#include <sstream>
#include <strstream>
#include <cstdlib> 
#include <ctime> 

streampos tamanhoArquivo(fstream& arq)
{
    arq.seekg(0, arq.end);
    streampos tam = arq.tellg();
    arq.seekg(0);
    return tam;
}

void lerArquivoCSV(const char* path, vector<Review>& reviews)
{
    fstream arquivo(path, ios::in);

    if (!arquivo.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto";
        assert(false);
    }
    auto bufferSize = tamanhoArquivo(arquivo);

    arquivo.seekg(54, ios::beg);    // pula primeira linha
    unique_ptr<char[]> buffer(new char[bufferSize]);

    arquivo.read(buffer.get(), bufferSize); // leitura para buffer
    istrstream lines(const_cast<char*>(buffer.get()), (int)bufferSize);
    arquivo.close();
    // // // // // //

    Review review;
    string linha;
    while(getline(lines, linha, ','))
    {
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

        reviews.push_back(review);
    }
}

void escreveBin(vector<Review>& reviews)
{
    fstream arqbin("C:/Users/Daniel/Desktop/vs/src/saida.bin", ios::out | ios::binary | ios::trunc);

    for (size_t i = 0; i < reviews.size(); i++)
    {
        arqbin.write(reinterpret_cast<char*>(&reviews[i]), sizeof(Review));
    }

}


void imprimeReviewEspecifica(int reviewN)
{
    fstream arqBin("C:/Users/Daniel/Desktop/vs/src/saida.bin", ios::in | ios::binary);
    if (!arqBin.is_open())
    {
        cerr << "erro";

    }

    auto pos = (reviewN - 1) * sizeof(Review);
    arqBin.seekg(pos);

    unique_ptr<char[]> buffer(new char[sizeof(Review)]);
    arqBin.read(buffer.get(), sizeof(Review)); // leitura para buffer*
    istrstream lines(const_cast<char*>(buffer.get()), sizeof(Review));

    Review review;
    review.review_id.resize(90);
    review.review_text.resize(4096);
    review.upvotes.resize(50);
    review.app_version.resize(20);
    review.posted_date.resize(20);

    while (lines.read(reinterpret_cast<char*>(&review), sizeof(Review)))
    {

    }
}



Review retornaReviewEspecifica(int reviewN)
{
    fstream arqBin("C:/Users/Daniel/Desktop/vs/src/saida.bin", ios::in | ios::binary);
    if (!arqBin.is_open())
    {
        cerr << "erro";

    }

    auto pos = (reviewN - 1) * sizeof(Review);
    arqBin.seekg(pos);

    unique_ptr<char[]> buffer(new char[sizeof(Review)]);
    arqBin.read(buffer.get(), sizeof(Review)); // leitura para buffer*
    istrstream lines(const_cast<char*>(buffer.get()), sizeof(Review));

    Review review;
    review.review_id.resize(90);
    review.review_text.resize(4096);
    review.upvotes.resize(50);
    review.app_version.resize(20);
    review.posted_date.resize(20);

    while (lines.read(reinterpret_cast<char*>(&review), sizeof(Review)))
    {
    }

    return review;
}

int getRandomNumber(int min, int max)
{
    static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

void imprimeReviewEspecifica(Review review)
{
    cout << "review_id: " << review.review_id << endl;
    cout << "review_text: " << review.review_text << endl;
    cout << "upvotes: " << review.upvotes << endl;
    cout << "app_version: " << review.app_version << endl;
    cout << "posted_date: " << review.posted_date << endl;
}

void escreveTexto(vector<Review> reviews)
{
    fstream arquivo("C:/Users/Daniel/Desktop/vs/src/saidaTxt.txt", ios::out | ios::in);

    for (size_t i = 0; i < reviews.size(); i++)
    {
        arquivo << reviews[i].review_id;
        arquivo << reviews[i].review_text;
        arquivo << reviews[i].upvotes;
        arquivo << reviews[i].app_version;
        arquivo << reviews[i].posted_date;
        arquivo << "\n";
    }
}

enum Saidas
{
    console = 1,
    arquivo = 2
};
// importa N registros aleatórios do arquivo binário.
// Para essa importação, a função deve perguntar ao usuário se ele deseja exibir a saída no console
 // ou salvá - la em um arquivo texto.

void testeImportacao()
{
    cout << "Digite a saida preferida para exportar N registros do arquivo binario:" << endl;
    cout << "Digite 1 para exporta 10 registros para o console," << endl;
    cout << "Digite 2 para exportar 100 registros para arquivo texto" << endl;
    int n = -1;
    cin >> n;

    switch (n)
    {
    case console:
    {
        for (size_t i = 0; i < 10; i++)
        {
            Review review = retornaReviewEspecifica(getRandomNumber(0, reviews_totais));
            imprimeReviewEspecifica(review);
        }
			break;
    }
    case arquivo:
    {
        vector<Review> reviews;
        for (size_t i = 0; i < 100; i++)
        {
            reviews.push_back(retornaReviewEspecifica(getRandomNumber(0, reviews_totais)));
        }
        escreveTexto(reviews);
        break;
    }
    default:
	    {
		    
        break;
	    }
    }
}
