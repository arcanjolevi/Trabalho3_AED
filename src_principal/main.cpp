/*
############################################################################
############################################################################
## REGISTRO DESTE ARQUIVO
#### Versão: 2.0
##### Observações: nenhuma
###### Problemas a corrigir: nenhum
####### Data e hora da modificação: 03/10 14:00h
######## Ultima pessoa a modificar: Levi
############################################################################
############################################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <string.h>

#include "structs.h"
#include "bmoretree.h"
#include "file.h"
#include "menu.h"

using namespace std;





int main () {
    BMTREE * r = BMTREE::getInstance();
    menu();
    return 0;    
}