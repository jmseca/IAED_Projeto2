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

/* Inicializa*/
avlHead* initHead(mother* M){
	avlHead* head;
	char control = ZERO; /*controlar se ainda ha memoria*/	
	head = (avlHead*) myMalloc(AVLHEAD,ONE,&control);
       	if (control) /*ja nao ha memoria*/
		exitProgram(M);
	head->occ = ZERO;
	head->rootAlfa = NULL;
	head->rootOrder = NULL;
	return avlHead 
}


comp* initComp(mother* M){
	comp* c1;
	char control = ZERO;
	buff* bf = M->bf;
	unsigned int vSize = getVsize(bf);
	c1 = (comp*) myMalloc(COMP,ONE,M,control);
	c1->nome = (char*) myMalloc(ONE,vSize,M,control);
	c1->valor = (char*) myMalloc(ONE,ONE,M,control);

	if (control){ /* ja nao ha memoria*/
		freeComp(c1,ONE);
		exitProgram(M);
	}
	/*Refazer o malloc*/
	c1->alfaRight = NULL;
	c1->alfaLeft = NULL;
	c1->orderRight = NULL;
	c1->orderLeft = NULL;
	c1->occ = ZERO;
	c1->alfaHeight = ZERO;
	c1->orderHeight = ZERO;
	*(c1->valor) = ZERO;
	myStrCpy(c1->nome,bf);
	return c1;
}

/* Faz free a uma componente
 * modo 1 -> houve erro a alocar memoria da componente
 * modo 0 -> fazer free da componente normalmente*/
void freeComp(comp *c1, char modo){
	if (modo) {
		if ((c1->nome)!=NULL){
			free(c1->nome);
		}
		if (c1 == NULL){
			free(c1);
		}
	} else {
		/* free all fica para dps*/
	
	}
}

/* Funcao responsavel por indicar o caminho a funcao findComp*/
short findFunc(comp *c1, char* found,char modo, buff* bf){
	short res;
	if (modo){ /* comparar nomes*/
		res = myStrCmp(c1->nome,bf);
	} else {
		res = (bf->occ)>(c1->occ) ? 1 : -1;
		res = (bf->occ)==(c1->occ) ? 0 : res;
	}
	if (!res){
		*found = 1;
	}
	return res;
}


/* Encontra a componente, ou o lugar onde deveria estar
 * modo 1 -> procurar por nome
 * modo 0 -> procurar por ordem de chegada*/
comp* findComp(comp* root,char* found, char modo, buff* bf){
	short res;
	comp* c1=root;
	while (c1!=NULL){
		res = findFunc(c1,found,modo,bf);
		if (*found){
			break;
		}
		if (res>ZERO){
			c1 = modo ? c1->alfaRight : c1->orderRight;
		} else {
			c1 = modo ? c1->alfaLeft : c1->orderLeft;
		}
	}
	return c1;

}









/* Atribui um novo valor a uma componente*/
void compNewValue(comp* c1, char* val){
	unsigned int dim = strlen(val);
	char control;
	dim++; /*incluir espaco para '\0'*/
	c1->valor = (char*) realloc(c1->valor,dim*(sizeof(char)));
	strcpy(c1->valor,val);

}

/* Adiciona uma nova componente ao ponteiro "c1", com os dados do buffer*/ 
comp* addNewComp(comp *c1, mother *M){
	c1 = initComp(M);
	return c1;
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
