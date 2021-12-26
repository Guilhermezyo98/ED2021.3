#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include "leitura.h"
#include "leitura.h"
#include "Timer.h"

using namespace std;

class ArvoreB
{
    NoB *raiz;  // Raiz
    int t;      // Grau minimo

public:
    // Construtor
    ArvoreB(int elemento){
        raiz = NULL;
        t = elemento;
        
    }


    // Funcao para imprimir a arvore
    void imprimir(){
        if (raiz != NULL)
            raiz->imprimir();
        cout<<endl;
    }


    // Funcao para procurar um no na arvore
    NoB* procurar(string k,int *comparacoes){
        return (raiz == NULL)? NULL : raiz->procurar(k,comparacoes);
    }


    // Funcao principal para inserir uma nova chave na arvore
    void inserir(elementoArvore *valor){
      // Arvore vazia
      if (raiz == NULL)
      {
          //Alocando memoria para raiz
          raiz = new NoB(t, true);
          raiz->chaves[0] = *valor;  // Inserir chave
          raiz->n = 1;  // Atualizar numero de chaves
          
      }
      else // Nao esta vazia
      {
          // Raiz cheia ,arvore cresce em altura
          if (raiz->n == 2*t-1)
          {
              //Alocar memória para nova raiz;
              NoB *p = new NoB(t, false);

              // Raiz velha e filha da nova raiz
              p->F[0] = raiz;

              // Dividir a raiz
              p->dividirFilho(0, raiz);

              // Raiz tem dois filhos,decidir onde vai ser inserido
              int i = 0;
              if (p->chaves[0].posicaoBinario->name < valor->posicaoBinario->name)
                i++;
              p->F[i]->inserirChaves(valor);

              // Mudar raiz
              raiz = p;
          }
          else{  // Raiz nao esta cheia
              raiz->inserirChaves(valor);
          }
      }
    }
};

#endif
