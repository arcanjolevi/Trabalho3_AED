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



#include "menu.h"



/*
## Imprime intem menu
Pré-condição:	Nenhuma
Pós-condição:	nhenhuma
*/
void itemMenu(char * texto){
	int largura = 40, altura = 3;
	int i, j;

	printf("                                            \u2554");
	for(i = 0;i < largura; i++)
		printf("\u2550");
	printf("\u2557\n");

	printf("                                            \u2551");
	printf("%-38s", texto);
	printf("  ");
	printf("\u2551\n");

	printf("                                            \u255A");
	for(i = 0;i < largura; i++)
		printf("\u2550");
	printf("\u255D\n");
}

/*
## Imprime item selecionado
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void itemMenuSelecionado(char * texto){
	int largura = 40, altura = 3;
	int i, j;

	printf("                                            \u259B");
	for(i = 0;i < largura; i++)
		printf("\u2580");
	printf("\u259c\n");
	

	printf("                                            \u258C");
	printf("%-38s", texto);
	printf("\u2590 ");
	printf("\u2590\n");

	printf("                                            \u2599");
	for(i = 0;i < largura; i++)
		printf("\u2584");
	printf("\u259F\n");
}


/*
## imprime quadro
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void imprimeQuadro(int n){
	system("clear");
	int largura = 41, altura = 3;
	int i, j;

	

	printf("\n\n\n\n\n\n\n\n                                           \u259B");
	for(i = 0;i <= largura; i++)
		printf("\u2598");
	printf("\u259C\n");

	if(n == 0)	
		itemMenuSelecionado("CARREGAR ARQUIVO");
	else 
		itemMenu("CARREGAR ARQUIVO");
	if(n == 1)	
		itemMenuSelecionado("INSERIR LIVRO");
	else 
		itemMenu("INSERIR LIVRO");
	if(n == 2)	
		itemMenuSelecionado("ATUALIZAR N DE EXEMPLARES");
	else 
		itemMenu("ATUALIZAR N DE EXEMPLARES");
	if(n == 3)	
		itemMenuSelecionado("REMOVER LIVRO");
	else 
		itemMenu("REMOVER LIVRO");
	if(n == 4)	
		itemMenuSelecionado("BUSCAR DADOS DE LIVRO");
	else 
		itemMenu("BUSCAR DADOS DE LIVRO");
	if(n == 5)	
		itemMenuSelecionado("IMPRIMIR ACERVO");
	else 
		itemMenu("IMPRIMIR ACERVO");
	if(n == 6)	
		itemMenuSelecionado("IMPRIMIR ARVORE B+");
	else 
		itemMenu("IMPRIMIR ARVORE B+");	

	printf("                                           \u2599");
	for(i = 0;i <= largura-1; i++)
		printf("\u2597");
	printf("\u2597");
	printf("\u259F\n");
	printf("                                           \"W\" E \"S\" MOVIMENTO - \"M\" SELECAO - \"E\" Sair \n                                                                  ");
	
}

/*
## Direciona para as funções
Pré-condição: nehuma
Pós-condição:	nenhuma
*/
void funcionalidade(int i){
	if(i == 0){// carregar Arquivo
		carregarArquivo();		
	}else if(i == 1){//inserir Livro
		inserirLivro();
	}else if(i == 2){//atualizar n exemplares
		atualizarExemplares();
	}else if(i == 3){//remover livro
		removerLivro();
	}else if(i == 4){//buscar dados livro
		buscaLivro();
	}else if(i == 5){//imprimir acervo
		imprimirAcervo();
	}else if(i == 6){//ímprimir arvore b+
		imprimirArvore();
	}else if(i == 7){//
		//Função aqui
	}else if(i == 8){//
		//Função aqui
	}
}


/*
## Menu principal
Pré-condição: nenhuma
Pós-condição:	nenhuma
*/
void menu(){
	char x = 'z';
	int i = 0;
	int selecao, primeiro = 0, ultimo = 6;
	while(x != 'x' && x != 'X'){
		imprimeQuadro(i);
		x = getchChar();
		if(x == 'w' || x == 'W')
			if(i == primeiro){
				i = ultimo;
			}
			else
				i--;
		if(x == 's' || x == 'S')
			if(i == ultimo)
				i = primeiro;
			else
				i++;

		if(x == 'M' || x == 'm')
			funcionalidade(i);

		if(x == 'E' || x == 'e')
			break;
	}
}
