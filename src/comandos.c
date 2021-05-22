/*
 * Ficheiro: comandos.c
 * Autor: Joao Fonseca
 * Descricao: Definicao das funcoes que tratam de cada comando,
 * tal como as suas funcoes auxiliares.
 *
*/

#include "proj2.h"

/*==========    CHECK COMMAND    ==========*/

/*Devolve um inteiro que identifica um comando*/
short commandId(char* str){
        return *(str)+ *(str+1)+*(str+2)+*(str+3);
}

/* Funcao que, com base no comando indicado, direciona a execucao
 *do programa para realizar o comando pretendido
 * Tambem indica se o programa ja acabou (1) ou nao (0)*/
void checkCommand(mother *M, char* control){
	short id = commandId(M->bf->command);
	switch (id){
		case HELP:
			handleHelp();
			*control = ZERO; /*Obrigatorio APAGAR ANTES DE ENTREGAAAAAAAAR*/
			break;
		case SET:
			handleSet(M);
			break;
		case PRINT:
			handlePrint(M);
			break;
		/*case FIND:
			handleFind(bf, root);
			break;
		case LIST:
			handleList(bf, root);
			break;
		case SEARCH:
			handleSearch(bf, root);
			break;
		case DELETE:
			handleDelete(bf, root);
			break;
		case QUIT:
                        handleQuit(bf, root);
                        *control=ONE;
                        break;*/
		default:
			printf("Erro Fatal - checkCommand\n");
	}

}

/*==========    HELP    ==========*/

/*Funcao responsavel por imprimir todos os comandos disponiveis*/
void handleHelp(){
	cleanWhite(); /*nao ha mais info na instrucao, limpa-se o input*/	
	printf(COMANDOS);
}


/*==========    QUIT    ==========

Funcao responsavel por terminar o programa corretamente
void handleQuit(mother *M){
        cleanWhite(); nao ha mais info na instrucao, limpa-se o input
	freeBuffer(bf);
	freeCompRec(root);
}
*/

/*==========    SET    ==========*/

/* Funcao responsavel por adicionar ou modificar um valor de um caminho,
 *sempre que o comando "set" e recebido no stdin*/
void handleSet(mother *M){
        comp *cpath;
	/* Controla se o progama teve erros (apesar de nao se aplicar)
	char succ=ONE; */
	char modo=ZERO; /* Se o caminho nao existir, cria*/
	char modoB=ZERO; /*Vai haver um path no stdin*/
        pathToBuff(M->bf,modoB);
	cpath = getPathComp(modo,M);
	valToBuff(M->bf);
	compNewValue(cpath,M);
	printf("O que tem a RootAlfa?\nRootAlfa = %s\n",M->motherRoot->rootAlfa->nome);
}



/*==========    PRINT    ==========*/

/* Responsavel por imprimir todos os valores e caminhos quando o programa
 * recebe a instrucao "print"*/
void handlePrint(mother *M){
	cleanWhite();
	resetBuff(M->bf);
	avlSortOrder(printCompsR,M->motherRoot->rootOrder,M->bf);
	/*aqui tenho de chamar o avlsortorder em vez do prinComps*/
}


/*==========    FIND    ==========*/

/* Imprime o valor assocido ao caminho quando o programa recebe
 *a instrucao "find"*/
void handleFind(mother* M){
	comp* cpath;
	/*char succ=ONE; Controla se o programa teve erros*/
	char modo=ONE; /* Se o caminho nao existir, ha erro*/
	char modoB=ZERO; /*Vai haver um path no stdin*/
	pathToBuff(M->bf,modoB);
	cpath = getPathComp(modo,M);
	if (cpath!=NULL){ 
		printCompVal(cpath);
	}
	cleanWhite();
}


/*==========    LIST    ==========*/

/* Responsavel pela execucao do programa no comando "list"
 * Lista todos os componentes imediatos de um subcaminho*/
/*void handleList(buff *bf,comp* root){*/
	/*comp *cpath;*/
	/*short succ=1;
	short modo=1;
        short modoB=1; Pode nao haver um path no stdin
        pathToBuff(bf,modoB);
	if (nullBuff(bf)){ invocado sem argumentos
		printf("nao era suposto estar aqui\n")listComp(root);
	} else {
		cpath = getPathComp(bf->bigBuff,root,modo,&succ);
		listComp(cpath);	
	}
	if (!nullBuff(bf)){
		cleanWhite();
	}*/ /*Se for null, entao ja se verificou que nao havia mais input	
}*/

