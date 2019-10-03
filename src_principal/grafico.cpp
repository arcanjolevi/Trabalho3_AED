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

#include "grafico.h"


/*
## captura caraceter
Pré-condição:   nehuma
Pós-condição:   nenhuma
*/
char getchChar(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return buf;
}


/*
## Ler uma linha
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
string lertexto(char * titulo){
    system("clear");
    int largura = 40, altura = 3;
    string texto;
    cout << "\n\n\n\n\n";
    cout << "                                            \u259B";
    int i;
    for(i = 0;i < largura; i++)
        cout << "\u2580";
    cout << "\n";
    cout <<"                                            \u258C";
    printf("%-39s\n", titulo);
    
    cout << "                                            \u258C ";
    getline(cin, texto);
    return texto;
}

/*
## Ler um numero inteiro
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
int lerinteiro(char * titulo){
    system("clear");
    int largura = 40, altura = 3;
    int numero;
    cout << "\n\n\n\n\n";
    cout << "                                            \u259B";
    int i;
    for(i = 0;i < largura; i++)
        cout << "\u2580";
    cout << "\n";
    cout <<"                                            \u258C";
    printf("%-39s\n", titulo);
    
    cout << "                                            \u258C ";
    cin >> numero;
    scanf("%*c");
    return numero;
}

/*
## Imprime uma notificação na tela
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
void notificacao(char * a){
    int largura = 40, altura = 3;
    system("clear");
    cout << "\n\n\n\n\n";
    cout << "                                            \u259B";
    int i;
    for(i = 0;i < largura; i++)
        cout << "\u2580";
    cout << "\n";
    cout << "                                            \u258C";
    printf("%s\n", a);
    cout << "                                            \u258C \"C\" para Continuar";
    getchChar();
    system("clear");
}

/*
## Imprime Livro na tela
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
void imprimeLivro(book l){
    int largura = 40, altura = 3;
    system("clear");
    cout << "\n\n\n\n\n";
    cout << "                                            \u259B";
    int i;
    for(i = 0;i < largura; i++)
        cout << "\u2580";
    cout << "\n";
    cout << "                                            \u258C";
    cout << "Titulo: " << l.title << endl;
    cout << "                                            \u258C";
    cout << "Autor: " << l.author << endl;
    cout << "                                            \u258C";
    cout << "Chave: " << l.key << endl;
    cout << "                                            \u258C";
    cout << "N de Exemplares: " << l.nExamples << endl;
    cout << "                                            \u258C\n";
    cout << "                                            \u258C \"C\" para Continuar";
    getchChar();
    system("clear");
}


/*
## Pausa o processamento
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
void pausa(){
    cout << "                                            \u258C\n";
    cout << "                                            \u258C \"C\" para Continuar";
    getchChar();
    system("clear");
}


