#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include "Timer.h"

#include <cassert>
#include <sstream>

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

	auto duracao = fim - inicio;
	double ms = duracao * 0.001;

	std::cout << m_legenda << ": " << duracao << "us (" << ms << "ms)\n";
}

void Timer::benchHeapSort(int trials)
{
	fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary), inputFile("./input.dat", ios::in);
	if (!(arquivoBinario.is_open() || inputFile.is_open()))
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao benchHeapSort()";
		assert(false);
	}

	string linha;
	vector<Review> reviews;
	while (getline(inputFile, linha))
	{
		cout << "\t *** \t" << linha << "\t *** \n";
		for (int i = 0; i < trials; ++i)
		{
			int size = stoi(linha);
			inicializaVetor(reviews, size);
			ostringstream msg;
			msg << "HeapSort, trial " << i;
			{
				Timer cronometro(msg.str());
				heapSort(reviews, reviews.size(), this);
			}
			cout << "resumo: swaps = " << this->m_swaps << "\tcomparacoes = " << this->m_comparacoes << endl;

			cout << endl;
		}
		cout << "\nresumo algoritmo HeapSort para size = " << linha << endl;
		cout << "\tnumero de trials:" << trials << endl;
		cout << "\tnumero de comparacoes medias:" << m_comparacoes / trials << endl;
		cout << "\tnumero de trocas medias:" << m_swaps / trials << endl;
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
