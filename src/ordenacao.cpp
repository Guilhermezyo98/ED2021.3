#include <vector>
#include "ordenacao.h"
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
