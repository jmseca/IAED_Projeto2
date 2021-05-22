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

/* Inicializa uma avlHead*/
avlHead* initHead(char* control){
	avlHead* head;
	head = (avlHead*) myMalloc(AVLHEAD,ONE,control);
       	if (!control){ /*ha memoria*/
		head->occ = ZERO;
		head->rootAlfa = NULL;
		head->rootOrder = NULL;
	}
	return head; 
}


comp* initComp(mother* M){
	comp* c1;
	char control = ZERO;
	buff* bf = M->bf;
	unsigned int vSize = getVsize(bf);
	c1 = (comp*) myMalloc(COMP,ONE,&control);
	c1->nome = (char*) myMalloc(ONE,vSize,&control);
	c1->valor = (char*) myMalloc(ONE,ONE,&control);
	c1->follow = initHead(&control);
	if (control){ /* ja nao ha memoria*/
		freeComp(c1,ONE);
		endProgram(M);
	}
	c1->alfaRight = NULL;
	c1->alfaLeft = NULL;
	c1->orderRight = NULL;
	c1->orderLeft = NULL;
	c1->occ = getBuffOcc(M->bf); /* occ guardada no buffer*/
	c1->alfaHeight = ONE;
	c1->orderHeight = ONE;
	*(c1->valor) = ZERO;
	myStrCpy(c1->nome,bf);
	return c1;
}

mother* initMother(){
	char control=ZERO;
	mother* M = (mother*) malloc(sizeof(mother));
	M->bf = initBuffer();
	M->motherRoot = initHead(&control);
	return M;
}

/* Faz free a uma componente
 * modo 1 -> houve erro a alocar memoria da componente
 * modo 0 -> fazer free da componente normalmente*/
void freeComp(comp *c1, char modo){
	if (modo) { /*Se houve erro, pelo menos c1->follow e NULL*/
		if ((c1->valor)!=NULL){
			free(c1->valor);
		}
		if ((c1->nome)!=NULL){
			free(c1->nome);
		}
		free(c1);
	} else {
		printf("In a place it shouldn't be\n");
		/* free all fica para dps*/
	
	}
}



/* Devolve a height do componente da arvore desejada
 * modo 1->ordenada alfabeticamente
 * modo 0->ordenada por criacao*/
int height(comp* h, char modo){
        if (h == NULL) return 0;
	if (modo)
        	return h->alfaHeight;
	else
		return h->orderHeight;
}

/* Rotacao a esquerda na arvore pretendida (modo)*/
comp* rotL(comp* h, char modo){
        int hleft, hright, xleft, xright;
	comp* x;
	if (modo) {
		x = h->alfaRight;
        	h->alfaRight = x->alfaLeft;
        	x->alfaLeft = h;

        	hleft = height(h->alfaLeft,modo);
        	hright = height(h->alfaRight,modo);
        	h->alfaHeight = hleft > hright ? hleft + 1 : hright + 1;

        	xleft = height(x->alfaLeft,modo);
        	xright = height(x->alfaRight,modo);
		x->alfaHeight = xleft > xright ? xleft + 1 : xright + 1;
	} else {
		x = h->orderRight;
                h->orderRight = x->orderLeft;
                x->orderLeft = h;

                hleft = height(h->orderLeft,modo);
                hright = height(h->orderRight,modo);
                h->orderHeight = hleft > hright ? hleft + 1 : hright + 1;

                xleft = height(x->orderLeft,modo);
                xright = height(x->orderRight,modo);
		x->orderHeight = xleft > xright ? xleft + 1 : xright + 1;
	}
        return x;
}

/* Rotacao a esquerda na arvore pretendida (modo)*/
comp* rotR(comp* h, char modo){
        int hleft, hright, xleft, xright;
        comp* x;
	if (modo) {
		x = h->alfaLeft;
        	h->alfaLeft = x->alfaRight;
        	x->alfaRight = h;

        	hleft = height(h->alfaLeft,modo);
        	hright = height(h->alfaRight,modo);
        	h->alfaHeight = hleft > hright ? hleft + 1 : hright + 1;

        	xleft = height(x->alfaLeft,modo);
        	xright = height(x->alfaRight,modo);
		x->alfaHeight = xleft > xright ? xleft + 1 : xright + 1;
	} else {
		x = h->orderLeft;
                h->orderLeft = x->orderRight;
                x->orderRight = h;

                hleft = height(h->orderLeft,modo);
                hright = height(h->orderRight,modo);
                h->orderHeight = hleft > hright ? hleft + 1 : hright + 1;

                xleft = height(x->orderLeft,modo);
                xright = height(x->orderRight,modo);
        	x->orderHeight = xleft > xright ? xleft + 1 : xright + 1;
	}
        return x;
}



