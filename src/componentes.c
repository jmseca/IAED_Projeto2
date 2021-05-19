/*
 * Ficheiro: componentes.c
 * Autor: Joao Fonseca
 * Descricao: Definicao das funcoes que vao manipular
 * os componentes, bem como as estruturas que formam e guardam os componentes.
*/

#include "proj2.h"
 
/* ============================================================================
 * Componentes
 *
 * -char* nome
 * -char* valor
 * -unsigned long occ
 * -unsigned long alfaHeight
 * -unsigned long orderHeight
 * -componente* alfaRight
 * -componente* alfaLeft
 * -componente* orderRight
 * -componente* orderLeft
 * -AVLhead* follow (componentes seguintes)
 ============================================================================*/


/* ============================================================================
 * avlHead
 *
 * -unsigned long occ
 * -componente* rootAlfa (avl ordenada alfabeticamente)
 * -componente* rootOrder (avl ordenada por criacao)
 ============================================================================*/


avlHead* initHead(mother* M){
	avlHead* head;
	head = (avlHead*) myMalloc(AVLHEAD,ONE,M);
       	head->occ = ZERO;
	head->rootAlfa = NULL;
	head->rootOrder = NULL;
	return avlHead 
}

comp* initComp(char *path, unsigned short start,unsigned short end,mother* M){
	comp* c1;
	unsigned int vSize = end-start+ONE;
	c1 = (comp*) myMalloc(COMP,ONE,M);
	c1->nome = (char*) myMalloc(ONE,vSize,M);
	c1->valor = (char*) myMalloc(ONE,ONE,M);
	/*Refazer o malloc*/
	c1->alfaRight = NULL;
	c1->alfaLeft = NULL;
	c1->orderRight = NULL;
	c1->orderLeft = NULL;
	c1->occ = ZERO;
	c1->alfaHeight = ZERO;
	c1->orderHeight = ZERO;
	*(c1->valor) = ZERO;
	myStrCpy(c1->nome,path,start,end);
	return c1;
	
}

/* Inicializa um ponteiro para um componente, alocando-lhe alguma memoria*/
comp* initComp(char* path, unsigned short start, unsigned short end){
        comp* c1;
        short i,size;
        size = end-start+1; /*tamanho do nome da componente em analise*/
        c1 = (comp*) malloc(sizeof(comp));
	/* Atribuir um nome*/
        c1->nome = (char*) malloc(sizeof(char)*size);
        myStrCpy(c1->nome,path,start,end); 
	/* Inicial o valor a Nulo*/
        c1->valor = (char*) malloc(sizeof(char));
        *(c1->valor) = '\0';
	c1->right = NULL; 
	c1->left = NULL; /*Nao ha valores ainda para as componentes seguintes*/
	/* Alocar memoria para as componentes ordenadas alfabeticamente*/
        c1->alfabeta = initVpc(FIRST_SIZE_C);
        /* Memoria para as componentes ordenadas por criacao*/
        c1->first = initVpc(FIRST_SIZE_C);
        return c1;
}

/* 0->str
 * 1->order*/
comp* findComp(avlHead *head, char* path,char* found, char modo, unsigned short start,
		unsigned end end, mother *M){
	comp* c2 = modo ? head->rootOrder : head->rootAlfa;
	short res;
	while (!found && c2!=NULL){
		res = myStrCmp(path,c2->nome,start,end);
		if (!res){
			*found = 1
		} else {
			if (modo){
			
			} else {
		
			}
		}
	}

	
}


/* Funcao que inicializa um vpc, alocando-lhe memoria*/
vpc* initVpc(short firstSize){
	vpc* vetor;
	vetor = (vpc*) malloc(sizeof(vpc));
	vetor->info = (comp**) malloc((firstSize)*sizeof(comp*));
	vetor->size = (unsigned long*) malloc(sizeof(unsigned long));
	vetor->occ = (unsigned long*) malloc(sizeof(unsigned long));
	*(vetor->size) = firstSize;
	*(vetor->occ) = 0;
	return vetor;
}


/* Funcao auxiliar do binarySearch que devolve o proximo
 *indice a verificar e atualiza o valor da
 *variavel size (atraves do uso de pointer)*/
unsigned long getBinInd(unsigned long *size, unsigned long ind,
	       	short up, unsigned long maxInd){
        unsigned long soma;
        soma = *size/2;
        *size = *size%2 ? (*size/2)+1 : *size/2;
        if (up){
                ind += soma;
        } else {
                ind = ind>soma ? ind-soma : soma-ind;
        }
        return ind<maxInd ? ind : ind-1;
}


/* Devolve o valor que resulta de comparar o nome do componente em analise 
 *com o que se quer comparar*/
