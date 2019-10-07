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

#include "bmoretree.h"

BMTREE * BMTREE::instanceBMTREE = NULL;


/*
## Destrutor da classe BMTREE
Pré-condição:   nenhuma 
Pós-condição:   nenhuma
*/
BMTREE * BMTREE::getInstance(){
    if(instanceBMTREE == NULL)
        instanceBMTREE = new BMTREE();
    return instanceBMTREE;
}


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
    int irmao = this->tree.filhos[ORDEM];
    Bmore aux = this->tree;
    
	int newPos = this->DataBase->getNextPosition("Tree");
	this->create();
    this->tree.pai = pai;
    aux.pai = pai;
    this->tree.myPos = newPos;
	
	int q = aux.numchaves/2;
    this->tree.numchaves = aux.numchaves - q;
    aux.numchaves = q;
    *m = aux.chaves[q];

    int i = 0;
    for(i = 0; i <= aux.numchaves;i++){
        this->tree.chaves[i] = aux.chaves[q+i];
    }
    aux.filhos[ORDEM] = newPos;
    this->tree.filhos[ORDEM] = irmao;
    this->tree.eh_folha = 1;
    aux.eh_folha = 1;
    this->DataBase->setBMoreTree(this->tree);
    this->tree = aux;
    //this->tree.filhos[q] = newPos;

    return newPos;
}


