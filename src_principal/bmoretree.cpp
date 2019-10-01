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

#include "bmoretree.h"


/*
## Construtor da classe BMTREE
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/	
BMTREE::BMTREE(){
	this->DataBase = file::getInstance();
	this->pos = -1;
}


/*
## Destrutor da classe BMTREE
Pré-condição: 	nenhuma	
Pós-condição:	nenhuma
*/
BMTREE::~BMTREE(){
	delete this->DataBase;
}



/*
## Imprime arvore por niveis
Pré-condição:	arquivo iniciado
Pós-condição:	nenhuma
*/
void BMTREE::show(){
	this->imprimearvore();
}


/*
## Split de um no folha
Pré-condição:	arquivo iniciado, no com overflow
Pós-condição:	no divido, key alterado, novo no irmao criado
*/
int BMTREE::splitfolha(Key * m, int pai){
	Bmore aux = this->tree;
	int newPos = this->DataBase->getNextPosition("Tree");
	this->create();
    this->tree.pai = pai;
    this->tree.myPos = newPos;
	
	int q = aux.numchaves/2;
    this->tree.numchaves = aux.numchaves - q;
    aux.numchaves = q;
    *m = aux.chaves[q];

    int i = 0;
    for(i = 0; i <= aux.numchaves;i++){
        this->tree.chaves[i] = aux.chaves[q+i];
    }
    aux.filhos[q] = this->tree.filhos[0];
    aux.filhos[aux.numchaves] = this->tree.myPos;

    this->DataBase->setBMoreTree(this->tree);
    this->tree = aux;

    return newPos;
}


/*
## Split de um nó não folha
Pré-condição:	arquivo iniciado, no com overflow
Pós-condição:	no divido, irmao criado, key alterado
*/
int BMTREE::split(Key * m, int pai){
    Bmore aux = this->tree;
    int newPos = this->DataBase->getNextPosition("Tree");
    this->create();
    this->tree.pai = pai;
    this->tree.myPos = newPos;
    int q = aux.numchaves/2;
    this->tree.numchaves = aux.numchaves - q - 1;
    aux.numchaves = q;
    *m = aux.chaves[q];
    int i = 0;
    this->tree.filhos[0] = aux.filhos[q+1];
    for(i = 0; i < aux.numchaves; i++){
        this->tree.chaves[i] = aux.chaves[q+1+i];
        this->tree.filhos[i + 1] = aux.filhos[q+2+1]; 
    }

    this->DataBase->setBMoreTree(this->tree);
    this->tree = aux;
    
    return newPos;
}


/*
## Adiciona uma key a direita de um nó não folha
Pré-condição:	arquivo iniciado
Pós-condição:	chave inserida no nó
*/
void BMTREE::adicionaNaDireita(int pos, Key info, int filho){
    int i; 
    for(i = this->tree.numchaves;i>pos;i--){
        this->tree.chaves[i] = this->tree.chaves[i-1];
        this->tree.filhos[i+1] = this->tree.filhos[i];
    }
    this->tree.chaves[pos] = info;
    this->tree.numchaves++;
    this->tree.filhos[pos+1] = filho;
}

/*
## Adicona chave a direita de um nó, insere dados do livro no arquivo
Pré-condição:	arquivos iniciados
Pós-condição:	chave adiciona no nó, arquivo de dados alterado
*/
void BMTREE::adicionaNaDireita(int pos, book info, int filho){
    int i; 
    for(i = this->tree.numchaves;i>pos;i--){
        this->tree.chaves[i] = this->tree.chaves[i-1];
        this->tree.filhos[i+1] = this->tree.filhos[i];
    }
    this->tree.chaves[pos].id = info.key;
    this->tree.chaves[pos].pos = this->DataBase->setBookData(info);
    this->tree.numchaves++;
    this->tree.filhos[pos+1] = filho;
}


/*
## Busca a posicao em que a chave deveria estar ou se ele já está no nó
Pré-condição:	arquivo iniciado
Pós-condição:	nenhuma
*/
int BMTREE::buscaPos(int info, int * pos){
    for((*pos) = 0;(*pos) < this->tree.numchaves;(*pos)++){
        if(this->tree.chaves[(*pos)].id == info)
            return 1;
        else if(info < this->tree.chaves[(*pos)].id)
            break;
    }
    return 0;
}

