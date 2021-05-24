/*
 * Ficheiro: mother.c
 * Autor: Joao Fonseca
 * Descricao: Implementacao da estrutura mother.
*/


#include "proj2.h"

/* ===========================================================================
 * Mother
 *
 * - buff* bf 			(buffer que vai guardar varias coisas)
 * - avlHead* motherRoot 	(a raiz das AVL's do programa)
 * - hash* h 			(Hash table que guarda os valores)  
 * =========================================================================*/



/*Inicializa uma mother*/
mother* initMother(){
        char control=ZERO;
        mother* M = (mother*) malloc(sizeof(mother));
        M->bf = initBuffer();
        M->motherRoot = initHead(&control);
        M->h = initHash();
        return M;
}

/*Devolve o Buffer da mother*/
buff* getMotherBuff(mother* M){
	return M->bf;
}

/*Devolve o Hash da mother*/
hash* getMotherHash(mother* M){
	return M->h;
}


/*Devolve a avlHead da mother*/
avlHead* getMotherHead(mother* M){
	return M->motherRoot;
}

/*Devolve o start do buffer*/
unsigned short getMBuffStart(mother* M){
	return getBuffStart(getMotherBuff(M));
}

/*Devolve o end do buffer*/
unsigned short getMBuffEnd(mother* M){
        return getBuffEnd(getMotherBuff(M));
}



/*Faz free à mother*/
void freeMother(mother *M){
        freeBuffer(M->bf);
        freeHead(M->motherRoot);
        freeHash(M->h);
        free(M);
}

