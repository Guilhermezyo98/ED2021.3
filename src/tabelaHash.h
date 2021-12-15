#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
//
#include "leitura.h"

using namespace std;


#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED
struct auxRep{
    int frequencia;
    int indice;
};
class tabelaHash{    
private:
    string *vet; 
    int tamanho;
    int m;
    int maiorPrimo(int x);
    void atualizaM(int tam);
    bool ePrimo(int x);
    int funcaoHash(string chave,int i);
    bool adicionaAux(int ind,string info);
    long int StringToInt(string x);
    auxRep *repeticao;
    void zera();
    void zeraRepeticao();

public:
            
    tabelaHash(int tam);
    ~tabelaHash();
    int colisoes;
    string get(int index);
    void adiciona(string x);
    bool verificaChave(string x);
    int index(string);
    auxRep *repeticoes();
    void txtFrequentes(int m,auxRep *rep,int tamTabela);
    void txtFrequentesTeste(int m,auxRep *rep,int tamTabela);
   
    

};

#endif 