/*
## Atualiza pai de todos os filho de um no
Pré-condição:   arquivo iniciado
Pós-condição:   pai dos nós atualizado
*/
void BMTREE::updateFather(Bmore aux){
    int fatherPos = aux.myPos;
    Bmore son;
    int i;
    for(i = 0;i <= aux.numchaves; i++){
        son = this->DataBase->getBMoreTree(aux.filhos[i]);
        son.pai = fatherPos;
        this->DataBase->setBMoreTree(son);
    }
}
/*
## Split de um nó não folha
Pré-condição:	arquivo iniciado, no com overflow
Pós-condição:	no divido, irmao criado, key alterado
*/
int BMTREE::split(Key * m, int pai){
    Bmore aux = this->tree;
    int newPos = this->DataBase->getNextPosition("Tree");
    int i = 0;
    int q;

    this->create();
    this->tree.pai = pai;    
    this->tree.myPos = newPos;
    aux.pai = pai;

    q = aux.numchaves/2;
    this->tree.numchaves = aux.numchaves - q - 1;
    aux.numchaves = q;
    *m = aux.chaves[q];
    
    this->tree.filhos[0] = aux.filhos[q+1];
    for(i = 0; i < aux.numchaves; i++){
        this->tree.chaves[i] = aux.chaves[q+1+i];
        this->tree.filhos[i + 1] = aux.filhos[q+2+i]; 
    }

    this->updateFather(this->tree);
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
## Adiciona uma key a direita de um nó não folha
Pré-condição:   arquivo iniciado
Pós-condição:   chave inserida no nó
*/
void BMTREE::adicionaNaDireita(int pos, Key info){
    int i; 
    for(i = this->tree.numchaves;i>pos;i--){
        this->tree.chaves[i] = this->tree.chaves[i-1];
    }
    this->tree.chaves[pos] = info;
    this->tree.numchaves++;
}

/*
## Adicona chave a direita de um nó folha, insere dados do livro no arquivo
Pré-condição:	arquivos iniciados
Pós-condição:	chave adiciona no nó, arquivo de dados alterado
*/
void BMTREE::adicionaNaDireita(int pos, book info, int filho){
    int i; 
    for(i = this->tree.numchaves;i>pos;i--){
        this->tree.chaves[i] = this->tree.chaves[i-1];
    }

    this->tree.chaves[pos].id = info.key;
    this->tree.chaves[pos].pos = this->DataBase->setBookData(info);
    this->tree.numchaves++;    
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
    int pos = h.root;
    if(pos == -1){
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
        insere_aux(pos, info);
        this->tree = DataBase->getBMoreTree(pos);
        if(overflow(this->tree)){
        	Key m;
        	int newRight;
            Bmore newRoot;

            newRoot = newBmore();
        	newRoot.myPos = this->DataBase->getNextPosition("Tree");

        	if(eh_folha(this->tree))
                newRight = splitfolha(&m, this->tree.myPos);
            else
                newRight = split(&m, this->tree.myPos);

            int aux;
            aux = this->tree.myPos;
            this->tree.myPos = newRoot.myPos;
            newRoot.myPos = aux;


            newRoot.chaves[0] = m;
            newRoot.numchaves = 1;
            newRoot.filhos[0] = this->tree.myPos;
            newRoot.filhos[1] = newRight;

            this->updateFather(this->tree);
            DataBase->setBMoreTree(this->tree);
            DataBase->setBMoreTree(newRoot);
        }
    }
}


/*
## Prepara o no principal para uso
Pré-condição:   nenhuma
Pós-condição:   todos os dados zerados
*/
void BMTREE::create(){
    int i;    
    for(i = 0;i< ORDEM + 1;i++)
        this->tree.filhos[i] = -1;

    for(i = 0;i < ORDEM;i++)
        this->tree.chaves[i].pos = -1;

    this->tree.numchaves = 0;
    this->tree.eh_folha = 0;
    this->tree.pai = this->tree.myPos = -1;
    
}


/*
## Prepara um nó novo para uso
Pré-condição:   nenhuma
Pós-condição:   todos os dados zerados
*/
Bmore BMTREE::newBmore(){
    int i; 
    Bmore tree;   
    for(i = 0;i< ORDEM + 1;i++)
        tree.filhos[i] = -1;

    for(i = 0;i < ORDEM;i++)
        tree.chaves[i].pos = -1;

    tree.numchaves = 0;
    tree.eh_folha = 0;
    tree.pai = tree.myPos = -1;
    return tree;
    
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
## imprime todos todos os elementos de um nó da arvore
Pré-condição:   arvore valida, arquivo iniciado
Pós-condição:   nenhuma
*/
void BMTREE::Debug(Bmore a){
    int i;
    
    cout << "[" ;

    
    cout << "myPos: " << a.myPos << " ";
    cout << "Pai: " << a.pai << " ";

    
    cout << " " << "Filhos: [";    
    for(i = 0;i<= ORDEM;i++)
            cout << " " << a.filhos[i] << " ";
    
    cout << "]  Chaves: ";
    for(i = 0; i < a.numchaves;i++){
        cout << a.chaves[i].id;
        if(i+1 != a.numchaves)
            cout << " ";
    }


    cout << " " << "Numchaves: " << a.numchaves;
        cout << "]";
}

/*
## imprime todos todos os nós de um nivel da arvore
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


/*
## Auxulia na procura de um livro na arvore
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
book BMTREE::search_aux(int pos, int key){
    book a;
    if(pos != -1){
        int i;
        Bmore aux = this->DataBase->getBMoreTree(pos);
        for(i = 0; i < aux.numchaves; i++){
            if(aux.chaves[i].id == key)
                return this->DataBase->getBookData(aux.chaves[i].pos);

            if(key < aux.chaves[i].id)
                return search_aux(aux.filhos[i], key);
        }
        return search_aux(aux.filhos[aux.numchaves], key);
    }else{        
        a.key = -1;
        return a;
    }
}

/*
## Procura Um livro na arvore
Pré-condição:   arquivo iniciado
Pós-condição:   nenhuma
*/
book BMTREE::searchBook(int chave){
    int root = this->DataBase->getHeadTree().root;
    return this->search_aux(root, chave);
}



/*
## Atualiza qtd de exemplares de um livro
Pré-condição:   arquivo iniciado
Pós-condição:   retorna se foi alterado ou nao
*/
int BMTREE::updateNumberofBooks(int key, int newNumber){
    book a = searchBook(key);
    if (a.key != -1){
        a.nExamples = newNumber;
        this->DataBase->setBookData(a);
        return 1;
    }
    return 0;

}


/*
## Imprime Conteudo das folhas
Pré-condição:   arquivo iniciado
Pós-condição:   nenhuma
*/
void BMTREE::printKeys(){
    int rootPos = this->DataBase->getHeadTree().root;
    if(rootPos != -1){
        Bmore aux = this->DataBase->getBMoreTree(rootPos);

        while(aux.filhos[0] != -1){
            aux = this->DataBase->getBMoreTree(aux.filhos[0]);
         }
    
        this->imprimeNo(aux);
        while(aux.filhos[ORDEM] != -1){
            aux = this->DataBase->getBMoreTree(aux.filhos[ORDEM]);
            this->imprimeNo(aux);
        }
    }
    
}


/*
## Imprime Acervo
Pré-condição:   arquivo iniciado
Pós-condição:   nenhuma
*/
void BMTREE::printBooks(){
    int rootPos = this->DataBase->getHeadTree().root;
    if(rootPos != -1){
        Bmore aux = this->DataBase->getBMoreTree(rootPos);

        while(aux.filhos[0] != -1){
            aux = this->DataBase->getBMoreTree(aux.filhos[0]);
         }
    
        this->printNodeBook(aux);
        while(aux.filhos[ORDEM] != -1){
            aux = this->DataBase->getBMoreTree(aux.filhos[ORDEM]);
            this->printNodeBook(aux);
        }
    }
}

/*
## Imprime todos os livros de um nó
Pre-condição:   arquivo aberto
Pós-condição:   livro do impressos na tela
*/
void BMTREE::printNodeBook(Bmore a){
    int i;
    for(i = 0; i < a.numchaves;i++)
        this->printOneBook(this->DataBase->getBookData(a.chaves[i].pos));
}

/*
##  Imprime um livro
Pre-condição:   nenhuma
Pós-condição:   livro impreso na tela
*/
void BMTREE::printOneBook(book l){
    cout << "                                            \u258C";
    cout << "Titulo: " << l.title << endl;
    cout << "                                            \u258C";
    cout << "Autor: " << l.author << endl;
    cout << "                                            \u258C";
    cout << "Chave: " << l.key << endl;
    cout << "                                            \u258C";
    cout << "N de Exemplares: " << l.nExamples << endl << endl;
}


/*
## Carrega dados do arquivo txt
Pré-condição:   arquivo existente, aquivo binario inicializado
Pós-condição:   dados carregados em arquivo binario
*/
int BMTREE::insertViaFile(char * _file){
    FILE * f = fopen(_file, "r");
    if(f == NULL)return 0;
    int chave;
    char temp[300];
    book  l;

    while(!feof(f)){
        fscanf(f, "%d%*c", &l.key);
        fscanf(f,"%[^;]%*c", l.title);
        fscanf(f,"%[^;]%*c", l.author);
        fscanf(f, "%d%*r", &l.nExamples);
        l.myPos = -1;
        this->insert(l);
    }    
    fclose(f);
    return 1;


}


/*
## Deleta uma chave na folah
Pré-condição:   no carregado em this->tree
Pós-condição:   chave removida, caso exista
*/
void BMTREE::delete_folha(int key){
    int pos;
    if(buscaPos(key, &pos)){
        int i;
        this->DataBase->freeThisBook(this->tree.chaves[pos].pos);
        for(i = pos;i < this->tree.numchaves;i++){
            this->tree.chaves[i] = this->tree.chaves[i+1];
        }
        this->tree.numchaves--;

    }
}


/*
## atuliza raiz do cabeçalho
Pré-condição:   nenhuma
Pós-condição:   nenhuma
*/
void BMTREE::updateRoot(int pos){
    headtree aux = this->DataBase->getHeadTree();
    aux.root = pos;
    this->DataBase->setHeadTree(aux);
}



/*
## Retorna a menor chave da arvore
Pré-condição:   arvore nao nula
Pós-condição:   nenhuma
*/
Key BMTREE::smaller(int pos){
    Bmore aux = this->DataBase->getBMoreTree(pos);
    while(aux.filhos[0] != -1){
        aux = this->DataBase->getBMoreTree(aux.filhos[0]);
    }
    return aux.chaves[0];
}

/*
## Atualiza todos os índices de um nó 
Pré-condição:   nenhuma 
Pós-condição:   nenhuma
*/
void BMTREE::updateIndex(){
    int i;
    for(i = 0;i < this->tree.numchaves;i++){
        this->tree.chaves[i] = smaller(this->tree.filhos[i+1]);
    }
}


/*
## Função principal paradeletar uma chave da arvore
Pré-condição:   nenhuma
Pós-condição:   chave eliminada,caso exista 
*/
void BMTREE::deleteKey(int key){
    int root = this->DataBase->getHeadTree().root;
    if(root != -1){
        this->tree = this->DataBase->getBMoreTree(root);
        if(eh_folha(this->tree)){
            delete_folha(key);
            if(this->tree.numchaves == 0)
                this->DataBase->clearAll();
            else
                this->DataBase->setBMoreTree(this->tree);

        }else{
            this->delete_aux(root, key);
            this->tree = this->DataBase->getBMoreTree(root);
            if(this->tree.numchaves == 0){
                this->DataBase->freeThisTree(this->tree.myPos);
                this->tree = this->DataBase->getBMoreTree(this->tree.filhos[0]);
                updateIndex();
                this->DataBase->setBMoreTree(this->tree);
                updateRoot(this->tree.myPos);
            }
        }        

    }
}


/*
## Retorna a posicao do filho em que deve-se remover uma chave
Pré-condição:   nenhuma
Pós-condição:   nenhume
*/
int BMTREE::newSearch(int key){
    int i;
    for(i = 0;i < this->tree.numchaves;i++){
        if(key < this->tree.chaves[i].id)
            break;
    }
    return i;
}


/*
## Faz merge em nó folha
Pré-condição:   folha com underflow
Pós-condição:   irmao e pai modificado
*/
void BMTREE::mergeFolha(int paiPos, int pos){
    int irmao;
    
    Bmore esquerda, pai, direita;
    pai = this->DataBase->getBMoreTree(paiPos);

    if(pos > 0){
        esquerda = this->DataBase->getBMoreTree(pai.filhos[pos-1]);
        direita = this->DataBase->getBMoreTree(pai.filhos[pos]);
    }
    else{
        esquerda = this->DataBase->getBMoreTree(pai.filhos[pos]);
        direita = this->DataBase->getBMoreTree(pai.filhos[pos+1]);
        pos++;
    }

    irmao = direita.filhos[ORDEM];
    int i;
    this->tree = esquerda;
    for(i = 0; direita.numchaves > 0;i++){
        adicionaNaDireita(this->tree.numchaves, direita.chaves[i],  NULL); 
        direita.numchaves--;  
    }
    for(i = pos;i < pai.numchaves;i++){
        pai.filhos[i] = pai.filhos[i+1];
    }
    pai.numchaves--;

    this->tree.filhos[ORDEM] = irmao;
    this->DataBase->setBMoreTree(this->tree);//esquerda
    this->DataBase->setBMoreTree(pai);//pai
    this->DataBase->setBMoreTree(direita);//direita
    this->DataBase->freeThisTree(direita.myPos);

}


/*
## Fazz merge em no
Pré-condição:   filho com underflow
Pós-condição:   nenhuma
*/
void BMTREE::mergeNo(int paiPos, int pos){
    
    Bmore esquerda, pai, direita;

    pai = this->DataBase->getBMoreTree(paiPos);

    if(pos > 0){
        direita = this->DataBase->getBMoreTree(pai.filhos[pos]);
        esquerda = this->DataBase->getBMoreTree(pai.filhos[pos - 1]);
    }else{
        direita = this->DataBase->getBMoreTree(pai.filhos[pos + 1]);
        esquerda = this->DataBase->getBMoreTree(pai.filhos[pos]);
    }

    if(pos > 0){
        this->tree = esquerda;
        adicionaNaDireita(this->tree.numchaves, pai.chaves[pos - 1], -1);
        esquerda = this->tree;

        this->tree = pai;
        delete_folha(pai.chaves[pos - 1].id);
        pai = this->tree;

        int i;
        for(i = pos; i < pai.numchaves;i++)
            pai.filhos[i] = pai.filhos[i+1];
        
        this->DataBase->setBMoreTree(pai);//grava o pai

        for(i = 0;i < direita.numchaves;i++){
            esquerda.chaves[esquerda.numchaves] = direita.chaves[i];
            esquerda.filhos[esquerda.numchaves] = direita.filhos[i];
            esquerda.numchaves++;
        }
        esquerda.filhos[esquerda.numchaves] = direita.filhos[i];

        this->DataBase->setBMoreTree(esquerda);//esquerda
        this->DataBase->setBMoreTree(direita);//direita
    }else{
        this->tree =  esquerda;
        adicionaNaDireita(this->tree.numchaves, pai.chaves[pos], direita.filhos[0]);
        esquerda = this->tree;

        this->tree = pai;
        delete_folha(pai.chaves[pos].id);
        pai = this->tree;

        int i;
        for(i = pos+1;i < pai.numchaves;i++)
            pai.filhos[i] = pai.filhos[i+1];

        this->DataBase->setBMoreTree(pai);//grava o pai

        for(i = 0;i < direita.numchaves;i++){
            esquerda.chaves[esquerda.numchaves] = direita.chaves[i];
            esquerda.filhos[esquerda.numchaves] = direita.filhos[i];
            esquerda.numchaves++;
        }
        esquerda.filhos[esquerda.numchaves] = direita.filhos[i];

        this->DataBase->setBMoreTree(esquerda);//grava esquerda
        this->DataBase->setBMoreTree(direita);//grava direita
    }

}

/*
## Faz rotação em nó de indice
Pré-condição:   filho em pos com underflow
Pós-condição:   nenhuma
*/
int BMTREE::rotation(int paiPos, int pos){

    Bmore esquerda, pai, direita, meio;
    pai = this->DataBase->getBMoreTree(paiPos);
    meio = this->DataBase->getBMoreTree(pai.filhos[pos]);


    if(pos > 0){
        esquerda = this->DataBase->getBMoreTree(pai.filhos[pos - 1]);
        if(esquerda.numchaves > (ORDEM/2)){
            this->tree = meio;
            adicionaNaDireita(0, pai.chaves[pos - 1]);
            meio = this->tree;

            pai.chaves[pos - 1] = esquerda.chaves[esquerda.numchaves - 1];
            int i;
            for(i = meio.numchaves;i > 0;i--)
                meio.filhos[i] = meio.filhos[i-1];
            meio.filhos[0] = esquerda.filhos[esquerda.numchaves];

            this->tree = esquerda;
            delete_folha(this->tree.chaves[this->tree.numchaves - 1].id);
            esquerda = this->tree;

            this->DataBase->setBMoreTree(esquerda);//grava esquerda
            this->tree = meio;
            updateIndex();
            meio = this->tree;
            this->DataBase->setBMoreTree(meio);//grava meio
            this->DataBase->setBMoreTree(pai);//grava pai

            return 1;
        }
    }else if(pos <= pai.numchaves){
        direita = this->DataBase->getBMoreTree(pai.filhos[pos + 1]);
        if(direita.numchaves > (ORDEM/2)){
            this->tree = meio;
            adicionaNaDireita(this->tree.numchaves, pai.chaves[pos], -1);
            meio = this->tree;

            pai.chaves[pos] = direita.chaves[0];
            meio.filhos[meio.numchaves] = direita.filhos[0];

            int i;
            for(i = 0;i < direita.numchaves;i++){
                direita.filhos[i] = direita.filhos[i+1];
            }
            this->tree = direita;
            delete_folha(pai.chaves[pos].id);
            direita = this->tree;

            this->DataBase->setBMoreTree(direita);//grava direita
            this->tree = meio;
            updateIndex();
            meio = this->tree;
            this->DataBase->setBMoreTree(meio);//grava meio
            this->DataBase->setBMoreTree(pai);//grava pai
            return 1;
        }
    }
    return 0;
}



/*
## Faz emprestimos com irmao de uma folha
Pré-condição:   folha con underflow
Pós-condição:   qtd minima respeitada na folha
*/
int BMTREE::emprestaFolha(int paiPos, int pos){
    Bmore esquerda, pai, direita, meio;
    bool flagEsquerda, flagDireita;
    flagEsquerda = flagDireita = true;
    pai = this->DataBase->getBMoreTree(paiPos);
    meio = this->DataBase->getBMoreTree(pai.filhos[pos]);

    if(pos > 0)
        esquerda = this->DataBase->getBMoreTree(pai.filhos[pos - 1]);
    else
        flagEsquerda = false;

    if(pos < pai.numchaves)
        direita = this->DataBase->getBMoreTree(pai.filhos[pos + 1]);
    else 
        flagDireita = false;

    this->tree = meio;

    if(flagEsquerda && esquerda.numchaves > (ORDEM/2)){

        adicionaNaDireita(0, esquerda.chaves[esquerda.numchaves - 1], -1);
        meio = this->tree;
        this->tree = esquerda;
        delete_folha(esquerda.chaves[esquerda.numchaves - 1].id);

        this->DataBase->setBMoreTree(this->tree);//esqueda
        this->DataBase->setBMoreTree(meio);//meio
        return 1;

    }else if( flagDireita && direita.numchaves > (ORDEM/2)){
        
        adicionaNaDireita(meio.numchaves, direita.chaves[0], NULL);
        meio = this->tree;
        this->tree = direita;
        delete_folha(direita.chaves[0].id);
        
        this->DataBase->setBMoreTree(this->tree);//direita
        this->DataBase->setBMoreTree(meio);//meio
        return 1;
    }
    return 0;
}




/*
## Remove chaves que nao estejam na raiz
Pré-condição:   no nao vazio
Pós-condição:   nenhuma
*/
void BMTREE::delete_aux(int node, int key){
    int pos;
    this->tree = this->DataBase->getBMoreTree(node);
    pos = newSearch(key);
    if(eh_folha(this->tree)){
        delete_folha(key);
        this->DataBase->setBMoreTree(this->tree);
    }else{
        this->delete_aux(this->tree.filhos[pos], key);
        this->tree = this->DataBase->getBMoreTree(node);
        Bmore filho = this->DataBase->getBMoreTree(this->tree.filhos[pos]);
        if(filho.numchaves < (ORDEM/2)){
            if(eh_folha(filho)){
                if(!emprestaFolha(this->tree.myPos, pos)){
                    this->tree = this->DataBase->getBMoreTree(node);
                    mergeFolha(this->tree.myPos, pos);
                }
            }else{                
                if(!rotation(this->tree.myPos, pos)){
                    this->tree = this->DataBase->getBMoreTree(node);
                    mergeNo(this->tree.myPos, pos);

                }                
            }
        }
        this->tree = this->DataBase->getBMoreTree(node);
        updateIndex();
        this->DataBase->setBMoreTree(this->tree);
    }
}