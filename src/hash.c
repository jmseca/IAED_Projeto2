/*
 * Ficheiro: hash.c
 * Autor: Joao Fonseca
 * Descricao: Implementacao de uma Tabela de Dispersao
 * de componentes
*/

#include "proj2.h"


hash* initHash(){ 
	hash* h;
	unsigned long i;
	h = (hash*) malloc(sizeof(hash));
	h->hSize = HASH_SIZE;
	h->tabela = (comp**) malloc(HASH_SIZE*(sizeof(comp*)));
	/*Colocar os Valores a NULL*/
	for (i=0;i<HASH_SIZE;i++){
		*(h->tabela +i)= NULL;
	}
	return h;
}



hash* addToHash(hash *h,comp* c1){
	unsigned long ind;
	ind = hashU(c1->valor,h->hSize); /*Dps abstracao*/
	h->tabela[ind] = c1;
	return h;
	
}

comp* getFirstHashEl(hash *h, comp* c1){
	unsigned long ind;
	comp* cout;
	ind = hashU(c1->valor,h->hSize); /*Dps abstracao*/
        cout = h->tabela[ind];
	return cout;
}







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
 * de caminho (podem ate ja corresponder a um componente "pai")*/
long coef(comp* c1,comp* c2){
	static long res;
	if (c1->prof==ZERO){ /*a de c2 tambem sera*/
		return c1->occ - c2->occ;		
	} else {
		res = coef(c1->motherComp,c2->motherComp);
		if (!res){
			res = c1->occ-c2->occ;
		} 
		return res;
	}
}

/* Compara a ordem de insercao de c1, com c2
 * Devolve 1 se c1 vem antes de c2 e 0 caso contrario*/
char compInsertOrder(comp *c1, comp *c2){
	unsigned short pc1 = c1->prof,pc2 = c2->prof; 
	char c = 1; /* var control*/
	long res;
	if (c2==NULL){
		return ZERO;
	}
	while (pc1<pc2){
		c2 = c2->motherComp;
		pc2--;
	}
	if (pc1 > pc2){
		c=0;
		while(pc1>pc2){
			c1 = c1->motherComp;
			pc1--;	
		}
	}
	res = coef(c1,c2);
	if (res>0){
		return ZERO;
	} else if (!res){
		return c;
	} else {
		return ONE;
	}
}


comp* getItem(char* value,mother *M){
	comp* out;
	unsigned long ind;
	ind = hashU(value,M->h->hSize);
	out = *(M->h->tabela + ind);
	M->bf->c = NULL;
	while (out!=NULL){
		if (!strcmp(value,out->valor)){
			if (M->bf->c==NULL || !compInsertOrder(out,M->bf->c)){
				M->bf->c = out;
			}
		}
		out = out->nextValue;

	}
	return M->bf->c;
}


void freeHash(hash* h){
	/*unsigned long i;
	for (i=0;i<h->hSize;i++){
		free(h->tabela[i]);
	}*/
	free(h->tabela);
	free(h);
}

comp* removeFromHashAux(comp *c1, comp *c2){
        if (c1==c2){ /*apontam para a mesma componente*/
                return c2->nextValue;
        } else {
                c1->nextValue = removeFromHashAux(c1->nextValue,c2);
        }
	return c1;
}



void removeFromHash(comp* c1, hash* h){
	unsigned long ind;
	comp* out;
        ind = hashU(c1->valor,h->hSize);
	out = *(h->tabela + ind);
	out = removeFromHashAux(out,c1);
}

