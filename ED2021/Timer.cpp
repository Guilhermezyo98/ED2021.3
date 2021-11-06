#include "Timer.h"

#include <iostream>

Timer::Timer()
{
	m_tempoInicio = std::chrono::high_resolution_clock::now();
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

	std::cout << duracao << "us (" << ms << "ms)\n";
}
