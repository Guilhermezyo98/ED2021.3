#include "Leitura.h"
#include "Parametros_constantes.h"

#include <sstream>
#include <strstream>
#include <cstdlib> 

streampos tamanhoArquivo(fstream& arq)
{
    arq.seekg(0, arq.end);
    streampos tam = arq.tellg();
    arq.seekg(0);
    return tam;
}

void lerArquivoCSV(string path, vector<Review>& reviews)
{
	if (reviews.size() == reviews_totais)
	{
        cerr << "\n\n\t\tacredito que voce tenha selecionado para ler arquivo csv 2x, cuidado!\n\n";
        return;
	}
    reviews.reserve(reviews_totais);

    fstream arquivo(path, ios::in);

    if (!arquivo.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto \n\t lerArquivoCSV";
        assert(false);
    }
    auto bufferSize = tamanhoArquivo(arquivo);

    arquivo.seekg(54, ios::beg);
    unique_ptr<char[]> buffer(new char[bufferSize]);
    arquivo.read(buffer.get(), bufferSize);
    // strinstrem exige duplicacao da memoria,
    // strstream nao, eh depreciado, mas possui construtor por referencia que evita uma nova alocacao = perde de desempenho
    istrstream lines(const_cast<char*>(buffer.get()), (int)bufferSize);

    arquivo.close();
    // // // // // //

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
                if (lines.get() != '"')     // linhas ondem o segundo parentese nao representa o fim da linha vao continuar o loop
                {                              // caso o contrario, o while infinito se quebra
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

        // Para garantir que todas reviews tenham o mesmo tamanho no final
        review.review_id.resize(TAMANHO_MAX_ID);
        review.review_text.resize(TAMANHO_MAX_TEXT);
        review.app_version.resize(TAMANHO_MAX_APP_VERSION);
        review.upvotes.resize(TAMANHO_MAX_UPVOTES);
        review.posted_date.resize(TAMANHO_MAX_DATE);

        reviews.push_back(review); // foi experimentado escrever no binario apos ler uma review, mas a chamada de funcao atrasa demais o processo
									// apesar de economizar muita memoria, fica lento demais para valer a pena deixar
    }
}

void escreveBin(string caminhoSaida, vector<Review>& reviews)
{
    if (reviews.size() == 0)
    {
        cerr << "\n\n\t\tvoce deveria ler o arquivo antes de tentar escrever, cuidado!\n\n";
        return;
    }

   fstream arqBin(caminhoSaida, ios::binary | ios::trunc | ios::in | ios::out);
    if (!arqBin.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto \n\t escreveBin() \n\t provavelmente nao foi possivel criar o arquivo, peco que crie manualmente se for o caso\n";
        assert(false);
    }

    for (size_t i = 0; i < reviews.size(); i++)
    {
        arqBin.write(reinterpret_cast<const char*>(reviews[i].review_id.c_str()), TAMANHO_MAX_ID);
        arqBin.write(reinterpret_cast<const char*>(reviews[i].review_text.c_str()), TAMANHO_MAX_TEXT);
        arqBin.write(reinterpret_cast<const char*>(reviews[i].upvotes.c_str()), TAMANHO_MAX_UPVOTES);
        arqBin.write(reinterpret_cast<const char*>(reviews[i].app_version.c_str()), TAMANHO_MAX_APP_VERSION);
        arqBin.write(reinterpret_cast<const char*>(reviews[i].posted_date.c_str()), TAMANHO_MAX_DATE);
    }
}

void imprimeReviewEspecifica(int reviewN, string caminhoBinario)
{
	if (reviewN < 0 || reviewN > reviews_totais)
	{
        cerr << "\n\t\tValor fora do intervalo" << endl;
        return;
	}

    ifstream arquivoBinario(caminhoBinario, ios::in | ios::binary);
    if (!arquivoBinario.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto \n\t imprimeReviewEspecifica() \n\t provavelmente nao foi possivel criar o arquivo, peco que crie manualmente se for o caso\n";
        assert(false);
    }

    auto pos = (reviewN)*TAMANHO_MAX_STRUCT;
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

    cout << "review_id: " << review.review_id << endl;
    cout << "review_text: " << review.review_text << endl;
    cout << "upvotes: " << review.upvotes << endl;
    cout << "app_version: " << review.app_version << endl;
    cout << "posted_date: " << review.posted_date << endl;
}

void imprimeReviewEspecifica(int reviewN, fstream arquivoBinario)
{
    if (!arquivoBinario.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto \n\t imprimeReviewEspecifica()\n  \n\t provavelmente nao foi possivel criar o arquivo, peco que crie manualmente se for o caso\n";
        assert(false);
    }

    auto pos = (reviewN)*TAMANHO_MAX_STRUCT;
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

    cout << "review_id: " << review.review_id << endl;
    cout << "review_text: " << review.review_text << endl;
    cout << "upvotes: " << review.upvotes << endl;
    cout << "app_version: " << review.app_version << endl;
    cout << "posted_date: " << review.posted_date << endl;

}

