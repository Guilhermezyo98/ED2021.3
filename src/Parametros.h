#ifndef PARAMETROS_H
#define PARAMETROS_H

const auto arquivo_path = "D:/Users/DANIEL/Downloads/Tiktok/tiktok_app_reviews.csv";
const auto saidaBinaria_path = "C:/Users/Daniel/Desktop/vs/src/saida.bin";
const auto saidaTexto_path = "C:/Users/Daniel/Desktop/vs/src/saidaTxt.txt";

const int reviews_totais = 3'646'475;

const int TAMANHO_MAX_ID = 90;
const int TAMANHO_MAX_TEXT = 100;
const int TAMANHO_MAX_UPVOTES = 4;
const int TAMANHO_MAX_APP_VERSION = 7;
const int TAMANHO_MAX_DATE = 20;
const int TAMANHO_MAX_STRUCT = TAMANHO_MAX_ID + TAMANHO_MAX_APP_VERSION + TAMANHO_MAX_DATE + TAMANHO_MAX_UPVOTES +
	TAMANHO_MAX_TEXT;

#endif // !PARAMETROS_H
