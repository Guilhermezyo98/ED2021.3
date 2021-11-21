#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer
{
private:
    std::string m_legenda;
    std::chrono::time_point <std::chrono::high_resolution_clock> m_tempoInicio;

public:
    Timer(std::string legenda);
    ~Timer();
    Timer(const Timer&) = delete;
    Timer& operator= (const Timer&) = delete;

private:
    void Stop();
};

#endif
