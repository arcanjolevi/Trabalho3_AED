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

#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#include "structs.h"
#include "bmoretree.h"
#include "file.h"

int main () {
    cout << "fucaaa\n";   
    BMTREE * r = new BMTREE();
    r->DataBase->showHeadTree();
    r->DataBase->showHeadFile();
    book a;
    a.myPos = -1;
    a.nExamples = 5;
    strcpy(a.author, "fulano");
    strcpy(a.title, "Nome Livro");
    a.key = 10;
    r->insert(a);
    a.key = 20;
    r->insert(a);
    a.key = 30;
    r->insert(a);
    a.key = 40;
    r->insert(a);
    a.key = 50;
    r->insert(a);
    a.key = 60;
    r->insert(a);
    a.key = 70;
    r->insert(a);
    a.key = 80;
    r->insert(a);
    a.key = 90;
    r->insert(a);
    a.key = 11;
    r->insert(a);
    a.key = 21;
    r->insert(a);
    a.key = 31;
    r->insert(a);
    a.key = 41;
    r->insert(a);
    a.key = 51;
    r->insert(a);
    a.key = 61;
    r->insert(a);
    a.key = 52;
    r->insert(a);
	a.key = 32;
    r->insert(a);   
    
    r->show();
    return 0;
}