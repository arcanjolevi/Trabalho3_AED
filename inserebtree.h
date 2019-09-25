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


#ifndef INSEREBTREE_H
#define INSEREBTREE_H
#include "structs.h"



/*
## Zera todos os filhos de um no
Pré-condição:	nó nao nulo
Pós-condição:	todos os filhos zerados
*/
Bmore * zeraFilhos(Bmore * r){
    int i = 0;
    for (i = 0;i < ORDEM ;i++)
        r->filhos[i] = 0;
    return r;
}

/*
## Diz se o nó é folha
Pré-condição:	nó nao nulo
Pós-condição:	nenhuma
*/
int eh_folha(Bmore * r){
    return (r->filhos[0] == 0);
}


/*
## diz de o nó está em overflow
Pré-condição:	nó nao nulo
Pós-condição:	nenhuma
*/
int overflow(Bmore * r){
    return (r->numchaves == ORDEM);
}


/*
## Faz split de uma folha da arvore b+
Pré-condição:	nó nao nulo
Pós-condição:	nó dividido em dois
*/
Bmore * splitfolha(Bmore * r, int * m, Bmore * pai){
    Bmore * novaDireita = new struct no;
    novaDireita->pai = pai;
    r->pai = pai;
    novaDireita = zeraFilhos(novaDireita);
    int q = r->numchaves/2;
    novaDireita->numchaves = r->numchaves - q;
    r->numchaves = q;
    *m = r->chaves[q];
    int i = 0;

    for(i = 0;i<=r->numchaves;i++){
        novaDireita->chaves[i] = r->chaves[q+i];
    }
    r->filhos[q] = novaDireita->filhos[0];
    r->filhos[r->numchaves] = novaDireita;
    return novaDireita;
}


/*
## faz split de um no nao folha
Pré-condição:	nó nao nulo
Pós-condição:	no dividido em dois
*/
Bmore * split(Bmore * r, int * m, Bmore * pai){
    Bmore * novaDireita = new struct no;
    novaDireita = zeraFilhos(novaDireita);
    novaDireita->pai = pai;
    r->pai = pai;
    int q = r->numchaves/2;
    novaDireita->numchaves = r->numchaves - q - 1;
    r->numchaves = q;
    *m = r->chaves[q];
    int i = 0;
    novaDireita->filhos[0] = r->filhos[q+1];
    for(i = 0;i<r->numchaves;i++){
        novaDireita->chaves[i] = r->chaves[q+i+1];
        novaDireita->filhos[i+1] = r->filhos[q+2+i];
    }
    
    return novaDireita;
}


/*
## Busca posição adequada para uma chave
Pré-condição:	nó nao nulo
Pós-condição:	nenhuma
*/
int buscaPos(Bmore * r, int info, int * pos){
    for((*pos) = 0;(*pos) < r->numchaves;(*pos)++){
        if(r->chaves[(*pos)] == info)
            return 1;
        else if(info < r->chaves[(*pos)])
            break;
    }
    return 0;
}

/*
## Adiciona elemento info em pos, descolando os membros para a direita
Pré-condição:	no nao nulo
Pós-condição:	chave adicionada em pos
*/
void adicionaNaDireita(Bmore * r, int pos, int info, Bmore * filho){
    int i; 
    for(i = r->numchaves;i>pos;i--){
        r->chaves[i] = r->chaves[i-1];
        r->filhos[i + 1] = r->filhos[i];
    }
    r->chaves[pos] = info;
    r->numchaves++;
    r->filhos[pos+1] = filho;  
}


/*
## Auxiliar da inserir
Pré-condição:	no nao nulo
Pós-condição:	chave inserirda na arvore
*/
void insere_aux(Bmore * r, int info){
    int pos;
    if(!buscaPos(r, info, &pos)){
        if(eh_folha(r)){
            //cout << "pos = " << pos << endl;
            adicionaNaDireita(r, pos, info, NULL);
        }
        else{
            insere_aux(r->filhos[pos], info);
            if(overflow(r->filhos[pos])){

                int m;
                Bmore * aux;
                if(eh_folha(r->filhos[pos]))
                    aux = splitfolha(r->filhos[pos], &m, r);
                else
                    aux = split(r->filhos[pos], &m, r);
                adicionaNaDireita(r, pos, m, aux);
            }
        }
    }else
        printf("%d ja esta na arvore\n", info);
}


/*
## Função principal de inserção
Pré-condição:	arvore valida
Pós-condição:	chave inserida na arvore
*/
Bmore * insere(Bmore * r, int info){
    if(r == NULL){
        r = new (Bmore);
        r = zeraFilhos(r);
        r->numchaves = 1;
        r->chaves[0] = info;
        r->pai = NULL;
        r->filhos[0] = NULL;
    }
    else{
        insere_aux(r, info);
        if(overflow(r)){
            int m;
            Bmore * novaRaiz = new (Bmore);
            novaRaiz = zeraFilhos(novaRaiz);
            Bmore * direita;
            if(eh_folha(r))
                    direita = splitfolha(r, &m, novaRaiz);
            else
                direita = split(r, &m, novaRaiz);            
            novaRaiz->chaves[0] = m;
            novaRaiz->numchaves = 1;
            novaRaiz->filhos[0] = r;
            novaRaiz->filhos[1] = direita;
            return novaRaiz;
        }
    }
    return r;
}

#endif