#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include <cassert>
#include <sstream>

#include "Timer.h"
#include "leitura.h"
#include "ordenacao.h"
#include "parametros.h"

Timer::Timer(std::string legenda)
	: m_legenda(move(legenda)), m_tempoInicio(std::chrono::high_resolution_clock::now()), m_swaps(0), m_comparacoes(0)
{
}

Timer::~Timer()
{
	Stop();
}

void Timer::Stop()
{
	auto fimTempo = std::chrono::high_resolution_clock::now();

	auto inicio = std::chrono::time_point_cast<std::chrono::microseconds>(m_tempoInicio).time_since_epoch().count();
	auto fim = std::chrono::time_point_cast<std::chrono::microseconds>(fimTempo).time_since_epoch().count();

	m_duracao = fim - inicio;
	double ms = m_duracao * 0.001;
	std::cout << m_legenda << ": " << m_duracao << "us (" << ms << "ms)\n";
}

void Timer::benchHeapSort(int trials)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary), inputFile("./input.dat", ios::in), saidaTxt
		        ("./saida.txt", ios::trunc | ios::out);
	if (!(arquivoBinario.is_open() || inputFile.is_open() || saidaTxt.is_open()))
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
		assert(false);
	}
	int montanteSwaps = 0, montanteComparacoes = 0;
	string linha;
	vector<Review> reviews;
	while (getline(inputFile, linha))
	{
		saidaTxt << "\t *** \t" << linha << "\t *** \n";
		for (int i = 0; i < trials; ++i)
		{
			int size = atoi(linha.c_str());
			inicializaVetor(reviews, size);
			ostringstream msg;
			msg << "HeapSort, trial " << i;
			{
				Timer cronometro(msg.str());
				heapSort(reviews, reviews.size(), this);
				cronometro.Stop();
				saidaTxt << "\tTEMPO: "<<  cronometro.m_legenda << ": " << cronometro.m_duracao << "us (" << cronometro.m_duracao * 0.001 << "ms)\n";
			}
			montanteComparacoes += this->m_comparacoes;
			montanteSwaps += this->m_swaps;
			saidaTxt << "pequeno resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes << endl;
			zeraMedicoes();
		}
		saidaTxt << "\nresumo algoritmo HeapSort para size = " << linha << endl;
		saidaTxt << "\tnumero de trials:" << trials << endl;
		saidaTxt << "\tnumero de comparacoes medias:" << montanteComparacoes / trials << endl;
		saidaTxt << "\tnumero de trocas medias:" << montanteSwaps / trials << endl;
		saidaTxt << endl << endl << endl;
		zeraMedicoes();
	}
}

void Timer::benchQuickSort(int trials)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary), inputFile("./input.dat", ios::in);
	if (!(arquivoBinario.is_open() || inputFile.is_open()))
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
		assert(false);
	}

	string linha;
	vector<Review> reviews;
	unsigned int aux=0,aux2=0;
	while (getline(inputFile, linha))
	{
		cout << "\t *** \t" << linha << "\t *** \n";
		for (int i = 0; i < trials; ++i)
		{
			int size = stoi(linha);
			inicializaVetor(reviews, size);
			ostringstream msg;
			msg << "QuickSort, trial " << i;
			{
				Timer cronometro(msg.str());
				quickSort(reviews,0,reviews.size()-1, this);
			}
			cout << "resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes << endl;
			aux+=this->m_swaps;
			aux2+=this->m_comparacoes;
			cout << endl;
			this->zeraMedicoes();
		}
		cout << "\nresumo algoritmo QuickSort para size = " << linha << endl;
		cout << "\tnumero de trials:" << trials << endl;
		cout << "\tnumero de comparacoes medias:" << aux2 / trials << endl;
		cout << "\tnumero de trocas medias:" << aux / trials << endl;
		cout << endl;
		zeraMedicoes();
	}
}

void Timer::inicializaVetor(vector<Review>& reviews, int size)
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

void Timer::acrecentaSwaps()
{
	++m_swaps;
}

void Timer::acrecentaComparacoes()
{
	++m_comparacoes;
}

void Timer::zeraMedicoes()
{
	m_comparacoes = 0;
	m_swaps = 0;
}