short getBinRes(char *cName, vpc *vetor, long ind,unsigned short start, 
		unsigned short end){
        short out; 
        out = myStrCmp(cName,vetor->info[ind]->nome,start,end);
	return out;
}



/* Funcao de procura e insercao binaria responsavel por devolver
 *o indice pretendido (que seja para encontrar ou inserir)*/
unsigned long binarySearch(char *cName, vpc *vetor, short *found,
		unsigned short start, unsigned short end){
        short up=1;
        short res=0;
	unsigned long size = *(vetor->occ);
	unsigned long ind=0;
        unsigned long maxInd = *(vetor->occ);
	if (size){
                size += size%2 ? 0 : 1;
                do {
                        ind = getBinInd(&size, ind, up, maxInd);
                        res = getBinRes(cName, vetor, ind,start,end);
                        if (!res){
                                *found=1;
                        }
                        up = res>0 ? 1 : 0;
                } while (size!=1 && !(*found));
        }
        if (ind<maxInd && !found){
                ind = res>0 ? ind+1 : ind;
        }
        return ind;
}

/*Adiciona a nova componente ao vpc*/
void updateVpc(comp *c1, vpc *vetor, unsigned long ind){
	unsigned long i;
	for (i=*(vetor->occ);i>ind;--i){
		vetor->info[i] = vetor->info[i-1];
	}
	vetor->info[ind] = c1;
	(*(vetor->occ))++;
}

/*Aumenta o numero de ponteiros de componentes que pode albergar*/
vpc* extendVpc(vpc *vetor){
	unsigned long newSize = *(vetor->size)*(1.5);
	vpc *vetor2;
	vetor2 = (vpc*) malloc(sizeof(vpc));
	vetor2->info = (comp**) realloc(vetor->info,sizeof(comp*)*newSize);
	*(vetor2->size) = newSize;
	vetor2->occ = vetor->occ;
	free(vetor->size);
	free(vetor->occ);
	free(vetor);
	return vetor2;
}

/* Adiciona um novo elemento a um vpc da Tabela de Dispersao
 * (ordenado alfabeticamente)*/
void addToAlfaVpc(comp* cNew,vpc* vetor,unsigned long ind){
	if (*(vetor->size)==*(vetor->occ)){
		vetor = extendVpc(vetor);
	}
	updateVpc(cNew,vetor,ind);
}

/* Adiciona um novo elemento a um vpc no indice "ind"*/
void addToFVpc(comp* cNew, vpc* vetor, unsigned long ind){
	if (*(vetor->size)==*(vetor->occ)){
                vetor = extendVpc(vetor);
        }
	updateVpc(cNew,vetor,*(vetor->occ));
}


/* Inicializa um ponteiro para um componente, alocando-lhe alguma memoria*/
comp* initComp(char* path, unsigned short start, unsigned short end){
	comp* c1;
	short i,size;
	size = end-start+1; /*tamanho do nome da componente em analise*/
	c1 = (comp*) malloc(sizeof(comp));
	/* Atribuir um nome*/
	c1->nome = (char*) malloc(sizeof(char)*size);
	myStrCpy(c1->nome,path,start,end);
	/* Inicial o valor a Nulo*/
	c1->valor = (char*) malloc(sizeof(char));
	*(c1->valor) = '\0';
	/* Alocar memoria para as componentes ordenadas alfabeticamente*/
	c1->alfabeta = initVpc(FIRST_SIZE_C);
	/* Memoria para as componentes ordenadas por criacao*/
	c1->primeiros = initVpc(FIRST_SIZE_C);
	return c1;
}

/*Inicializa um ponteiro para a componente raiz
 *Apesar de ser parecido com initComp, nao e necessario args
 *Para iniciar uma root, dai a escolha de uma nova funcao*/
comp* initRoot(){
	comp* c1;
        short i;
	/*Nome e val da raiz dao jeito no comando print*/
        c1 = (comp*) malloc(sizeof(comp));
	c1->nome = (char*) malloc(sizeof(char));
	*(c1->nome) = '\0'; 
	c1->valor = (char*) malloc(sizeof(char));
	*(c1->valor) = '\0';
        /* Alocar memoria para as componentes ordenadas alfabeticamente*/
        c1->alfabeta = initVpc(FIRST_SIZE_C);
	/* Memoria para as componentes ordenadas por criacao*/
        c1->primeiros = initVpc(FIRST_SIZE_C);
        return c1;
}


/* Atribui um novo valor a uma componente*/
void compNewValue(comp* c1, char* val){
	size_t dim = strlen(val);
	dim++; /*incluir espaco para '\0'*/
	c1->valor = (char*) realloc(c1->valor,dim*(sizeof(char)));
	strcpy(c1->valor,val);

}

/* Adiciona uma nova componente a "c1" e devolve um ponteiro para
 *a nova componente criada. 
 * Ja se recebe o vpc e respetivo ind da tabela de dsipersao 
 *onde vamos adicionar*/
