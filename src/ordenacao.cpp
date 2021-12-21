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

void InsertionSort(vector<Review>& vet, size_t inicio, size_t fim, Timer* timer)
{
	for (int i = inicio + 1; i < fim + 1; i++)
	{
		Review val = vet[i];
		int j = i;
		while (j > inicio && vet[j - 1].upvotes > val.upvotes)
		{
			vet[j] = vet[j - 1];
			j -= 1;
		}
		vet[j] = val;
	}
}

int partition(vector<Review>& vet, size_t inicio, size_t fim, Timer* timer)
{
  int pivot = vet[fim].upvotes ;
  int i ,j;
  i = inicio;
  j = inicio;
 
  for (int i = inicio; i < fim; i++)
     {
      if(vet[i].upvotes <pivot)
      {
        Review temp = vet[i];
      vet[i] = vet[j];
      vet[j] = temp;
      j += 1;
      }
    }
   
    Review temp = vet[j];
    vet[j] = vet[fim];
    vet[fim] = temp;
 
  return j;
}

void quickSort(vector<Review>& vet, size_t inicio, size_t fim, Timer* timer)
{
	while (inicio < fim)
	{
		if (fim - inicio + 1 < 10)
		{
			InsertionSort(vet, inicio, fim, timer);
			break;
		}

		else

		{
			int pivot = partition(vet, inicio, fim, timer);

			if (pivot - inicio < fim - pivot)
			{
				quickSort(vet, inicio, pivot - 1, timer);
				inicio = pivot + 1;
			}
			else
			{
				quickSort(vet, pivot + 1, fim, timer);
				fim = pivot - 1;
			}
		}
	}
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

int quickSortHashAux(vector<pair<string, int>>& vet, int inicio, int fim)
{
	int pivo = vet[fim].second;

	int i = (inicio - 1);

	for (int j = inicio; j <= fim - 1; j++)
	{
		if (vet[j].second >= pivo)
		{
			i++;
			swap(vet[i], vet[j]);
		}
	}
	swap(vet[i + 1], vet[fim]);
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
