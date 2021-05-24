/*
 * Ficheiro: mother.c
 * Autor: Joao Fonseca
 * Descricao: Implementacao da estrutura mother.
*/

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
	return H->motherRoot;
}

/*Faz free à mother*/
void freeMother(mother *M){
        freeBuffer(M->bf);
        freeHead(M->motherRoot);
        freeHash(M->h);
        free(M);
}

