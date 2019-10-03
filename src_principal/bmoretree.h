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

#ifndef BMORETREE_H
#define BMORETREE_H

#include "structs.h"
#include "file.h"

class BMTREE{
private:
	static BMTREE * instanceBMTREE;
	Bmore tree;
	int pos;
	
	/*
	## Construtor da classe BMTREE
	Pré-condição:	nenhuma
	Pós-condição:	nenhuma
	*/	
	BMTREE();

public:
	
	file * DataBase;

	/*
	## Destrutor da classe BMTREE
	Pré-condição: 	nenhuma	
	Pós-condição:	nenhuma
	*/
	static BMTREE * getInstance();
	

	

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


	/*
	## Auxulia na procura de um livro na arvore
	Pré-condição:   nenhuma
	Pós-condição:   nenhuma
	*/
	book search_aux(int pos, int key);


	/*
	## Procura Um livro na arvore
	Pré-condição:	arquivo iniciado
	Pós-condição:	nenhuma
	*/
	book searchBook(int pos);

	/*
	## Atualiza qtd de exemplares de um livro
	Pré-condição:	arquivo iniciado
	Pós-condição:	retorna se foi alterado ou nao
	*/
	int updateNumberofBooks(int key, int newNumber);

	/*
	## Imprime todas as folhas da arvore (chaves validas)
	Pré-condição:	arquivo iniciado
	Pós-condição:	nenhuma
	*/
	void printKeys();

	/*
	## imprime todos todos os elementos de um nó da arvore
	Pré-condição:   arvore valida, arquivo iniciado
	Pós-condição:   nenhuma
	*/
	void Debug(Bmore a);

	/*
	## Imprime Acervo
	Pre-condição:	arquiv aberto
	Pós-condição:	acervo impresso
	*/
	void printBooks();

	/*
	## Imprime todos os livros de um nó
	Pre-condição:	arquivo aberto
	Pós-condição:	livro do impressos na tela
	*/
	void printNodeBook(Bmore a);

	/*
	##	Imprime um livro
	Pre-condição:	nenhuma
	Pós-condição:	livro impreso na tela
	*/
	void printOneBook(book l);

	/*
	## Prepara um nó novo para uso
	Pré-condição:   nenhuma
	Pós-condição:   todos os dados zerados
	*/
	Bmore newBmore();

	/*
	## Atualiza pai de todos os filho de um no
	Pré-condição:   arquivo iniciado
	Pós-condição:   pai dos nós atualizado
	*/
	void updateFather(Bmore aux);

};






#endif 