void imprimeReviewEspecifica(Review review)
{
    cout << "review_id: " << review.review_id << endl;
    cout << "review_text: " << review.review_text << endl;
    cout << "upvotes: " << review.upvotes << endl;
    cout << "app_version: " << review.app_version << endl;
    cout << "posted_date: " << review.posted_date << endl;
}

Review retornaReviewEspecifica(int reviewN, fstream& arquivoBinario)
{
    if (!arquivoBinario.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto \n\t retornaReviewEspecifica()  \n\t provavelmente nao foi possivel criar o arquivo, peco que crie manualmente se for o caso\n";
        assert(false);
    }
    auto pos = (reviewN)*TAMANHO_MAX_STRUCT;
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
    static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}


void escreveTexto(fstream& arquivoTexto, vector<Review>& reviews)
{
	if (!arquivoTexto.is_open())
	{
        cerr << "ERRO: arquivo nao pode ser aberto \n\t escreveTexto()  \n\t provavelmente nao foi possivel criar o arquivo, peco que crie manualmente se for o caso\n";
        assert(false);
	}

    for (size_t i = 0; i < reviews.size(); i++)
    {
        arquivoTexto << reviews[i].review_id;
        arquivoTexto << reviews[i].review_text;
        arquivoTexto << reviews[i].upvotes;
        arquivoTexto << reviews[i].app_version;
        arquivoTexto << reviews[i].posted_date;
        arquivoTexto << "\n";
    }
}

enum Saidas
{
    console10 = 1,
    consoleN = 2,
    arquivo100 = 3,
    arquivoN = 4,
    sair = 5
};
// importa N registros aleatórios do arquivo binário.
// Para essa importação, a função deve perguntar ao usuário se ele deseja exibir a saída no console
 // ou salvá - la em um arquivo texto.

void testeImportacao(string caminhoEntrada, string caminhoBinario, string caminhoTexto)
{
    cout << "\t\tDigite a saida preferida para exportar N registros do arquivo binario:" << endl;
    cout << "\t\tDigite 1 para exporta 10 registros para o console," << endl;
    cout << "\t\tDigite 2 para exporta N registros para o console," << endl;
    cout << "\t\tDigite 3 para exportar 100 registros para arquivo texto" << endl;
    cout << "\t\tDigite 4 para exportar N registros para arquivo texto" << endl;
    cout << "\t\tDigite 5 para sair " << endl;

    int n = -1;
    cin >> n;
    // srand(static_cast<unsigned int>(std::time(nullptr)));
    switch (n)
    {
    case console10:
    {
        fstream arquivoBinario(caminhoBinario, ios::in | ios::binary);
        for (size_t i = 0; i < 10; i++)
        {
            imprimeReviewEspecifica(retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario));
        }
        break;
    }
    case consoleN:
    {
        cout << "\n Digite o valor para N";
        int N = -1;
        cin >> N;
        fstream arquivoBinario(caminhoBinario, ios::in | ios::binary);
        for (size_t i = 0; i < N; i++)
        {
            imprimeReviewEspecifica(retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario));
        }
        break;
    }
    case arquivo100:
    {
        vector<Review> reviews;
        fstream arquivoBinario(caminhoBinario, ios::in | ios::binary);
        fstream arquivoTexto(caminhoTexto, ios::in | ios::trunc | ios::out);

        for (size_t i = 0; i < 100; i++)
        {
            reviews.push_back(retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario));
        }
        escreveTexto(arquivoTexto, reviews);
        cout << "\n\n------------------------------------------";
        cout << "\n\n------------------------------------------";
        cout << "\n\n-------------Exportacao finalizada!-------";
        cout << "\n\n------------------------------------------";
        cout << "\n\n------------------------------------------\n\n";
        break;
    }
    case arquivoN:
    {
        cout << "\n Digite o valor para N";
        int N = -1;
        cin >> N;
        vector<Review> reviews;
        fstream arquivoBinario(caminhoBinario, ios::in | ios::binary);
        fstream arquivoTexto(caminhoTexto, ios::in | ios:: trunc | ios::out);
        for (size_t i = 0; i < N; i++)
        {
            if (i == 348)
            {
                cout << " ";
            }
            reviews[i] = (retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario));
        }
        escreveTexto(arquivoTexto, reviews);
        cout << "\n\n------------------------------------------";
        cout << "\n\n------------------------------------------";
        cout << "\n\n-------------Exportacao finalizada!-------";
        cout << "\n\n------------------------------------------";
        cout << "\n\n------------------------------------------\n\n";
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