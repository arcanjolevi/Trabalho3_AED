/*
############################################################################
############################################################################
## REGISTRO DESTE ARQUIVO
#### Versão: 1.0
##### Observações: nenhuma
###### Problemas a corrigir: nenhum
####### Data e hora da modificação: 25/09 20:00h
######## Ultima pessoa a modificar: Levi
############################################################################
############################################################################
*/

#ifndef FILE_H
#define FILE_H

#include "structs.h"
#include <iostream>
using namespace std;

class file{
private:
	char * BMoreTree = "bmoretree.bin";
	char * booksData = "booksdata.bin";
	FILE * binFile;
	FILE * dataFile;

public:	
	file();
	~file();
	void fileError();
	headfile * getHeadFile();
	void setHeadFile(headfile * h);
	headtree * getHeadTree();
	void setHeadTree(headtree * h);

	bmoretree* getBMoreTree();
	void setBMoreTree(bmoretree * r);
	book * getBookData();
	void setBookData(book * b);
};


/*
## 
Pré-condição:	
Pós-condição:	
*/
file::file (){
	this->binFile = fopen(BMoreTree, "w+b");
	this->dataFile = fopen(booksData, "w+b");

	if(this->dataFile == NULL || this->binFile == NULL)
		this->fileError();
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
file::~file(){
	fclose(this->binFile);
	fclose(this->dataFile);
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
void file::fileError(){
	cout << "Erro arquivo" << endl;
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
headfile * file::getHeadFile(){
	headfile * aux = new headfile;
	fseek(this->dataFile, 0, SEEK_SET);
	fread(aux, sizeof(headfile), 1, this->dataFile);
	return aux;
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
void file::setHeadFile(headfile * head){
	fseek(this->dataFile, 0, SEEK_SET);
	fwrite(head, sizeof(headfile), 1, this->dataFile);
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
headtree * file::getHeadTree(){
	headtree * aux = new headtree;
	fseek(this->binFile, 0, SEEK_SET);
	fread(aux, sizeof(headtree), 1, this->binFile);
	return aux;
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
void file::setHeadTree(headtree * head){
	seek(this->binFile, 0, SEEK_SET);
	fwrite(head, sizeof(headtree), 1, this->binFile);
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
Bmore * file::getBMoreTree(int pos){
	Bmore * a = new Bmore;
   	fseek(this->binFile, sizeof(headtree) + pos * sizeof(Bmore), SEEK_SET);
	fread(a, sizeof(Bmore), 1, this->binFile);
	return a;
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
void file::setBMoreTree(bmoretree * r, int pos){
	fseek(this->binFile, sizeof(headtree) + pos * sizeof(Bmore), SEEK_SET);
	fwrite(r, sizeof(Bmore), 1, this->binFile);
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
book * file::getBookData(int pos){
	book * a = new book;
   	fseek(this->dataFile, sizeof(headfile) + pos * sizeof(book), SEEK_SET);
	fread(a, sizeof(book), 1, this->dataFile);
	return a;
}

/*
## 
Pré-condição:	
Pós-condição:	
*/
void file::setBookData(book * b){
	fseek(this->dataFile, sizeof(headfile) + pos * sizeof(book), SEEK_SET);
	fwrite(b, sizeof(book), 1, this->dataFile);
}



#endif