comp* addNewComp(comp *c1, char* path, unsigned long ind,
		unsigned short start, unsigned short end){
	comp* cNew;
	cNew = initComp(path,start,end);
	addToAlfaVpc(cNew,c1->alfabeta,ind); 
	addToFirstVpc(cNew,c1->primeiros);
	return cNew;
}



/* Verifica se a componente que tem o nome em "path", limitada por start e end
 * esta nos componentes seguintes de "c1"
 * modo '0', se nao esta, cria uma nova componente e adiciona-la
 * modo '1', se nao esta termina o programa.O aviso e transmitido pelo found*/
comp* belongsToComp(comp *c1, char *path, short *found,
		unsigned short start, unsigned short end, short modo){
	unsigned long ind;
	comp* out; /* A devolver*/
	vpc *vetor;
	ind = hashFun(path,start);
	vetor = c1->hash[ind];
	ind = binarySearch(path,vetor,found,start,end);
	if (*found){
		out = vetor->info[ind];
	} else if (!modo){
		out = addNewComp(c1,path,vetor,ind,start,end);
	}
	return out;
}

/* Verifica se existe valor associado a componente*/
short compValNull(comp *c1){
	return (*(c1->valor))=='\0';
}

/* Verifica se a componente e a raiz ou nao*/
short isRoot(comp* c1){
	return (*(c1->nome))=='\0';
}

/*Imprime o valor de uma componente*/
void printCompVal(comp *c1){
	printf("%s\n",c1->valor);
}

/*Imprime o nome de uma componente*/
void printCompName(comp *c1){
	printf("%s\n",c1->nome);
}

/* Devolve ponteiro para a componente final do caminho
 * modo '0'-se o caminho nao existir, cria um novo
 * modo '1'-se nao existir, nao cria */
comp* getPathComp(char* path, comp* root, short modo, short* succ){
	unsigned short start=0,end;
	short found;
	pathClean(path,&start);
	while (*(path+start)!='\0'){
		found = 0;
		end = findSepar(path,start);
		root = belongsToComp(root, path, &found, start, end, modo);
		if (!found && modo){
			printf("not found\n");
			*succ = 0; 
			break;
		}
		start=end;
		pathClean(path,&start);
	}

	return root;
}





/* Liberta a memoria de um vpc, onde ja foi libertada
 *a memoria das componentes*/
void freeVpc(vpc* vetor){
	free(vetor->size);
	free(vetor->occ);
	free(vetor->info);
	free(vetor);
}

/* Liberta a memoria da Tabela de Dispersao de um Componente
 *sem libertar a memoria dos componentes associados*/
void freeHash(vpc** hash){
	short i;
	for (i=0;i<HASH_MAX;i++){
		freeVpc(hash[i]);
	}
	free(hash);

}


/* Liberta a memoria de uma componente*/
void freeComp(comp *c1){
	free(c1->valor);
	free(c1->nome);
	freeHash(c1->hash);
	freeVpc(c1->primeiros);
	free(c1);
}

/* Liberta a memoria da componente c1 e de todas as que lhe seguem*/
void freeCompRec(comp* c1){
	if (*(c1->primeiros->occ)==0){ /*se nao ha componentes que lhe seguem*/
		freeComp(c1);
	} else {
		do {
			(*(c1->primeiros->occ))--; /* indice do ultimo colocado*/
			freeCompRec(c1->primeiros->info[*(c1->primeiros->occ)]);
		} while(*(c1->primeiros->occ)>0);
		freeComp(c1);
	}

}


/* Imprime os nomes das componentes associadas a um vpc*/
void printVpcComp(vpc* vetor){
	unsigned long i;
	for (i=0;i<(*(vetor->occ));i++){
		printCompName(vetor->info[i]);
	}
}

/* Imprime todos os componentes imediatos a "c1" por ordem alfabetica*/
void listComp(comp* c1){
	short i=0;
	for (;i<HASH_MAX;i++){
		printVpcComp(c1->hash[i]);
	}
}


/* Faz print de todos os valores associados a caminhos a 
 *partir do componenente "c1"*/
void printAll(comp* c1, buff* bf){	
	unsigned long ind=0;	
	if (!(compValNull(c1))){ /*se tem valor*/
		printf("%s/",bf->bigBuff); /*O caminho que esta para tras*/
		printf("%s ",c1->nome); /*nome da componente*/
		printf("%s\n",c1->valor); 
	}
	if (*(c1->primeiros->occ)){ /*Se tem componentes "filho"*/
		addToBuff(bf,c1);
		for(;ind<*(c1->primeiros->occ);ind++){
			printAll(c1->primeiros->info[ind],bf);
		}
		removeFromBuff(bf,c1);
	}
	
}
