/*
############################################################################
############################################################################
## REGISTRO DESTE ARQUIVO
#### Versão: 1.1
##### Observações: nenhuma
###### Problemas a corrigir: nenhum
####### Data e hora da modificação: 01/10 14:00h
######## Ultima pessoa a modificar:	Levi
############################################################################
############################################################################
*/


#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include "grafico.h"
#include "interacao.h"
using namespace std;



/*
## Imprime intem menu
Pré-condição:	Nenhuma
Pós-condição:	nhenhuma
*/
void itemMenu(char * texto);

/*
## Imprime item selecionado
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void itemMenuSelecionado(char * texto);


/*
## imprime quadro
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void imprimeQuadro(int n);

/*
## Direciona para as funções
Pré-condição: nehuma
Pós-condição:	nenhuma
*/
void funcionalidade(int i);

/*
## Menu principal
Pré-condição: nenhuma
Pós-condição:	nenhuma
*/
void menu();



#endif