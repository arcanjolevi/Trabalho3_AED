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

#ifndef STRUCTS_H
#define STRUCTS_H

#define ORDEM 5


typedef struct chave{
	int id, pos;
}Key;


typedef struct no{
	int myPos, pai;
	Key chaves[ORDEM];
    int filhos[ORDEM+1];
    int numchaves;
    bool eh_folha;
}Bmore;



typedef struct livro{
	int key;
	char title[200];
	char author[100];
	int nExamples;
	int myPos;
}book;

typedef struct cabecalho_arvore{
	int root, free, top;
}headtree;

typedef struct cabecalho_info{
	int top, free;
}headfile;

#endif