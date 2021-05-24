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
 * -char* nome 			(nome de uma componente)
 * -char* valor 		(valor de uma componente)
 * -unsigned long occ 		(A ordem de insercao no seu caminho "mãe")
 * -unsigned long alfaHeight 	(Altura da AVL alfa)
 * -unsigned long orderHeight 	(Altura da AVL order)
 * -componente* alfaRight  	(Ramo diretio do alfa)
 * -componente* alfaLeft 	(Ramo esquerdo do alfa)
 * -componente* orderRight 	(Ramo direito do order)
 * -componente* orderLeft 	(Ramo esquerdo do order)
 * -componente* motherComp	(Pointer para o caminho "mãe")
 * -componente* nextValue	(Ponteiro para uma componente da Hash)
 * - unsigned short prof	(profundidade do caminho da componente)
 * -AVLhead* follow 		(componentes seguintes)
 ============================================================================*/


/* ============================================================================
 * Node -> Será um ponteiro para uma componete
 * 	Alfa - nome da componente
 * 	Order - occ da componente 
============================================================================*/



/* Inicializa uma componente, alocando memoria*/
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
		freePreComp(c1);
		endProgram(M);
	}
	c1->alfaRight = NULL;
	c1->alfaLeft = NULL;
	c1->orderRight = NULL;
	c1->orderLeft = NULL;
	c1->occ = getBuffOcc(getMotherBuff(M)); /* occ guardada no buffer*/
	c1->alfaHeight = ONE;
	c1->orderHeight = ONE;
	*(c1->valor) = ZERO;
	myStrCpy(c1->nome,bf);
	c1->motherComp=getBuffComp(getMotherBuff(M));
	c1->nextValue = NULL;
	c1->prof=calculProf(c1);
	return c1;
}

/*Devolve a profundidade dos caminhos a que se encontra a componente*/
unsigned short calculProf(comp* c1){
	unsigned short out = ZERO;
	while(c1->motherComp!=NULL){
		out++;
		c1 = c1->motherComp;
	}
	return out;

}

/*Devolve a avlHead dos seus componentes "filho"*/
avlHead* getCompFollow(comp* c1){
	return c1->follow;
}



/* Faz free a uma componente que deu erro no malloc*/
void freePreComp(comp *c1){
	/*Se houve erro, pelo menos c1->follow e NULL*/
	if ((c1->valor)!=NULL){
		free(c1->valor);
	}
	if ((c1->nome)!=NULL){
		free(c1->nome);
	}
	free(c1);
}


/* Atribui um novo valor a uma componente*/
void compNewValue(comp* c1, mother* M){
	unsigned int dim = strlen(M->bf->bigBuff2);
	char* safe;
	dim++; /*incluir espaco para '\0'*/
	safe = (char*) realloc(c1->valor,dim*(sizeof(char)));
	if (safe==NULL){
		/* Esta funcao e chamada quando c1 ja pertence a uma AVL
		 * c1 (e c1->valor) nao podem ser libertados agora*/
		endProgram(M);
	}
	c1->valor = safe;
	strcpy(c1->valor,M->bf->bigBuff2);
}

/* Verifica se existe valor associado a componente*/
char compValNull(comp *c1){
	return (*(c1->valor))=='\0';
}



/* Imprime o valor de uma componente se existir*/
void printCompVal(comp *c1){
	if (compValNull(c1)){
		printf("no data\n");
	} else {
		printf("%s\n",c1->valor);
	}
}

/* Imprime o nome da componente*/
void printCompName(comp* c1){
	printf("%s\n",c1->nome);
}


/* Imprime o caminho do componente*/
void printPath(comp* c1){
	if (c1->motherComp != NULL){
		printPath(c1->motherComp);
	}
	printf("/");
	printf("%s",c1->nome);
}

/* Imprime o caminho de uma componente, 
 * e de todos os seus "filhos" (se tiver)*/
void printMaster(comp* c1){
	if (!compValNull(c1)){
		printPath(c1);
		printf(" %s\n",c1->valor);
	}
	if ((c1->follow->occ)){ /*tem componentes filho*/
		avlSortOrderDeep2(printMaster,c1->follow->rootOrder);
	}
}