/*
## Auxiliar da inserir principal, adiciona o uma chave caso nao exista
Pré-condição:	arquivo iniciado, arvore nao vazia
Pós-condição:	chave inserida, caso nao estaja presente
*/
void BMTREE::insere_aux(int node, book info){
    int pos;
    this->tree = DataBase->getBMoreTree(node);
    if(!buscaPos(info.key, &pos)){
        if(eh_folha(this->tree)){
            adicionaNaDireita(pos, info, -1);
            this->DataBase->setBMoreTree(this->tree);
        }
        else{
            insere_aux(this->tree.filhos[pos], info);
            this->tree = DataBase->getBMoreTree(node);
            Bmore father = this->tree;
            this->tree = DataBase->getBMoreTree(this->tree.filhos[pos]);//Recebe Filho
            if(overflow(this->tree)){//Overflow no filho
                Key m;
                int aux;
                if(eh_folha(this->tree))//Se o Filho eh folha
                    aux = splitfolha(&m, father.myPos);
                else
                    aux = split(&m, father.myPos);

                this->DataBase->setBMoreTree(this->tree);//Filho
                this->tree = father;                
                adicionaNaDireita(pos, m, aux);
                this->DataBase->setBMoreTree(this->tree);
            }
        }        
    }else
        printf("%d ja esta na arvore\n", info.key);
}



/*
## Função pricipal para inserção de elementos na arvore
Pré-condição:	arquivo iniciado
Pós-condição:	dados inseridos
*/
void BMTREE::insert(book info){
    headtree h = DataBase->getHeadTree();
    this->pos = h.root;
    if(this->pos == -1){
        this->create();
        this->tree.chaves[0].id = info.key;
        this->tree.chaves[0].pos = this->DataBase->setBookData(info);
        this->tree.numchaves = 1;
        this->tree.myPos = 0;
        h.top = h.top + 1;
        h.root = 0;
        DataBase->setBMoreTree(this->tree);
        DataBase->setHeadTree(h);
    }
    else{
        insere_aux(this->pos, info);
        this->tree = DataBase->getBMoreTree(this->pos);
        if(overflow(this->tree)){
        	Key m;
        	int newRight;
            Bmore newRoot;

        	newRoot.myPos = this->DataBase->getNextPosition("Tree");

        	if(eh_folha(this->tree))
                newRight = splitfolha(&m, newRoot.myPos);
            else
                newRight = split(&m, newRoot.myPos);

            int aux;
            aux = this->tree.myPos;
            this->tree.myPos = newRoot.myPos;
            newRoot.myPos = aux;


            newRoot.chaves[0] = m;
            newRoot.numchaves = 1;
            newRoot.filhos[0] = this->tree.myPos;
            newRoot.filhos[1] = newRight;

            DataBase->setBMoreTree(this->tree);
            DataBase->setBMoreTree(newRoot);
        }
    }
}


/*
## Prepara um nó novo para uso
Pré-condição:   nenhuma
Pós-condição:   todos os dados zerados
*/
void BMTREE::create(){
    int i;    
    for(i = 0;i< ORDEM + 1;i++)
        this->tree.filhos[i] = -1;

    for(i = 0;i < ORDEM;i++)
        this->tree.chaves[i].pos = -1;

    this->tree.pai = this->tree.numchaves = this->tree.eh_folha = this->tree.myPos = -1;
    
}


/*
## Diz se o nó é folha
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
int BMTREE::eh_folha(Bmore r){
    return (r.filhos[0] == -1);
}


/*
## diz de o nó está em overflow
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
int BMTREE::overflow(Bmore r){
    return (r.numchaves == ORDEM);
}



/*
## Imprime um no da arvore
Pré-condição:	nenhuma
Pós-condição:	nenhuma
*/
void BMTREE::imprimeNo(Bmore a){
    int i;
    cout << "[" ;
    for(i = 0; i < a.numchaves;i++){
        cout << a.chaves[i].id;
        if(i+1 != a.numchaves)
            cout << " ";
    }
    cout << "]";
}

/*
## imprime todos todos os elementos de um nivel da arvore
Pré-condição:	arvore valida, arquivo iniciado
Pós-condição:	nenhuma
*/
void BMTREE::imprimeNiveis(int node, int n){
    
    if(node != -1){
    	Bmore aux = this->DataBase->getBMoreTree(node);
        if(n == 0){
        	this->imprimeNo(aux);           
        }
        else{
            int i;
            for(i = 0;i <= aux.numchaves;i++){
                imprimeNiveis(aux.filhos[i], n-1);
            }
            
        }
        
    }
}


/*
## Retorna altura da arvore
Pré-condição:	arquivo iniciado
Pós-condição:	nenhuma
*/
int BMTREE::altura(int node){
	if(node != -1){
	    Bmore aux = this->DataBase->getBMoreTree(node);
	    int i = 0;
	    while(aux.filhos[0] != - 1){
	        aux = this->DataBase->getBMoreTree(aux.filhos[0]);
	        i++;
	    }
	    return i + 1;
	}
	return 0;
}


/*
## Imprime todos os niveis da arvore
Pré-condição:	arquivo iniciado
Pós-condição:	nenhuma
*/
void BMTREE::imprimearvore(){
	headtree aux = this->DataBase->getHeadTree();
	int n = this->altura(aux.root);
    int i;
    for(i = 0;i < n;i++){
        imprimeNiveis(aux.root,i);
        cout << endl;
    }
    

}