#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
using namespace std;
using namespace std::chrono;

class Timer
{
private:
	string m_legenda;
	time_point<high_resolution_clock> m_tempoInicio;
	int swaps;
	int comparacoes;

public:
	Timer(std::string legenda);
	~Timer();

	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

private:
	void Stop();
};

#endif
