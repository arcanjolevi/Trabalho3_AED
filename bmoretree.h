/*
############################################################################
############################################################################
## REGISTRO DESTE ARQUIVO
#### Versão: 1.0
##### Observações: nenhuma
###### Problemas a corrigir: nenhum
####### Data e hora da modificação: 24/09 20:00h
######## Ultima pessoa a modificar:	Levi
############################################################################
############################################################################
*/

#ifndef BMORETREE_H
#define BMORETREE_H

#include "structs.h"
#include "inserebtree.h"
#include "printbtree.h"

class BTREE{
private:
	Bmore * r;

public:

	/*
	## Construtor da classe BTREE
	Pré-condição:	nenhuma
	Pós-condição:	nenhuma
	*/
	BTREE();

	/*
	## Destrutor da classe BTREE
	Pré-condição: 	nenhuma	
	Pós-condição:	nenhuma
	*/
	~BTREE();

	/*
	## insere elemento na arvore
	Pré-condição:	arvore válida
	Pós-condição:	elemento inserido
	*/
	void insert(int info);

	/*
	## Imprime arvore por niveis
	Pré-condição:	arvore válida
	Pós-condição:	nenhuma
	*/
	void showLevels();
};




#endif 