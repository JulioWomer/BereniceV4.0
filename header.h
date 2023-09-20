#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

void Cadastrar();
void Atualizar();
void Excluir();
void Salvar();
void Ler();
void menuDeVendas();
void Realizarvenda();
float formapag_avista(float subtotal);
void CupomFiscal(float total, int indiceG2);

///Struct pra armazenar temporariamente os produtos! :)
typedef struct
{
    int Cod;
    char Nome[25];
    float Valor;
    int Estoque;
    int Vendas;
    float Subtotal;
    int QTDtotal;
} itens;

typedef struct
{
    int item;
    char nome[26];
    float valor_unita;
    int quant;
    float subtotal;
} cupom;

itens *p = NULL;
int indiceG = 0;

itens prod[]; // array para cadastrar novos itens na struct declarada acima
cupom cupom_fiscal[30];

#endif // HEADER_H_INCLUDED
