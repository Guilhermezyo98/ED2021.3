#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

#include "leitura.h"
using namespace std;
using namespace std::chrono;

class Timer
{
private:
	string m_legenda;
	time_point<high_resolution_clock> m_tempoInicio;
	int m_swaps;
	int m_comparacoes;

public:
	Timer(string legenda);
	~Timer();

	void acrecentaSwaps();
	void acrecentaComparacoes();
	void benchHeapSort(int trials);

	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

private:
	void Stop();
	void inicializaVetor(vector<Review>& reviews, int size);
	void zeraMedicoes();

};

#endif
