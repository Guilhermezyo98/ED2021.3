#pragma once
#include <memory>
#include <chrono>

class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_tempoInicio;

public:
	Timer();
	~Timer();

private:
	void Stop();
};
