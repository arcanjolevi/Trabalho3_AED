/*
############################################################################
############################################################################
## REGISTRO DESTE ARQUIVO
#### Versão: 2.0
##### Observações: nenhuma
###### Problemas a corrigir: nenhum
####### Data e hora da modificação: 03/10 14:00h
######## Ultima pessoa a modificar:	Levi
############################################################################
############################################################################
*/

#ifndef GRAFICO_H
#define GRAFICO_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include "structs.h"

using namespace std;
using namespace std;

/*
## captura caraceter
Pré-condição:   nehuma
Pós-condição:   nenhuma
*/
char getchChar();


/*
## Ler uma linha
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
string lertexto(char * titulo);

/*
## Ler um numero inteiro
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
int lerinteiro(char * titulo);

/*
## Imprime uma notificação na tela
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
void notificacao(char * a);

/*
## Imprime Livro na tela
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
void imprimeLivro(book l);

/*
## Pausa o processamento
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
void pausa();


#endif