/* Devolve a componente maxima de uma AVL
 * modo 0 -> AVL por ordem de criacao
 * modo 1 -> AVL por ordem alfabetica*/
comp* max(comp* h, char modo){
	if (modo){
        	while (h!=NULL && ((h->alfaRight) != NULL)){
                	h = h->alfaRight;
        	}
	} else {
		while (h!=NULL && ((h->orderRight) != NULL)){
                        h = h->orderRight;
                }
	}
        return h;
}


/* Faz uma rotacao esquerda-direita, dependendo do modo como queremos fazer*/
comp* rotLR(comp* h,char modo){ 
        if (h == NULL){ 
		return h;
	}
	if (modo){
        	h->alfaLeft = rotL(h->alfaLeft,modo);
	} else {
		h->orderLeft = rotL(h->orderLeft,modo);
	}
        return rotR(h,modo);
}

/* Faz uma rotacao direita-esquerda, dependendo do modo como queremos fazer*/
comp* rotRL(comp* h, char modo){ 
        if (h == NULL){ 
		return h;
	}
	if (modo){
                h->alfaRight = rotR(h->alfaRight,modo);
        } else {
                h->orderRight = rotR(h->orderRight,modo);
        }
        return rotL(h,modo);
}

/* Balance factor, que tambem sera diferente, dependendo do modo*/
int balance(comp* h, char modo) {
        if(h == NULL){ 
		return 0;
	}
        return modo ? height(h->alfaLeft,modo) - height(h->alfaRight,modo) :\
	      	height(h->orderLeft,modo) - height(h->orderRight,modo);
}

/* Verifica se e necessario fazer rotates numa arvore dependendo do modo*/
comp* AVLbalance(comp* h, char modo){
        int balanceFactor, hleft, hright;
	comp *left,*right;
	left = modo ? h->alfaLeft : h->orderLeft;
	right = modo ? h->alfaRight : h->orderRight;
        if (h == NULL) {
		return h;
	}
        balanceFactor = balance(h,modo);
        if(balanceFactor > 1) { /* mais peso para a esquerda */
                if (balance(left,modo) >= 0) h = rotR(h,modo);
                else h = rotLR(h,modo);
        }
        else if(balanceFactor < -1){ /* mais peso para a direita*/
                if (balance(right,modo) <= 0) h = rotL(h,modo);
                else h = rotRL(h,modo);
        }
        else{
                hleft = height(left,modo);
                hright = height(right,modo);
		if (modo){
                	h->alfaHeight = hleft > hright ? hleft + 1 : hright + 1;
		} else {
			h->orderHeight = hleft > hright ? hleft + 1 : hright + 1;
		}
        }
        return h;
}



/* Funcao responsavel por indicar o caminho a funcao findComp*/
short findFunc(comp *c1,char modo, buff* bf){
	short res;
	if (modo){ /* comparar nomes*/
		res = myStrCmp(c1->nome,bf);
	} else {
		res = (bf->occ)>(c1->occ) ? 1 : -1;
		res = (bf->occ)==(c1->occ) ? 0 : res;
	}
	return res;
}


/* Devolve a componente com as mesmas caracteristicas do buffer
 * Se nao encontrar, devolve NULL
 * modo 1 -> procurar por nome
 * modo 0 -> procurar por ordem de chegada*/
comp* findComp(comp* root, char modo, buff* bf){
	static short res;
	res = findFunc(root,modo,bf);
	if (root == NULL || !res){
		return root;
	}
	else if (res>0){
		if (modo){
			return findComp(root->alfaRight, modo,bf);
		} else {
			return findComp(root->orderRight,modo,bf);
		}
	} else {
		if (modo){
                        return findComp(root->alfaLeft, modo,bf);
                } else {
                        return findComp(root->orderLeft,modo,bf);
                }
	}	
}

/* Insere a componente com as caracteristicas guardadas no buffer,
 * faz os rotates necessarios. Devolve um pointer para a componente inserida
 * Se ja existir devolve o seu ponteiro
 * modo 1 -> procurar por nome
 * modo 0 -> procurar por ordem de chegada*/ 
comp* insertComp(comp* root, char modo,char* exists, mother* M){
	static short res;
	if (root == NULL){
		compToBuff(initComp(M),M->bf);
		return getBuffComp(M->bf);
        }
	if (modo){
		res = findFunc(root,modo,M->bf);
		if (!res){
			compToBuff(root,M->bf);
			return root;
		}
		else if (res>0){
                        root->alfaRight = 
				insertComp(root->alfaRight,modo,exists,M);	
		} else {
                        root->alfaLeft = 
				insertComp(root->alfaLeft,modo,exists,M);	
		}
	} else { /* Por ordem de criacao, inserimos sempre no fim*/	
        	root->orderRight = insertComp(root->orderRight,modo,exists,M);
	}
	if (res){ /*se nao inserimos, nao precisamos de fzr rotate*/
		root = AVLbalance(root,modo);
	}
        return root;
}

