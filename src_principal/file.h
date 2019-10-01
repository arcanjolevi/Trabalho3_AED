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

#ifndef FILE_H
#define FILE_H

#include "structs.h"
#include <iostream>
#include <string>
using namespace std;

class file{
private:
	static file * instance;
	static char * BMoreTree;
	static char * booksData;
	FILE * binFile;
	FILE * dataFile;
	headtree tree_head;
	headfile data_head;

	/*
	## Construtor classe file
	Pré-condição:	nenhuma
	Pós-condição:	arquivos criados e abertos
	*/
	
	file();

public:	

	/*
	## Retorna instancia do singleton
	Pré-condição:	nenhuma
	Pós-condição:	nenhuma
	*/
	static file * getInstance();


	/*
	## Cria cabeçalhos dos arquivo
	Pré-condição:	nenhuma
	Pós-condição:	cabeçalhos criados e gravados
	*/
	void creatHead();

	/*
	## Destrutor classe file
	Pré-condição:	nenhuma
	Pós-condição:	nenhuma
	*/
	~file();

	/*
	## Notificação de erro de arquivo
	Pré-condição:	nenhuma
	Pós-condição:	mensagem impressa na tela
	*/
	void fileError();

	/*
	## Retorna cabeçalho do arquivo de dados
	Pré-condição:	arquivo aberto
	Pós-condição:	nenhuma
	*/
	headfile  getHeadFile();

	/*
	## Grava cabeçalo no arquivo binario de dados
	Pré-condição:	arquivo inicializado	
	Pós-condição:	cabeçalho gravado no arquivo
	*/
	void setHeadFile(headfile head);

	/*
	## Retorna cabeçalho do arquivo binario da arvore
	Pré-condição:	arquivo inicializado e aberto
	Pós-condição:	nenhuma
	*/
	headtree getHeadTree();

	/*
	## Grava cabeçalho no arquivo binario de árvore
	Pré-condição:	arquivo aberto
	Pós-condição:	cabeçalho gravado no arquivo
	*/
	void setHeadTree(headtree head);

	/*
	## Retorna no em uma posição expecifica do arquivo
	Pré-condição:	arquivo aberto
	Pós-condição:	nenhuma
	*/
	Bmore getBMoreTree(int pos);

	/*
	## Grava nó no arquivo em determinada posição 
	Pré-condição:	arquivo aberto
	Pós-condição:	no gravado no arquivo, arquivo alterado
	*/
	void setBMoreTree(Bmore r, int pos);

	/*
	## Grava nó no arquivo binario, expecificamente na posiçao referente a r.myPos
	Pré-condição:	arquivo aberto
	Pós-condição:	Nó gravado, arquivo alterado
	*/
	int setBMoreTree(Bmore r);

	/*
	## Retorna dados de um livro em determinada posição do arquivo
	Pré-condição:	arquivo aberto
	Pós-condição:	nenhuma
	*/
	book getBookData(int pos);

	/*
	## Grava dados de um livro em determinada posição do arquivo binario
	Pré-condição:	arquivo aberto
	Pós-condição:	arquivo alterado
	*/
	void setBookData(book b, int pos);

	/*
	## Grava dados de um livro no arquivo, na posição de b.myPos
	Pré-condição:	arquivo aberto
	Pós-condição:	arquivo alterado
	*/
	int setBookData(book b);

	/*
	## Retorna a proxima posição que pode ser ocupda nos arquivos
	Pré-condição:	arquivo aberto
	Pós-condição:	cabeçalhos alterados
	*/
	int getNextPosition(string a);

	/*
	## Imprime cabeçalho do arquivo de dados
	Pré-condição:	arquivo aberto
	Pós-condição:	impressão na tela
	*/
	void showHeadFile();

	/*
	## Imprime cabeçalho do arquivo da arvore
	Pré-condição:	arquivo aberto
	Pós-condição:	impressão na tela
	*/
	void showHeadTree();

};

#endif