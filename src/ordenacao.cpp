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


//////////quick///////
void quickSort(vector<Review>& v,int inicio,int fim,desempenho *desempenho){
    int pivo;

    if(inicio < fim){
        pivo = quickAux(v,inicio,fim,desempenho);
        quickSort(v,inicio,pivo-1,desempenho);
        quickSort(v,pivo+1,fim,desempenho);
    }

}
int quickAux(vector<Review>& v,int inicio ,int final,desempenho *desempenho){
    Review aux;                                // review auxiliar
    int esq = inicio;                           // Inteiro que mostra onde inicia o vetor
    int dir = final;                            // Final que guarda a ultima posição do vetor

    Review pivo = v[inicio];           // Pivo a chave que sera comparada

    while(esq < dir){
        while(esq <= dir && v[esq].upvotes <= pivo.upvotes){
            esq ++;
            desempenho->numComparacoes = desempenho->numComparacoes + 1;
        }

        desempenho->numComparacoes = desempenho->numComparacoes + 1;

        while(dir >= 0 && v[dir].upvotes > pivo.upvotes){
            desempenho->numComparacoes = desempenho->numComparacoes + 1;
            dir --;
        }
        desempenho->numComparacoes = desempenho->numComparacoes + 1;
        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
            desempenho->numTrocas = desempenho->numTrocas + 1;
        }
    }
    v[inicio] = v[dir];
    v[dir] = pivo;
    desempenho->numTrocas = desempenho->numTrocas + 1;
    return dir;
}