/*
 * Ficheiro: hash.c
 * Autor: Joao Fonseca
 * Descricao: Implementacao de uma Tabela de Dispersao
 * de nodes pelos seus valores (que são strings).
 * Para colisões, utiliza a resolução por encadeamento 
 * externo
*/

#include "proj2.h"

/*Inicializa uma Hash Table*/
hash* initHash(){ 
	hash* h;
	unsigned long i;
	h = (hash*) malloc(sizeof(hash));
	h->hSize = HASH_SIZE;
	h->tabela = (node*) malloc(HASH_SIZE*(sizeof(node)));
	/*Colocar os Valores a NULL*/
	for (i=0;i<HASH_SIZE;i++){
		*(h->tabela +i)= NULL;
	}
	return h;
}

/*Devolve o tamanho da Hash*/
unsigned long getHashSize(hash* h){
	return h->hSize;
}

/* Adiciona um node à hash*/
hash* addToHash(hash *h,node c1){
	unsigned long ind;
	ind = hashU(getValue(c1),h->hSize); /*Dps abstracao*/
	h->tabela[ind] = c1;
	return h;
	
}

/* Devolve o primeiro elemento da hash, no mesmo indice
 * que o node "c1"*/
node getFirstHashEl(hash *h, node c1){
	unsigned long ind;
	node cout;
	ind = hashU(getValue(c1),h->hSize); /*Dps abstracao*/
        cout = h->tabela[ind];
	return cout;
}






/*Função Hash*/
unsigned long hashU(char *v, unsigned long M){
	unsigned long h, a = 31415, b = 27183;
	for (h=0; *v != '\0'; a=(a*b)&(M-1)){
		h = ((a*h) + (*v))%M;
		v++;
	}
	return h;
}



/*Funcao auxiliar do compInsertOrder,verifica qual a
 * componente que vem antes, quanto ja estao na mesma profundidade
 * de caminho (podem ate ja corresponder a um componente "mae")*/
long coef(node c1,node c2){
	static long res;
	if (getProf(c1)==ZERO){ /*a de c2 tambem sera*/
		return compareOrder(getOrder(c1),getOrder(c2));		
	} else {
		res = coef(getMotherNode(c1),getMotherNode(c2));
		if (!res){
			res = compareOrder(getOrder(c1),getOrder(c2));
		}
		return res;
	}
}

/* Compara  c1 com c2 pelo order
 * Devolve 0 se c1 vem antes de c2 e 1 caso contrario*/
char compInsertOrder(node c1, node c2){
	unsigned short pc1 = getProf(c1),pc2 = getProf(c2); 
	char c = ZERO; /* var control*/
	long res;
	while (pc1<pc2){
		c2 = getMotherNode(c2);
		pc2--;
	}
	if (pc1 > pc2){
		c=ONE;
		while(pc1>pc2){
			c1 = getMotherNode(c1);
			pc1--;	
		}
	}
	res = coef(c1,c2);
	if (res>ZERO){
		return ONE;
	} else if (!res){
		return c;
	} else {
		return ZERO;
	}
}

/*Devolve o primeiro node com valor "value"*/
node getItem(char* value,mother *M){
	node out;
	unsigned long ind;
	nodeToBuff(NULL,getMotherBuff(M));
	if (!nullStr(value)){
		ind = hashU(value,getHashSize(getMotherHash(M)));
		out = *(getMotherHash(M)->tabela + ind);
		while (out!=NULL){
			if (!strcmp(value,getValue(out))){
				if (M->bf->c==NULL || 
				!compInsertOrder(out,
				getBuffNode(getMotherBuff(M)))){
					nodeToBuff(out,getMotherBuff(M));
				}
			}
			out = getNextValue(out);
		}
	}
	return getBuffNode(getMotherBuff(M));
}

/* Faz free à Hash*/
void freeHash(hash* h){
	free(h->tabela);
	free(h);
}

/* Remove um node da Hash*/
void removeFromHash(node c1, hash* h){
	unsigned long ind;
	node out;
        ind = hashU(c1->valor,h->hSize);
	out = *(h->tabela + ind);
	out = removeFromHashAux(out,c1);
	/* removeFromHashAux esta em componentes.c*/
}

