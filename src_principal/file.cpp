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
#include "file.h"

char * file::BMoreTree = "bmoretree.bin";
char * file::booksData = "booksdata.bin";
file * file::instance = NULL;


/*
## Retorna instancia do singleton
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
file * file::getInstance(){
	if(instance == NULL)
		instance = new file();
	return instance;
}

/*
## Cria cabeçalhos dos arquivo
Pré-condição:	nenhuma
Pós-condição:	cabeçalhos criados e gravados
*/
void file::creatHead(){
	this->tree_head.top = 0;
	this->tree_head.root = -1;
	this->tree_head.free = -1;

	this->data_head.top = 0;
	this->data_head.free = -1;

	this->setHeadFile(data_head);
	this->setHeadTree(tree_head);
}

/*
## Construtor classe file
Pré-condição:	nenhuma
Pós-condição:	arquivos criados e abertos
*/
file::file (){
	this->binFile = fopen(BMoreTree, "w+b");
	this->dataFile = fopen(booksData, "w+b");

	if(this->dataFile == NULL || this->binFile == NULL)
		this->fileError();

	this->creatHead();
}

/*
## Destrutor classe file
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
file::~file(){
	fclose(this->binFile);
	fclose(this->dataFile);
}

/*
## Notificação de erro de arquivo
Pré-condição:	nenhuma
Pós-condição:	mensagem impressa na tela
*/
void file::fileError(){
	cout << "Erro arquivo" << endl;
}

/*
## Retorna cabeçalho do arquivo de dados
Pré-condição:	arquivo aberto
Pós-condição:	nenhuma
*/
headfile  file::getHeadFile(){
	fseek(this->dataFile, 0, SEEK_SET);
	fread(&this->data_head, sizeof(headfile), 1, this->dataFile);
	return this->data_head;
}

/*
## Grava cabeçalo no arquivo binario de dados
Pré-condição:	arquivo inicializado	
Pós-condição:	cabeçalho gravado no arquivo
*/
void file::setHeadFile(headfile head){
	this->data_head = head;
	fseek(this->dataFile, 0, SEEK_SET);
	fwrite(&head, sizeof(headfile), 1, this->dataFile);
}

/*
## Retorna cabeçalho do arquivo binario da arvore
Pré-condição:	arquivo inicializado e aberto
Pós-condição:	nenhuma
*/
headtree file::getHeadTree(){
	fseek(this->binFile, 0, SEEK_SET);
	fread(&this->tree_head, sizeof(headtree), 1, this->binFile);
	return this->tree_head;
}

/*
## Grava cabeçalho no arquivo binario de árvore
Pré-condição:	arquivo aberto
Pós-condição:	cabeçalho gravado no arquivo
*/
void file::setHeadTree(headtree head){
	this->tree_head = head;
	fseek(this->binFile, 0, SEEK_SET);
	fwrite(&head, sizeof(headtree), 1, this->binFile);
}

/*
## Retorna no em uma posição expecifica do arquivo
Pré-condição:	arquivo aberto
Pós-condição:	nenhuma
*/
Bmore file::getBMoreTree(int pos){
	Bmore a;
   	fseek(this->binFile, sizeof(headtree) + pos * sizeof(Bmore), SEEK_SET);
	fread(&a, sizeof(Bmore), 1, this->binFile);
	return a;
}

/*
## Grava nó no arquivo em determinada posição 
Pré-condição:	arquivo aberto
Pós-condição:	no gravado no arquivo, arquivo alterado
*/
void file::setBMoreTree(Bmore r, int pos){
	fseek(this->binFile, sizeof(headtree) + pos * sizeof(Bmore), SEEK_SET);
	fwrite(&r, sizeof(Bmore), 1, this->binFile);
}

/*
## Grava nó no arquivo binario, expecificamente na posiçao referente a r.myPos
Pré-condição:	arquivo aberto
Pós-condição:	Nó gravado, arquivo alterado
*/
int file::setBMoreTree(Bmore r){
	int position;
	if(r.myPos == -1){
		position = getNextPosition("Tree");
		r.myPos = position;
	}
	else
		position = r.myPos;
	
	fseek(this->binFile, sizeof(headtree) + position * sizeof(Bmore), SEEK_SET);
	fwrite(&r, sizeof(Bmore), 1, this->binFile);

	return position;
}

/*
## Retorna dados de um livro em determinada posição do arquivo
Pré-condição:	arquivo aberto
Pós-condição:	nenhuma
*/
book file::getBookData(int pos){
	book a;
   	fseek(this->dataFile, sizeof(headfile) + pos * sizeof(book), SEEK_SET);
	fread(&a, sizeof(book), 1, this->dataFile);
	return a;
}

/*
## Grava dados de um livro em determinada posição do arquivo binario
Pré-condição:	arquivo aberto
Pós-condição:	arquivo alterado
*/
void file::setBookData(book b, int pos){
	fseek(this->dataFile, sizeof(headfile) + pos * sizeof(book), SEEK_SET);
	fwrite(&b, sizeof(book), 1, this->dataFile);
}

/*
## Grava dados de um livro no arquivo, na posição de b.myPos
Pré-condição:	arquivo aberto
Pós-condição:	arquivo alterado
*/
int file::setBookData(book b){
	int position;
	if(b.myPos == -1){
		position = getNextPosition("Data");
		b.myPos = position;
	}
	else
		position = b.myPos;
	fseek(this->dataFile, sizeof(headfile) + position * sizeof(book), SEEK_SET);
	fwrite(&b, sizeof(book), 1, this->dataFile);

	return position;
}

/*
## Retorna a proxima posição que pode ser ocupda nos arquivos
Pré-condição:	arquivo aberto
Pós-condição:	cabeçalhos alterados
*/
int file::getNextPosition(string a){
	int posaux;
	if(a == "Data"){
		this->getHeadFile();
		if(this->data_head.free == -1){
			this->data_head.top++;
			this->setHeadFile(this->data_head);
			return this->data_head.top - 1;
		}else{
			posaux = this->data_head.free;
			book aux = this->getBookData(posaux);
			data_head.free = aux.key;//Lista Encadeada
			this->setHeadFile(this->data_head);
			return posaux;
		}
	}else if(a == "Tree"){
		this->getHeadTree();
		if(this->tree_head.free == -1){
			this->tree_head.top++;
			this->setHeadTree(this->tree_head);
			return this->tree_head.top - 1;
		}else{
			posaux = this->tree_head.free;
			Bmore aux = this->getBMoreTree(posaux);
			this->tree_head.free = aux.pai;//Lista Encadeada
			this->setHeadTree(this->tree_head);
			return posaux;

		}

	}else{
		cout << "Erro de espaco em arquivo\n\n";
	}
}



/*
## Imprime cabeçalho do arquivo de dados
Pré-condição:	arquivo aberto
Pós-condição:	impressão na tela
*/
void file::showHeadFile(){
	this->getHeadFile();
	cout << "Top: " << this->data_head.top << " " << "Free: " 
	<< this->data_head.free << endl;
} 



/*
## Imprime cabeçalho do arquivo da arvore
Pré-condição:	arquivo aberto
Pós-condição:	impressão na tela
*/
void file::showHeadTree(){
	this->getHeadTree();
	cout << "Root: " << this->tree_head.root << " " << "Top: " << this->tree_head.top << " "
	<< "Free: " << this->tree_head.free << endl;
}