/* Devolve ponteiro para a componente final do caminho 
 * no buffer da mother
 * modo '0'-se o caminho nao existir, cria um novo
 * modo '1'-se nao existir, nao cria */
comp* getPathComp(short modo, mother* M){
	char* path = M->bf->bigBuff;
	avlHead* root = M->motherRoot;
	comp* c1;
	pathClean(path,&(M->bf->start));
	occToBuff(root->occ,M->bf);
	while (*(path+(M->bf->start))!='\0'){
		M->bf->end = findSepar(path,M->bf->start);
		if (modo){
			c1 = findComp(root->rootAlfa, ONE, M->bf);
			if (c1==NULL){
				printf("not found\n");
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

/*Devolve a AVL onde esta o componente que se quer eliminar
 * Semelhante a anterior, mas devolve-se um tipo diff
 * (Em cima, se devolvesse "root", nao chegava a "c1" depois)*/
avlHead* getDeleteAVL(mother* M){
	char* path = M->bf->bigBuff;
	comp* c1;
	avlHead* root = M->motherRoot;
	if (!nullBuff(M->bf)){
        	pathClean(path,&(M->bf->start));
		while (*(path+(M->bf->start))!='\0'){

			M->bf->end = findSepar(path,M->bf->start);
			c1 = findComp(root->rootAlfa, ONE, M->bf);
                	if (c1==NULL){
                        	printf("not found\n");
				return NULL;
                	}
			root = c1->follow;
                	M->bf->start = M->bf->end;
                	pathClean(path,&(M->bf->start));
		}
	}
	return root;
}







/* Imprime o caminho da componente e o seu valor
 * Parte do caminho esta guardado no buffer*/
void printComp(comp *c1, buff *bf){
	printf("%s ",bf->bigBuff); /*O caminho que esta para tras*/
        printf("%s\n",c1->valor);
}


/*Imprime as componentes recursivamente*/
void printCompsR(comp* c1, buff* bf){
	addToBuff(bf,c1);
	if (!(compValNull(c1))){ /* tem valor*/
		printComp(c1,bf);	
	}
	if ((c1->follow->occ)){ /*tem componentes filho*/
		avlSortOrderDeep(printCompsR,c1->follow->rootOrder,bf);
	}
	removeFromBuff(bf);
		
}



/* free a uma componente e dos seus constituintes, recursivamente*/
void freeCompR(comp *c1){
	freeHead(c1->follow);
	free(c1->valor);
	free(c1->nome);
	free(c1);
}


/*==========	NODE	==========*/

/*Devolve o order do Node*/
unsigned long getOrder(node c1){
	return c1->occ;
}

/* Devolve o alfa do Node*/
char* getAlfa(node c1){
	return c1->nome;
}


/*Devolve o valor do node*/
char* getValue(node c1){
	return c1->valor;
}

/*Compara o alfa de um node com o guardado no buffer*/
short compareAlfaBuff(char* alfa,buff* bf){
	return myStrCmp(alfa,bf);
}

/*Compara dois order's*/
char compareOrder(unsigned long order1, unsigned long order2){
	if (order1>order2){
                return ONE;
        } else if (order1<order2){
                return -ONE;
        } else {
                return ZERO;
        }
	
}

/*devolve a profundidade de um node*/
unsigned short getProf(node c1){
	return c1->prof;
}

/*Devolve a componente "mae" do node*/
node getMotherNode(node c1){
	return c1->motherComp;
}

/*devolve o proximo node, na tabela hash*/
node getNextValue(node c1){
	return c1->nextValue;
}

/*Funcao auxiliar para remover um node da Hash*/
node removeFromHashAux(node c1, node c2){
        if (c1==NULL){
                return NULL;
        }
        if (c1==c2){ /*apontam para a mesma componente*/
                return getNextValue(c2);
        } else {
                c1->nextValue = removeFromHashAux(c1->nextValue,c2);
        }
        return c1;
}

