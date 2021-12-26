#include <stdio.h>
#include <iostream>~

#include "leitura.h"
#include "Timer.h"

using namespace std;

#ifndef NOB_H
#define NOB_H

// No da arvore b
class NoB
{
    public:
        elementoArvore *chaves;// Conjunto de chaves
        int t;      // Grau mínimo (define o intervalo para o número de chaves)
        NoB **F;    // Indicadores dos filhos
        int n;      // Número atual de chaves
        bool folha;  // E folha retorna true
        NoB(int _t, bool folha);   // Construtor
        void inserirChaves(elementoArvore *elemento);      //Funcao para inserir um no na arvore b
        void dividirFilho(int i, NoB *p);       //Funcao para dividir um no
        void imprimir();       //Funcao para percorrer todos os nos de uma subarvore
        NoB *procurar(string valor, int *comparacoes);   // Procurar uma chave na arvore

friend class ArvoreB;
};

#endif