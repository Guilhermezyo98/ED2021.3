#ifndef TIMER_H
#define TIMER_H

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

#endif
