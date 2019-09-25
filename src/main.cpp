/*
############################################################################
############################################################################
## REGISTRO DESTE ARQUIVO
#### Versão: 1.0
##### Observações: nenhuma
###### Problemas a corrigir: nenhum
####### Data e hora da modificação: 24/09 20:00h
######## Ultima pessoa a modificar: Levi
############################################################################
############################################################################
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

#include "bmoretree.h"
#include "file.h"

int main () {
    cout << "fuca\n";
    file * a = new file();
    headfile * b = new headfile;
    b->top = 44;
    b->free = 7;
    a->setHeadFile(b);
    headfile * c = a->getHeadFile();
    cout << c->top << " " << c-> free << endl;
    
    return 0;
}