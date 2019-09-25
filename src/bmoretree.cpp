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

#include "bmoretree.h"


/*
## Construtor da classe BTREE
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/	
BTREE::BTREE(){
	this->r = NULL;
}


/*
## Destrutor da classe BTREE
Pré-condição: 	nenhuma	
Pós-condição:	nenhuma
*/
BTREE::~BTREE(){
	cout << "Arvore Deletada" << endl;
}

/*
## insere elemento na arvore
Pré-condição:	arvore válida
Pós-condição:	elemento inserido
*/
void BTREE::insert(int info){
	this->r = insere(this->r, info);
}


/*
## Imprime arvore por niveis
Pré-condição:	arvore válida
Pós-condição:	nenhuma
*/
void BTREE::show(){
	imprimearvore(this->r);
}