/* Insere uma componente nova nas AVL's por ordem de criacao e por 
 * ordem alfabetica. Se ja existir, devolve a componente*/
comp* insertAll(avlHead* root, mother* M){
	char exists=ZERO;
	root->rootAlfa = insertComp(root->rootAlfa,ONE,&exists,M);
        if (!exists){ /* Se a componente ainda nao existir*/
        	root->rootOrder=insertComp(root->rootOrder,ZERO,&exists,M);
		(root->occ)+=ONE;
	}
	return getBuffComp(M->bf);
}



/* Atribui um novo valor a uma componente*/
void compNewValue(comp* c1, mother* M){
	unsigned int dim = strlen(M->bf->bigBuff);
	char* safe;
	dim++; /*incluir espaco para '\0'*/
	safe = (char*) realloc(c1->valor,dim*(sizeof(char)));
	if (safe==NULL){
		/* Esta funcao e chamada quando c1 ja pertence a uma AVL
		 * c1 (e c1->valor) nao podem ser libertados agora*/
		endProgram(M);
	}
	c1->valor = safe;
	printf("Whats in the buffer -%s-\n",M->bf->bigBuff);
	strcpy(c1->valor,M->bf->bigBuff);
}

/* Verifica se existe valor associado a componente*/
short compValNull(comp *c1){
	return (*(c1->valor))=='\0';
}

/* Devolve ponteiro para a componente final do caminho 
 * no buffer da mother
 * modo '0'-se o caminho nao existir, cria um novo
 * modo '1'-se nao existir, nao cria */
comp* getPathComp(short modo, char* succ, mother* M){
	char* path = M->bf->bigBuff;
	avlHead* root = M->motherRoot;
	comp* c1;
	pathClean(path,&(M->bf->start));
	occToBuff(root->occ,M->bf);
	while (*(path+(M->bf->start))!='\0'){
		M->bf->end = findSepar(path,M->bf->start);
		if (modo){
			c1 = findComp(root->rootOrder, ZERO, M->bf);
			if (c1==NULL){
				printf("not found\n");
                        	*succ = 0;
                        	break;
			}
		} else {
			c1 = insertAll(root,M);
		}
		root = c1->follow;
		occToBuff(root->occ,M->bf);	
		M->bf->start = M->bf->end;
		pathClean(path,&(M->bf->start));
	}
	return c1;
}





/* Travessia in-order da AVL alfabetica, com uma funcao a correr*/
void avlSortAlfa(void (*f)(comp*),comp* c1){
	if (c1==NULL) return;
	avlSortAlfa(f,c1->alfaLeft);
	(*f)(c1);
	avlSortAlfa(f,c1->alfaRight);
}

/* Travessia in-order da AVL por criacao, com uma funcao a correr*/
void avlSortOrder(void (*f)(comp*,buff*),comp* c1,buff* bf){
	if (c1==NULL) return;
        avlSortOrder(f,c1->orderLeft,bf);
        (*f)(c1,bf);
        avlSortOrder(f,c1->orderRight,bf);
}

/* Travessia post-order da AVL alfabetica, com uma funcao a correr*/
void avlPostAlfa(void (*f)(comp*),comp* c1){
	if (c1==NULL) return;
        avlPostAlfa(f,c1->alfaLeft);
        avlPostAlfa(f,c1->alfaRight);
        (*f)(c1);

}

/* Travessia post-order da AVL por criacao, com uma funcao a correr*/
void avlPostOrder(void (*f)(comp*),comp* c1){
	if (c1==NULL) return;
        avlPostOrder(f,c1->orderLeft);
        avlPostOrder(f,c1->orderRight);
        (*f)(c1);
}


/* Imprime o caminho da componente e o seu valor
 * Parte do caminho esta guardado no buffer*/
void printComp(comp *c1, buff *bf){
	printf("%s/",bf->bigBuff); /*O caminho que esta para tras*/
        printf("%s ",c1->nome); /*nome da componente*/
        printf("%s\n",c1->valor);
}


/*Imprime as componentes recursivamente*/
void printCompsR(comp* c1, buff* bf){
	printf("comName - %s\n",c1->nome);
	if (!(compValNull(c1))){ /* tem valor*/
		printf("has value\n");
		printComp(c1,bf);	
	}
	if ((c1->follow->occ)){ /*tem componentes filho*/
		printf("has occ\n");
		addToBuff(bf,c1);
		avlSortOrder(printCompsR,c1->follow->rootOrder,bf);
		removeFromBuff(bf,c1);
	}
		
}

