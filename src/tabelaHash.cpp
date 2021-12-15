#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include "tabelaHash.h"
#include "parametros.h"
#include <fstream>
#include <cassert>
using namespace std;
void quickSortHash(auxRep *v,int inicio,int fim);
int quickSortHashAux(auxRep *v,int inicio,int final);
void desempenhoHash(int n,int parametro,int caminho);

tabelaHash::tabelaHash(int tam)
{
    this->tamanho=tam;
    this->vet = new string[tam];
    atualizaM(tam);
    this->colisoes=0;
    this->repeticao = new auxRep[tam];
    zera();
    zeraRepeticao();
}
tabelaHash::~tabelaHash()
{
    delete []vet;
}
int tabelaHash::funcaoHash(string x,int i)
{
    long int chave = StringToInt(x);
    chave = chave * floor(sqrt(chave));
    return ((((chave%m)%tamanho)*(i*(((chave%m)%tamanho))))%tamanho);
}
bool tabelaHash::ePrimo(int x)
{
    int aux,div=0;
    for(aux=2 ; aux<=sqrt(x) ; aux++)
        if(x%aux==0)
            div++;
    if(div==0)
        return true;
    else
        return false;
}
void tabelaHash::zera()
{
    for(int i=0; i<tamanho; i++)
    {
        vet[i]="0";
    }
}
void tabelaHash::zeraRepeticao(){
    for(int i=0;i<tamanho;i++){
        repeticao[i].frequencia=0;
        repeticao[i].indice=i;
    }
}
auxRep* tabelaHash::repeticoes(){
    return this->repeticao;
}
int tabelaHash::maiorPrimo(int x)
{
    int parada=0;
    x = x / 2; // MAGICA
    for(int i=0; parada==0; i++,x++)
    {
        if(ePrimo(x))
            return x;
    }
}
void tabelaHash::atualizaM(int tam)
{
    m = maiorPrimo(tam);
}

bool tabelaHash::adicionaAux(int ind,string info)
{
    string comp;
    comp+='0';
    if(vet[ind] == comp || vet[ind] == info){
        vet[ind] = info;
        repeticao[ind].frequencia = repeticao[ind].frequencia + 1;
        repeticao[ind].indice = ind;
        return true;
    }
    else
    {
        return false;
    }
}
void tabelaHash::txtFrequentes(int numImpressao,auxRep *rep, int tamTabela){
    cout<<endl;
    int j = 0;
    ofstream arquivotxt("saixaTabelaHash.txt",ios::app);
    arquivotxt << "******************************************************** "  << endl;
    arquivotxt << "*********************  Tabela Hash  ********************" << endl;
    arquivotxt << "******************************************************** " <<  endl;
    for(int i = tamTabela;i >= numImpressao;i-- ){
        arquivotxt << j + 1 <<": "<<vet[rep[i].indice]  << "  Número de repetições: " << rep[i].frequencia <<endl;
        j++;
        if(j == numImpressao)
            break;
    }
    
    arquivotxt.close();
}
void tabelaHash::txtFrequentesTeste(int numImpressao,auxRep *rep, int tamTabela){
    cout<<endl;
    int j = 0;
    ofstream arquivotxt("teste.txt",ios::app);
    arquivotxt << "******************************************************** "  << endl;
    arquivotxt << "*********************  Tabela Hash  ********************" << endl;
    arquivotxt << "******************************************************** " <<  endl;
    for(int i = tamTabela;i >= numImpressao;i-- ){
        arquivotxt << j + 1 <<": "<<vet[rep[i].indice]  << "  Número de repetições: " << rep[i].frequencia <<endl;
        j++;
        if(j == numImpressao)
            break;
    }
    
    arquivotxt.close();
}
void tabelaHash::adiciona(string chave)
{
    int controle=0;
    
    for(int i=0; i<tamanho && controle==0; i++)
    {
        if(adicionaAux(funcaoHash(chave,i),chave))
            controle=1;
    }
    if(controle == 0)
    {
        colisoes++;
    }
}
bool tabelaHash::verificaChave(string chave)
{
    for(int i=0; i<tamanho; i++)
    {
        if(vet[funcaoHash(chave,i)]==chave)
        {
            return true;
        }
    }
    return false;
}
int tabelaHash::index(string chave)
{
    if(verificaChave(chave))
    {
        for(int i=0; i<tamanho; i++)
        {
            if(vet[funcaoHash(chave,i)]==chave)
            {
                return funcaoHash(chave,i);
            }
        }
    }
    else{
        return -1;
    }
}
string tabelaHash::get(int index){
    return this->vet[index];
}
long int tabelaHash::StringToInt(string x){
    long int soma=1;
    for(int i=0;i<x.size();i++){
        soma=(soma*toascii(x[i])*pow(3,i));
    }
    return soma;
}


void quickSortHash(auxRep *v,int inicio,int fim){
    int pivo;
    if(fim > inicio){
        pivo = quickSortHashAux(v,inicio,fim);
        quickSortHash(v,inicio,pivo - 1);
        quickSortHash(v,pivo + 1,fim);

    }
}

int quickSortHashAux(auxRep *v,int inicio,int final){
    int esq,dir;
    auxRep pivo;
    auxRep aux;
    esq = inicio;
    dir = final;
    pivo = v[inicio];
    while(esq < dir){
        while(esq <= final && v[esq].frequencia <= pivo.frequencia){
            esq++;
        }
        while(dir >= 0 && v[dir].frequencia > pivo.frequencia){
            dir--;
        }
        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
        }

    }
    v[inicio] = v[dir];
    v[dir] = pivo;
    return dir;
    
}


void desempenhoHash(int n,int parametro,int caminho,int quantidade){
    int tamTabela = n * 1.5;

    tabelaHash tabela(tamTabela);
    fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
	if (!arquivoBinario.is_open())
	{
		cerr << "ERRO: arquivo nao pode ser aberto na funcao inicializaVetor()";
		assert(false);
	}
    vector<Review> vReview;
    for (int j = 0; j < quantidade; j++)
	{
		vReview.resize(quantidade);
		vReview[j] = retornaReviewEspecifica(retonaNumeroAleatorio(0, reviews_totais), arquivoBinario);
	}
    for(int i = 0;i < n;i++){
        tabela.adiciona(vReview[i].app_version);
    }
    
    auxRep *vet = new auxRep[tamTabela];
    vet = tabela.repeticoes();
    
    cout <<endl;

    quickSortHash(vet,0,tamTabela-1);

    if (caminho == 0){
        tabela.txtFrequentes(parametro,vet,tamTabela-1);   
    }
    else {
        tabela.txtFrequentesTeste(parametro,vet,tamTabela-1);
        }
}








