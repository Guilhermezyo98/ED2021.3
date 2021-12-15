#ifndef ORDENACAO_H
#define ORDENACAO_H
#include "leitura.h"
#include "Timer.h"

// HeapSort
void heapSort(std::vector<Review>& reviews, int n, Timer* timer);
void heapify(vector<Review>& reviews, int n, int i, Timer* timer);

int quickAux(vector<Review>& v, int inicio, int final, Timer* desempenho);
void quickSort(vector<Review>& v, int inicio, int fim, Timer* desempenho);

#endif // !ORDENACAO_H
