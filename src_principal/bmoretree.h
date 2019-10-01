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

#ifndef BMORETREE_H
#define BMORETREE_H

#include "structs.h"
#include "file.h"

class BMTREE{
private:
	Bmore tree;
	int pos;
	

public:

	file * DataBase;

	/*
	## Construtor da classe BMTREE
	Pré-condição:	nenhuma
	Pós-condição:	nenhuma
	*/	
	BMTREE();

	/*
	## Destrutor da classe BMTREE
	Pré-condição: 	nenhuma	
	Pós-condição:	nenhuma
	*/
	~BMTREE();

	/*
	## Imprime arvore por niveis
	Pré-condição:	arquivo iniciado
	Pós-condição:	nenhuma
	*/
	void show();

	/*
	## Split de um no folha
	Pré-condição:	arquivo iniciado, no com overflow
	Pós-condição:	no divido, key alterado, novo no irmao criado
	*/
	int splitfolha(Key * m, int pai);

	/*
	## Split de um nó não folha
	Pré-condição:	arquivo iniciado, no com overflow
	Pós-condição:	no divido, irmao criado, key alterado
	*/
	int split(Key * m, int pai);

	/*
	## Adiciona uma key a direita de um nó não folha
	Pré-condição:	arquivo iniciado
	Pós-condição:	chave inserida no nó
	*/
	void adicionaNaDireita(int pos, Key info, int filho);

	/*
	## Adicona chave a direita de um nó, insere dados do livro no arquivo
	Pré-condição:	arquivos iniciados
	Pós-condição:	chave adiciona no nó, arquivo de dados alterado
	*/
	void adicionaNaDireita(int pos, book info, int filho);

	/*
	## Busca a posicao em que a chave deveria estar ou se ele já está no nó
	Pré-condição:	arquivo iniciado
	Pós-condição:	nenhuma
	*/
	int buscaPos(int info, int * pos);

	/*
	## Auxiliar da inserir principal, adiciona o uma chave caso nao exista
	Pré-condição:	arquivo iniciado, arvore nao vazia
	Pós-condição:	chave inserida, caso nao estaja presente
	*/
	void insere_aux(int node, book info);

	/*
	## Função pricipal para inserção de elementos na arvore
	Pré-condição:	arquivo iniciado
	Pós-condição:	dados inseridos
	*/
	void insert(book info);

	/*
	## Prepara um nó novo para uso
	Pré-condição:   nenhuma
	Pós-condição:   todos os dados zerados
	*/
	void create();

	/*
	## Diz se o nó é folha
	Pré-condição:	nenhuma
	Pós-condição:	nenhuma
	*/
	int eh_folha(Bmore r);

	/*
	## diz de o nó está em overflow
	Pré-condição:	nenhuma
	Pós-condição:	nenhuma
	*/
	int overflow(Bmore r);

	/*
	## Imprime um no da arvore
	Pré-condição:	nenhuma
	Pós-condição:	nenhuma
	*/
	void imprimeNo(Bmore a);

	/*
	## imprime todos todos os elementos de um nivel da arvore
	Pré-condição:	arvore valida, arquivo iniciado
	Pós-condição:	nenhuma
	*/
	void imprimeNiveis(int node, int n);

	/*
	## Retorna altura da arvore
	Pré-condição:	arquivo iniciado
	Pós-condição:	nenhuma
	*/
	int altura(int node);

	/*
	## Imprime todos os niveis da arvore
	Pré-condição:	arquivo iniciado
	Pós-condição:	nenhuma
	*/
	void imprimearvore();

};






#endif 