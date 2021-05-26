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
node initComp(mother* M){
	node c1;
	char control = ZERO;
	buff* bf = getMotherBuff(M);
	unsigned int vSize = getVsize(bf);
	c1 = (node) myMalloc(COMP,ONE,&control);
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
	c1->occ = buffOrder(getMotherBuff(M)); /* occ guardada no buffer*/
	c1->alfaHeight = ONE;
	c1->orderHeight = ONE;
	*(c1->valor) = ZERO;
	myStrCpy(c1->nome,bf);
	c1->motherComp=getBuffNode(getMotherBuff(M));
	c1->nextValue = NULL;
	c1->prof=calculProf(c1);
	return c1;
}

/*Devolve a profundidade dos caminhos a que se encontra a componente*/
unsigned short calculProf(node c1){
	unsigned short out = ZERO;
	if (c1!=NULL){
		while(c1->motherComp!=NULL){
			out++;
			c1 = c1->motherComp;
		}
	}
	return out;

}

/*Devolve a avlHead dos seus componentes "filho"*/
avlHead* getCompFollow(node c1){
	return c1->follow;
}



/* Faz free a uma componente que deu erro no malloc*/
void freePreComp(node c1){
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
void compNewValue(node c1, mother* M){
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
	strcpy(c1->valor,getBuff2(getMotherBuff(M)));
}

/* Verifica se existe valor associado a componente*/
char compValNull(node c1){
	return (*(c1->valor))==ZERO;
}



/* Imprime o valor de uma componente se existir*/
void printCompVal(node c1){
	if (compValNull(c1)){
		printf(NO_DATA);
	} else {
		printf(SN,c1->valor);
	}
}

/* Imprime o nome da componente*/
void printCompName(node c1){
	printf(SN,c1->nome);
}

/* Imprime o caminho do componente sem \n*/
void printPath(node c1){
	if (c1->motherComp != NULL){
		printPath(c1->motherComp);
	}
	printf(_S,c1->nome);
}

/* Imprime o caminho de uma componente, 
 * e de todos os seus "filhos" (se tiver)*/
void printMaster(node c1){
	if (!compValNull(c1)){
		printPath(c1);
		printf(" %s\n",c1->valor);
	}
	if ((c1->follow->occ)){ /*tem componentes filho*/
		avlSortOrderDeep(printMaster,c1->follow->rootOrder);
	}
}


/* Devolve ponteiro para a componente final do caminho 
 * no buffer da mother
 * modo '0'-se o caminho nao existir, cria um novo
 * modo '1'-se nao existir, nao cria */
node getPathComp(short modo, mother* M){
	char* path = getBuff(getMotherBuff(M));
	avlHead* root = getMotherHead(M);
	node c1=NULL;
	pathClean(path,&(getMotherBuff(M)->start));
	orderToBuff(root->occ,getMotherBuff(M));
	while (*(path+(getMBuffStart(M)))!='\0'){
		getMotherBuff(M)->end = findSepar(path,getMBuffStart(M));
		if (modo){
			c1 = findComp(root->rootAlfa, ONE, getMotherBuff(M));
			if (c1==NULL){
				printf(NOT_FOUND);
                        	break;
			}
		} else {
			c1 = insertAll(root,M);
		}
		root = c1->follow;
		orderToBuff(root->occ,getMotherBuff(M));
                getMotherBuff(M)->start = getMBuffEnd(M);
                pathClean(path,&(getMotherBuff(M)->start));
	
	}
	return c1;
}

/*Devolve a AVL onde esta o componente que se quer eliminar
 * Semelhante a anterior, mas devolve-se um tipo diff
 * (Em cima, se devolvesse "root", nao chegava a "c1" depois)*/
avlHead* getDeleteAVL(mother* M){
	char* path = getBuff(getMotherBuff(M));
	node c1;
	avlHead* root = getMotherHead(M);
	if (!nullBuff(getMotherBuff(M))){
        	pathClean(path,&(getMotherBuff(M)->start));
		while (*(path+(getMBuffStart(M)))!='\0'){

			getMotherBuff(M)->end = findSepar(path,getMBuffStart(M));
			c1 = findComp(root->rootAlfa, ONE, getMotherBuff(M));
                	if (c1==NULL){
                        	printf(NOT_FOUND);
				return NULL;
                	}
			root = c1->follow;
                	getMotherBuff(M)->start = getMBuffEnd(M);
                	pathClean(path,&(getMotherBuff(M)->start));
		}
	}
	return root;
}




/* free a uma componente e dos seus constituintes, recursivamente*/
void freeCompR(node c1){
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

/*Copia alfa para o buffer (bigbuff)*/
void cpyAlfa(buff* bf, char *alfa){
	strcpy(bf->bigBuff,alfa);
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
		return getNextValue(c1);
        } else {
		c1 = removeFromHashAux(c1->nextValue,c2);
        }
        return c1;
}

