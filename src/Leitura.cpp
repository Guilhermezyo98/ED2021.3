#include "Leitura.h"
#include "Parametros_constantes.h"

#include <strstream>


void lerArquivoCSV(string caminho,string caminhoSaida)
{
    fstream arquivo;
    fstream arquivoSaida;
	arquivoSaida.open(caminhoSaida, ios::out | ios::binary | ios::trunc);
	arquivoSaida.close();
	fstream arqBin;
	arqBin.open(caminhoSaida, ios::out | ios::binary | ios::app);
    arquivo.open(caminho, ios::in);
    if (!arquivo.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto";
        assert(false);
    }
    constexpr size_t bufferSize = 543'022'558;

    arquivo.seekg(54, ios::beg); // pula primeira linha
	unique_ptr<char[]> buffer(new char[bufferSize]);

    arquivo.read(buffer.get(), bufferSize);
    istrstream lines(const_cast<char*>(buffer.get()), bufferSize);

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

        //////////// escrita/////////////////
        //reviews.push_back(review);
        escreveBin(&review ,&arqBin);
        ////////////////////////////
    }
    arqBin.close();
}

void escreveBin(Review* review,fstream *arqBin)
{

	//Abrir arquivo out: sa�da, bin�rio, app:add no final
	if (!arqBin->is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto";
		assert(false);
	}

	arqBin->write((char*)&review, sizeof(Review));

	//arqBin.flush(); //Encerrar inser��o.
	 //Fechar arquivo
}

void leBin(string caminho)
{
    fstream arqBin;
    arqBin.open(caminho, ios::binary); //Abrir arquivo
    if (!arqBin.good())
    {
        cerr << "ERRO: arquivo nao pode ser aberto";
        assert(false);
    }
    // arqBin.read(reinterpret_cast<char *>(&reviews), sizeof(Review));
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
        //vetor de reviews aleatorios recebe reviews das posi��es sorteadas
    }

    delete aux;
    arqBin.close(); //Fechar arquivo
    return aleatorio;
}
