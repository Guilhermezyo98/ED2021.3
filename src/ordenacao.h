#ifndef ORDENACAO_H
#define ORDENACAO_H
#include "leitura.h"
#include "Timer.h"

// HeapSort
void heapSort(std::vector<Review>& reviews, int n, Timer* timer);
void heapify(vector<Review>& reviews, int n, int i, Timer* timer);

void InsertionSort(vector<Review> &vet, size_t lo, size_t hi,  Timer* timer);
void QuickSort(vector<Review> &vet, size_t lo, size_t hi,  Timer* timer);

void combSort(std::vector<Review>& reviews, int n, Timer* timer);
int nextGap(int gap);

void quickSortHash(vector<pair<string, int>>& vetor, int inicio, int fim);
int quickSortHashAux(vector<pair<string, int>>& vet, int inicio, int final);

#endif // !ORDENACAO_H
