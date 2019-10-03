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

#include "interacao.h"

/*
## Intercação com usuario na leitura de arquivo
Pré-condição:	nenhuma
Pós-condição:	nennhuma
*/
void carregarArquivo(){
	notificacao("Carregar Arquivo");
}

/*
## Ler livro do usuario e insere na Base de dados
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void inserirLivro(){
	BMTREE * r = BMTREE::getInstance();
	notificacao("Inserir Livro");
	book novo;
	novo.myPos = -1;
	novo.key = lerinteiro("Insira a chave do livro");
	strcpy(novo.title, lertexto("Insira o Titulo no Livro").c_str());
	strcpy(novo.author, lertexto("Insira o Autor no Livro").c_str());
	novo.nExamples = lerinteiro("Insira o numero de exemplares");
	r->insert(novo);
}

/*
## Atualiza numero de exemplares
Pré-condição:	nenhma
Pós-condição:	nenhuma
*/
void atualizarExemplares(){
	BMTREE * r = BMTREE::getInstance();
	notificacao("Atualizar Numero de exemplares");
	int chave = lerinteiro("Insira a chave do livro");
	int numero = lerinteiro("Insira o novo numero de exemplares");
	if(!r->updateNumberofBooks(chave, numero))
		notificacao("Impossivel Atualizar");
	pausa();
}

/*
## Remove livro escolhido pelo usuario
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void removerLivro(){
	notificacao("Remover Livro");
	int chave = lerinteiro("Insira a chave do livro");
	//Remover livro
}

/*
## Procura um livro escolhido elo usuario
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void buscaLivro(){
	BMTREE * r = BMTREE::getInstance();
	notificacao("Buscar Livro");
	int chave = lerinteiro("Insira a chave do livro");
	book a = r->searchBook(chave);
	if(a.key != -1)
		imprimeLivro(a);
	else
		notificacao("Livro Nao Encontrado");
}

/*
## Imprime acervo na tela
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void imprimirAcervo(){
	notificacao("imprimir Acervo");
	BMTREE * r = BMTREE::getInstance();
	r->printBooks();
	pausa();
	
}

/*
## Imprime Arvore B+ por niveis
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void imprimirArvore(){
	notificacao("Imprimir Arvore");
	BMTREE * r = BMTREE::getInstance();
	r->show();
	pausa();
}