if (!compValNull(cpath)){
                removeFromHash(cpath,getMotherHash(M));
}

compNewValue(cpath,M);

cpath->nextValue = getFirstHashEl(getMotherHash(M), cpath);
M->h = addToHash(getMotherHash(M),cpath);



/*------------------------------------*/



/* Adiciona um node à hash*/
hash* addToHash(hash *h,node c1){
        unsigned long ind;
        ind = hashU(getValue(c1),h->hSize);
        printf("ind = %ld\n",ind);
        h->tabela[ind] = c1;
        return h;

}

/* Devolve o primeiro elemento da hash, no mesmo indice
 * que o node "c1"*/
node getFirstHashEl(hash *h, node c1){
        unsigned long ind;
        node cout;
        ind = hashU(getValue(c1),h->hSize);
        cout = h->tabela[ind];
        return cout;
}


char removeFromHash(node c1, hash* h){
        unsigned long ind;
        node out;
        ind = hashU(getValue(c1),h->hSize);
        out = *(h->tabela + ind);
        if (c1==out){
                out = getNextValue(c1);
                return ONE;
        }
        out = removeFromHashAux(out,c1);
        /* removeFromHashAux esta em componentes.c*/
        return ZERO;
}




/*Funcao auxiliar para remover um node da Hash*/
node removeFromHashAux(node c1, node c2){
        if (c1==NULL){
                printf("a1\n");
                return NULL;
        }
        if (c1==c2){ /*apontam para a mesma componente*/
                printf("a2\n");
                printf("is next Null %d\n",getNextValue(c1)==NULL);
                exit(0);
                return getNextValue(c1);
        } else {
                printf("a3\n");
                c1->nextValue = removeFromHashAux(c1->nextValue,c2);
        }
        return c1;
}





