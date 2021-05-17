/*
 * Ficheiro: componentes.c
 * Autor: Joao Fonseca
 * Descricao: Definicao das funcoes que vao manipular
 * os componentes, bem como as estruturas que formam os componentes.
*/

#include "proj2.h"
 

/* ============================================================================
 * Componente (comp):
 *
 * - unsigned long* size, numero de ponteiros de componentes que pode receber
 * - unsigned long* occ, quantos ponteiros de componentes ja tem
 * - char* valor, valor do caminho
 * - char* nome, nome do componente
 * - Hashtable de Dim 12 que guarda os ponteiros para os componentes 
 * seguintes. Colisoes resolvidas com uma especie de encadeamento externo,
 * onde os vetores estao ordenados por ordem alfabetica
 * em vez de por ordem de chegada.
 * - Vetor com os ponteiros 
 * dos seguintes componentes ordenados por ordem de criacao
 * ============================================================================
*/

/* ============================================================================
 * Vetores de Ponteiros de Componentes (vpc):
 *
 * - unsigned long* size, numero de ponteiros de componentes que pode receber
 * - unsigned long* occ, quantos ponteiros de componentes ja tem
 * - comp** info, vetor com os ponteiros
 * de componentes
 * ============================================================================
*/

	
/*Funcao de Dispersao para a Hashtable dos componentes*/
unsigned short hashFun(char* str){
	unsigned short out;
	/*char ascii 33 eh o primeiro que se pode ter no nome*/
	out = (*str-33)/8;
	return out;
	
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
long getBinRes(char *cName, vpc *vetor, long ind){
        int out; 
        out = strcmp(cName,vetor->info[ind]->nome);
        return out;
}



/* Funcao de procura e insercao binaria responsavel por devolver
 *o indice pretendido (que seja para encontrar ou inserir)*/
unsigned long binarySearch(char *cName, vpc *vetor, short *found){
        short up=1;
        int res=0;
	unsigned long size = *(vetor->size);
	unsigned long ind=0;
        unsigned long maxInd = *(vetor->occ)-1;
	found = 0; /*Evitar erros possiveis*/
	if (size){
                size += size%2 ? 0 : 1;
                do {
                        ind = getBinInd(&size, ind, up, maxInd);
                        res = getBinRes(cName, vetor, ind);
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
	for (i=*(vetor->occ);i>=ind;--i){
		vetor->info[i] = vetor->info[i-1];
	}
	vetor->info[ind] = c1;
	vetor->occ++;
}

/*Aumenta o numero de ponteiros de componentes que pode albergar*/
vpc* extendVpc(vpc *vetor, unsigned long newSize){
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


/* Inicializa um ponteiro para um componente, alocando-lhe alguma memoria*/
comp* initComp(char* nome, ){
	comp* c1;
	short i;
	c1 = (comp*) malloc(sizeof(comp));
	c1->valor = (char*) malloc(sizeof(char));
	*(c1->valor) = '\0';
	c1->hash = (vpc**) malloc(sizeof(vpc*)*HASH_MAX);
	for (i=0;i<HASH_MAX;i++){
		c1->hash[i] = initVpc(FIRST_SIZE_H);
	}
	c1->primeiros = initVpc(FIRST_SIZE_C);
	return c1;
}

/* Verifica se a componente com nome "nome" esta nos 
 *componentes seguintes de "c1"*/
comp* belongsToComp(comp *c1, char *nome, short *found){
	unsigned long size,occ,ind;
	vpc *vetor;
	ind = hashFun(nome);
	vetor = c1->hash[ind];
	size = *(vetor->size);
	occ = *(vetor->occ);
	ind = binarySearch(name,vetor,found);
	if (*found){
		return vetor[ind];
	} else {
		return c1
	}
}

/* Verifica se existe valor associado a componente*/
short compValNull(comp *c1){
	return *(c1->valor[0])=='\0';
}

void printCompVal(comp *c1){
	printf("%s\n",c1->valor);
}


/* Recebe */
comp* goToPath(char* path){
