/*
############################################################################
############################################################################
## REGISTRO DESTE ARQUIVO
#### Versão: 1.0
##### Observações: nenhuma
###### Problemas a corrigir: nenhum
####### Data e hora da modificação: 25/09 20:00h
######## Ultima pessoa a modificar:	Levi
############################################################################
############################################################################
*/


#ifndef STRUCTS_H
#define STRUCTS_H

#define ORDEM 5

typedef struct no{
    struct no * filhos[ORDEM+1];
    struct no * pai;
    bool eh_folha;
    int chaves[ORDEM];
    int numchaves;
}Bmore;

typedef struct livro{
	int key;
	char title[200];
	char author[100];
	int nExamples;

}book;

typedef struct cabecalho_arvore{
	int raiz, free, top;
}headtree;

typedef struct cabecalho_info{
	int top, free;
}headfile;

#endif