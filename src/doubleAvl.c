/*
 * Ficheiro: doubleAvl.c
 * Autor: Joao Fonseca
 * Descricao: Implementacao de duas AVL's que partilham
 * os mesmos nodes. Essas serao ordenadas atraves de 2 valores do node
 * alfa e order. Para isso, usa tambem algumas estruturas da mother.
*/

#include "proj2.h"


/* ============================================================================
 * avlHead
 *
 * -unsigned long occ 		(ocupacao da avl)
 * -componente* rootAlfa 	(avl ordenada por alfa)
 * -componente* rootOrder 	(avl ordenada por order)
 ============================================================================*/


/*Inicializa uma avlHead*/
avlHead* initHead(char* control){
        avlHead* head;
        head = (avlHead*) myMalloc(AVLHEAD,ONE,control);
        if (!(*control)){ /*ha memoria*/
                head->occ = ZERO;
                head->rootAlfa = NULL;
                head->rootOrder = NULL;
        }
        return head;
}


/* Devolve a height do node da arvore desejada
 * modo 1->ordenada por alfa
 * modo 0->ordenada por order*/
unsigned short height(node h, char modo){
        if (h == NULL) return 0;
        if (modo){
                return h->alfaHeight;
	}
	return h->orderHeight;
}



/* Rotacao a esquerda na arvore pretendida (modo)*/
node rotL(node h, char modo){
        unsigned short hleft, hright, xleft, xright;
        node x;
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
node rotR(node h, char modo){
        unsigned short hleft, hright, xleft, xright;
        node x;
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



/* Devolve o node maximo de uma AVL
 * modo 0 -> AVL por order
 * modo 1 -> AVL por alfa*/
node max(node h, char modo){
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
node rotLR(node h,char modo){
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
node rotRL(node h, char modo){
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
int balance(node h, char modo) {
        if(h == NULL){
                return 0;
        }
        return modo ? height(h->alfaLeft,modo) - height(h->alfaRight,modo) :\
                height(h->orderLeft,modo) - height(h->orderRight,modo);
}



/* Verifica se e necessario fazer rotates numa arvore dependendo do modo*/
node AVLbalance(node h, char modo){
        int balanceFactor, hleft, hright;
        node left,right;
        if (h == NULL) {
                return h;
        }
        left = modo ? h->alfaLeft : h->orderLeft;
        right = modo ? h->alfaRight : h->orderRight;
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
short findFunc(node c1,char modo, buff* bf){
        short res;
        if (modo){ /* comparar nomes*/
                res = compareAlfaBuff(getAlfa(c1),bf);
        } else {
                res = compareOrder(buffOrder(bf),getOrder(c1));

        }
        return res;
}


/* Devolve a componente com as mesmas caracteristicas do buffer
 * Se nao encontrar, devolve NULL
 * modo 1 -> procurar por alfa
 * modo 0 -> procurar por order*/
node findComp(node root, char modo, buff* bf){
        static short res;
        if (root==NULL) return root;
        res = findFunc(root,modo,bf);
        if (!res){
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


/* Insere o node com as caracteristicas guardadas no buffer,
 * faz os rotates necessarios. Devolve um pointer para a componente inserida
 * Se ja existir devolve o seu ponteiro
 * modo 1 -> procurar por nome
 * modo 0 -> procurar por ordem de chegada*/
node insertComp(node root, char modo,char* exists, mother* M){
        static short res;
        if (root == NULL){
                if (modo){ /*só se cria a componente quando modo=1*/
                        nodeToBuff(initComp(M),getMotherBuff(M));
                }
                return getBuffNode(getMotherBuff(M));
        }
        if (modo){
                res = findFunc(root,modo,getMotherBuff(M));
                if (!res){
                        *exists = ONE;
                        nodeToBuff(root,getMotherBuff(M));
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



/* Insere uma node nova nas AVL's por order e por 
 * alfa. Se ja existir, devolve o node*/
node insertAll(avlHead* root, mother* M){
        char exists=ZERO;
        root->rootAlfa = insertComp(root->rootAlfa,ONE,&exists,M);
        if (!exists){ /* Se a componente ainda nao existir*/
                root->rootOrder=insertComp(root->rootOrder,ZERO,&exists,M);
                (root->occ)+=ONE; /*Ocupacao da avl aumentou*/
        }
        return getBuffNode(getMotherBuff(M));
}




/* Funcao auxiliar do delete, que devolve o novo
 * caminho quando removemos uma node da AVL*/
node deleteAux(node c1,char modo, buff* bf){
        if (c1!=NULL){
                if (!findFunc(c1,modo,bf)){
                        if (modo){
                                c1 = c1->alfaLeft;
                        } else {
                                c1 = c1->orderLeft;
                        }
                } else {
                        if (modo){
                                c1->alfaLeft = deleteAux(c1->alfaLeft,modo,bf);
                                c1->alfaRight =
                                        deleteAux(c1->alfaRight,modo,bf);
                        } else {
                                c1->orderLeft =
                                        deleteAux(c1->orderLeft,modo,bf);
                                c1->orderRight =
                                        deleteAux(c1->orderRight,modo,bf);
                        }
                c1 = AVLbalance(c1,modo);
                }
        }
        return c1;

}


/* Delete a uma node (cujo nome esta no buffer) 
 * da AVL por alfa */
node delete1(node root, char* exists, buff* bf){
        static short res;
        static node aux;
        if (root==NULL){
                *exists = ZERO; /*nao existe*/
                return root;
        }
        res = findFunc(root,ONE,bf);
        if (res<0){
                root->alfaLeft = delete1(root->alfaLeft,exists,bf);
        } else if (res>0){
                root->alfaRight = delete1(root->alfaRight,exists,bf);
        } else { /*encontrou-se o componente a apagar*/
                aux = root;
                if (root->alfaLeft!=NULL && root->alfaRight!=NULL){
                        root = max(root->alfaLeft,ONE);
                        cpyAlfa(bf,getAlfa(root)); /*copia o Alfa para o buff*/
                        setSizeBuffStart(bf,ZERO);
                        root->alfaLeft = deleteAux(aux->alfaLeft,ONE,bf);
                        root->alfaRight = deleteAux(aux->alfaRight,ONE,bf);
                } else {
                        if (root->alfaLeft==NULL && root->alfaRight==NULL){
                                root = NULL;
                        } else if (root->alfaLeft==NULL){
                                root = root->alfaRight;
                        } else {
                                root = root->alfaLeft;
                        }
                }
                /* Guardar o order da antiga root, para a apagar depois*/
                orderToBuff(getOrder(aux),bf);
                nodeToBuff(aux,bf);
        }
        root = AVLbalance(root,ONE);
        return root;
}

/* Delete a uma componente (cujo nome esta no buffer) 
 * da AVL ordenada por criacao */
node delete2(node root, buff* bf){
        static short res;
        static node aux;

        if (root==NULL) {
                printf("Alguma coisa está mal, não devia estar aqui\n");
                return root;
        }
        res = findFunc(root,ZERO,bf);
        if (res<0){
                root->orderLeft = delete2(root->orderLeft,bf);
        } else if (res>0){
                root->orderRight = delete2(root->orderRight,bf);
        } else { /*encontrou-se o componente a apagar*/
                aux = root;
                if (root->orderLeft!=NULL && root->orderRight!=NULL){
                        root = max(root->orderLeft,ZERO);
                        orderToBuff(root->occ,bf);
                        root->orderLeft = deleteAux(aux->orderLeft,ZERO,bf);
                        root->orderRight = deleteAux(aux->orderRight,ZERO,bf);
                } else {
                        if (root->orderLeft==NULL && root->orderRight==NULL){
                                root = NULL;
                        } else if (root->orderLeft==NULL){
                                root = root->orderRight;
                        } else {
                                root = root->orderLeft;
                        }
                }
                /* Agr apagamos o componente*/
                freeCompR(aux);
        }
        root = AVLbalance(root,ZERO);
        return root;
}



/* Delete de um componente das duas AVL's
 * O nome do componente para apagar esta no buffer*/
avlHead* deleteComp(avlHead *head, mother *M){
        char exists = ONE; /*controla se o que queremos apagar existe*/
        head->rootAlfa = delete1(head->rootAlfa,&exists,getMotherBuff(M));
        if (exists){
                if (!compValNull(getBuffNode(getMotherBuff(M)))){
			/* neste programa tambem havera um node na Hash da mother*/
                        removeFromHash(getBuffNode(getMotherBuff(M)), getMotherHash(M));
                }
                head->rootOrder = delete2(head->rootOrder,getMotherBuff(M));
        } else {
                printf(NOT_FOUND);
        }

        return head;
}




/* Faz free a uma avlHead, depois de o fazer para os seus componentes*/
void freeHead(avlHead *head){
        if (head->occ){ /*tem componentes filho*/
                avlPostOrder(freeCompR,head->rootOrder);
        }
        free(head);

}



/* Travessia in-order da AVL alfabetica, com uma funcao a correr*/
void avlSortAlfa(void (*f)(node),node c1){
        if (c1==NULL){
                return;
        }
        avlSortAlfa(f,c1->alfaLeft);
        (*f)(c1);
        avlSortAlfa(f,c1->alfaRight);
}


/* Travessia in-order da AVL por criacao, com uma funcao a correr
 * Sem condicao de paragem*/
void avlSortOrderDeep(void (*f)(node),node c1){
        if (c1==NULL) return;
        avlSortOrderDeep(f,c1->orderLeft);
        (*f)(c1);
        avlSortOrderDeep(f,c1->orderRight);
}

/* Travessia post-order da AVL por criacao, com uma funcao a correr*/
void avlPostOrder(void (*f)(node),node c1){
        if (c1==NULL){
                return;
        }
        avlPostOrder(f,c1->orderLeft);
        avlPostOrder(f,c1->orderRight);
        (*f)(c1);
}

