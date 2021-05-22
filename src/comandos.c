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
			break;
		case QUIT:
                        handleQuit(M);
                        *control=ONE;
                        break;
		case SET:
			handleSet(M);
			break;
		case PRINT:
			handlePrint(M);
			break;
		case FIND:
			handleFind(M);
			break;
		case LIST:
			handleList(M);
			break;
		case SEARCH:
			handleSearch(M);
			break;
		case DELETE:
			handleDelete(M);
			break;
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


/*==========    QUIT    ==========*/

/*Funcao responsavel por terminar o programa corretamente*/
void handleQuit(mother *M){
        cleanWhite();
	freeMother(M);
}

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
}



/*==========    PRINT    ==========*/

/* Responsavel por imprimir todos os valores e caminhos quando o programa
 * recebe a instrucao "print"*/
void handlePrint(mother *M){
	cleanWhite();
	resetBuff(M->bf);
	avlSortOrderDeep(printCompsR,M->motherRoot->rootOrder,M->bf);	
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
void handleList(mother *M){
	comp *cpath;
	char modo=ONE;
        char modoB=ONE; /*Pode nao haver um path no stdin*/
	pathToBuff(M->bf,modoB);
	if (nullBuff(M->bf)){ /*"list" invocado sem argumentos*/
		avlSortAlfa(printCompName,M->motherRoot->rootAlfa);	
		/*Se for null, entao ja se verificou que nao havia mais input*/
	} else {
		cpath = getPathComp(modo,M);
		avlSortAlfa(printCompName,cpath->follow->rootAlfa);
		cleanWhite();
	}

}	


/*==========    SEARCH    ==========*/
/* Responsavel pela execucao do programa no comando "search"
 * Devolve o primeiro caminho com o valor recebido no stdin*/
void handleSearch(mother *M){
	resetBuff(M->bf);
	valToBuff(M->bf);
	buffStart(M->bf); /* fazer reset à condicao de paragem*/
	avlSortOrderStop(findValueR,M->motherRoot->rootOrder,M->bf);	
	if (!buffCheckStop(M->bf)){ /*nao encontrou caminho*/
		printf("not found\n");
	}
}


/*==========    DELETE    ==========*/
/* Responsavel pela execucao do programa no comando "delete"
 * Apaga o caminho recebido no stdin e todos os seus componentes filho*/
void handleDelete(mother *M){
	avlHead *head;
        char modoB=ONE; /*Pode nao haver um path no stdin*/
        pathToBuff(M->bf,modoB);
        if (nullBuff(M->bf)){ /*"delete" invocado sem argumentos*/
                avlPostOrder(freeCompR,M->motherRoot->rootOrder); 
		/*Se for null, entao ja se verificou que nao havia mais input*/
        } else {
		buffSwitchComp(M->bf);
                head = getDeleteAVL(M);
		if (head!=NULL){
			/*Agr passa-se o valor do componente para bigBuff*/
			strcpy(M->bf->bigBuff,M->bf->bigBuff2);
			setSizeBuffStart(M->bf,ZERO);
			head = deleteComp(head,M->bf);
		}
                cleanWhite();
        }

}


