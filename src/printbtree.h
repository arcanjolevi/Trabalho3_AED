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

#ifndef PRINTBTREE_H
#define PRINTBTREE_H

#include <iostream>
#include <stdlib.h>
using namespace std;

#include "structs.h"

/*
## Imprime um no da arvore
Pré-condição:	arvore valida
Pós-condição:	nenhuma
*/
void imprimeNo(Bmore * no){
    if(no){
        int i;
        cout << "[" ;
        for(i = 0; i < no->numchaves;i++){
            cout << no->chaves[i];
            if(i+1 != no->numchaves)
                cout << " ";
        }
        cout << "]";
    }
}

/*
## imprime todos todos os elementos de um nivel da arvore
Pré-condição:	arvore valida
Pós-condição:	nenhuma
*/
void imprimeNiveis(Bmore * r, int n){
    if(r){
        if(n == 0){
            imprimeNo(r);            
        }
        else{
            int i;
            for(i = 0;i<= r->numchaves;i++){
                imprimeNiveis(r->filhos[i], n-1);
                //cout << endl;
            }
            
        }
        
    }
}


/*
## Retorna altura da arvore
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
int altura(Bmore * r){
    Bmore * aux = r;
    int i = 0;
    while(r){
        r = r->filhos[0];
        i++;
    }
    return i;
}


/*
## Imprime todos os niveis da arvore
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void imprimearvore(Bmore * r){
    int n = altura(r);
    int i;
    for(i = 0;i < n;i++){
        imprimeNiveis(r,i);
        cout << endl;
    }
    

}

#endif