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

#ifndef INTERACAO_H
#define INTERACAO_H

#include "structs.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;

#include "bmoretree.h"
#include "grafico.h"


/*
## Intercação com usuario na leitura de arquivo
Pré-condição:	nenhuma
Pós-condição:	nennhuma
*/
void carregarArquivo();
/*
## Ler livro do usuario e insere na Base de dados
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void inserirLivro();

/*
## Atualiza numero de exemplares
Pré-condição:	nenhma
Pós-condição:	nenhuma
*/
void atualizarExemplares();

/*
## Remove livro escolhido pelo usuario
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void removerLivro();

/*
## Procura um livro escolhido elo usuario
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void buscaLivro();

/*
## Imprime acervo na tela
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void imprimirAcervo();

/*
## Imprime Arvore B+ por niveis
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void imprimirArvore();

#endif