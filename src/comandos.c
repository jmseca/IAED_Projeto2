/*
 * Ficheiro: comandos.c
 * Autor: Joao Fonseca
 * Descricao: Definicao das funcoes que tratam de cada comando.
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
	short id = commandId(M->bf->bigBuff);
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
        node cpath;
	char modo=ZERO; /* Se o caminho nao existir, cria*/
	char modoB=ZERO; /*Vai haver um path no stdin*/

	pathToBuff(M->bf,modoB);
	nodeToBuff(NULL,getMotherBuff(M));
	cpath = getPathComp(modo,M);
	valToBuff(M->bf);
	compNewValue(cpath,M);
	if (!compValNull(cpath)){
		if (cpath->nextValue != NULL){ /*ja foi inserido*/
			removeFromHash(cpath,getMotherHash(M));	
		}	
		cpath->nextValue = getFirstHashEl(getMotherHash(M), cpath);
		M->h = addToHash(getMotherHash(M),cpath);
	}	
}



/*==========    PRINT    ==========*/

/* Responsavel por imprimir todos os valores e caminhos quando o programa
 * recebe a instrucao "print"*/
void handlePrint(mother *M){
	cleanWhite();
	resetBuff(getMotherBuff(M));
	avlSortOrderDeep(printMaster,getMotherHead(M)->rootOrder);
}


/*==========    FIND    ==========*/

/* Imprime o valor assocido ao caminho quando o programa recebe
 *a instrucao "find"*/
void handleFind(mother* M){
	node cpath;
	char modo=ONE; /* Se o caminho nao existir, ha erro*/
	char modoB=ZERO; /*Vai haver um path no stdin*/
	pathToBuff(getMotherBuff(M),modoB);
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
	node cpath;
	char modo=ONE;
        char modoB=ONE; /*Pode nao haver um path no stdin*/
	pathToBuff(getMotherBuff(M),modoB);
	if (nullBuff(getMotherBuff(M))){ /*"list" invocado sem argumentos*/
		avlSortAlfa(printCompName,getMotherHead(M)->rootAlfa);	
		/*Se for null, entao ja se verificou que nao havia mais input*/
	} else {
		cpath = getPathComp(modo,M);
		if (cpath!=NULL){
			avlSortAlfa(printCompName,getCompFollow(cpath)->rootAlfa);
		}
	}

}	


/*==========    SEARCH    ==========*/
/* Responsavel pela execucao do programa no comando "search"
 * Devolve o primeiro caminho com o valor recebido no stdin*/
void handleSearch(mother *M){
	node path;
	resetBuff(getMotherBuff(M));
	valToBuff(getMotherBuff(M));
	path = getItem( getBuff2(getMotherBuff(M)) ,M);
	if (path==NULL){
		printf(NOT_FOUND);
	} else {
		printPath(path);
		printf("\n"); 
	}

}


/*==========    DELETE    ==========*/
/* Responsavel pela execucao do programa no comando "delete"
 * Apaga o caminho recebido no stdin e todos os seus componentes filho*/
void handleDelete(mother *M){
	avlHead *head;
        char modoB=ONE; /*Pode nao haver um path no stdin*/
        pathToBuff(getMotherBuff(M),modoB);	
        if (nullBuff(getMotherBuff(M))){ /*"delete" invocado sem argumentos*/
                avlPostOrder(freeCompR,getMotherHead(M)->rootOrder);
		modoB = ZERO; /*reutilizacao da var*/
		free(getMotherHead(M));
		M->motherRoot = initHead(&modoB);
        } else {
		buffSwitchComp(M->bf);
                head = getDeleteAVL(M);
		if (head!=NULL){
			/*Agr passa-se o valor do componente para bigBuff*/
			cpyBuffs(getMotherBuff(M));	
			setSizeBuffStart(getMotherBuff(M),ZERO);
			head = deleteComp(head,M);
		}
        }

}


