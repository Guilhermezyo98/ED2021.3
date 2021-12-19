#include <vector>
#include <algorithm>
#include "ordenacao.h"

#include <iostream>

#include "leitura.h"
#include "Timer.h"

void heapSort(std::vector<Review>& reviews, int n, Timer* timer)
{
	for (int i = n - 1; i >= 0; i--)
	{
		heapify(reviews, n, i, timer);
	}

	for (int i = n - 1; i >= 0; i--)
	{
		swap(reviews[0], reviews[i]);
		timer->acrecentaSwaps();
		heapify(reviews, i, 0, timer);
	}
}

void heapify(vector<Review>& reviews, int n, int i, Timer* timer)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	timer->acrecentaComparacoes();
	if (l < n && reviews[l].upvotes > reviews[largest].upvotes)
	{
		largest = l;
	}
	timer->acrecentaComparacoes();
	if (r < n && reviews[r].upvotes > reviews[largest].upvotes)
	{
		largest = r;
	}
	timer->acrecentaComparacoes();
	if (largest != i)
	{
		swap(reviews[i], reviews[largest]);
		timer->acrecentaSwaps();
		heapify(reviews, n, largest, timer);
	}
}

void InsertionSort(vector<Review>& vet, size_t lo, size_t hi, Timer* timer)
{
	size_t i = lo + 1;
	size_t j;
	Review t;
	while (i <= hi)
	{
		t = vet[i];
		j = i;
		timer->acrecentaComparacoes();
		while ((j > lo) && vet[j - 1].upvotes > t.upvotes)
		{
			timer->acrecentaComparacoes();
			timer->acrecentaSwaps();
			vet[j] = vet[j - 1];
			j--;
		}
		timer->acrecentaSwaps();
		vet[j] = t;
		i++;
	}
}

void QuickSort(vector<Review>& vet, size_t lo, size_t hi, Timer* timer)
{
	timer->acrecentaComparacoes();
	if (lo >= hi)
		return;
	timer->acrecentaComparacoes();
	if ((hi - lo) < 100)
	{
		InsertionSort(vet, lo, hi, timer);
		return;
	}
	int pivot = vet[lo + (hi - lo) / 2].upvotes;
	Review t;
	size_t i = lo - 1;
	size_t j = hi + 1;
	while (1)
	{
		timer->acrecentaComparacoes();
		while (vet[++i].upvotes < pivot);
		timer->acrecentaComparacoes();
		while (vet[--j].upvotes > pivot);
		timer->acrecentaComparacoes();
		if (i >= j)
			break;
		timer->acrecentaSwaps();
		t = vet[i];
		vet[i] = vet[j];
		vet[j] = t;
	}
	QuickSort(vet, lo, j, timer);
	QuickSort(vet, j + 1, hi, timer);
}

void quickSortHash(vector<pair<string, int>>& vetor, int inicio, int fim)
{
	if (inicio < fim)
	{
		int pivo = quickSortHashAux(vetor, inicio, fim);
		quickSortHash(vetor, inicio, pivo - 1);
		quickSortHash(vetor, pivo + 1, fim);
	}
}

int quickSortHashAux(vector<pair<string, int>>& vet, int inicio, int final)
{
	int pivo = vet[final].second;
	int i = (inicio - 1);

	for (int j = inicio; j <= final - 1; j++)
	{
		if (vet[j].second >= pivo)
		{
			i++;
			swap(vet[i], vet[j]);
		}
	}
	swap(vet[i + 1], vet[final]);
	return (i + 1);
}

int nextGap(int gap)
{
	gap = int(gap / 1.3);

	if (gap < 1)
	{
		return 1;
	}

	return gap;
}

void combSort(std::vector<Review>& reviews, int n, Timer* timer)
{
	int gap = n;

	while (gap != 1)
	{
		gap = nextGap(gap);

		for (int i = 0; i < n - gap; i++)
		{
			timer->acrecentaComparacoes();
			if (reviews[i].upvotes > reviews[i + gap].upvotes)
			{
				swap(reviews[i], reviews[i + gap]);
				timer->acrecentaSwaps();
			}
		}
	}
}
