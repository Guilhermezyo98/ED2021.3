#ifndef PARAMETROS_H
#define PARAMETROS_H

const auto arquivo_path = "t.csv";

const int reviews_totais = 3'646'475;

const int TAMANHO_MAX_ID = 90;
const int TAMANHO_MAX_TEXT = 100;
const int TAMANHO_MAX_UPVOTES = 4;
const int TAMANHO_MAX_APP_VERSION = 8;
const int TAMANHO_MAX_DATE = 21;
const int TAMANHO_MAX_STRUCT = TAMANHO_MAX_ID + TAMANHO_MAX_APP_VERSION + TAMANHO_MAX_DATE + TAMANHO_MAX_UPVOTES +
	TAMANHO_MAX_TEXT;

#endif // !PARAMETROS_H
