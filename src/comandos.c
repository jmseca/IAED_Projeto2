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
short checkCommand(buff *bf, comp* root){
	short id = commandId(bf->command);
	short out=0;
	switch (id){
		case HELP:
			handleHelp();
			break;
		case QUIT:
			handleQuit(bf, root);
			out=1;
			break;
		case SET:
			handleSet(bf, root);
			break;
		case PRINT:
			handlePrint(bf, root);
			break;
		case FIND:
			handleFind(bf, root);
			break;
		case LIST:
			handleList(bf, root);
			break;
		/*case SEARCH:
			handleSearch(bf, root);
			break;
		case DELETE:
			handleDelete(bf, root);
			break;*/
		default:
			printf("Erro Fatal - checkCommand\n");
	}
	return out;

}

/*==========    HELP    ==========*/

/*Funcao responsavel por imprimir todos os comandos disponiveis*/
void handleHelp(){
	cleanWhite(); /*nao ha mais info na instrucao, limpa-se o input*/	
	printf(COMANDOS);
}


/*==========    QUIT    ==========*/

/*Funcao responsavel por terminar o programa corretamente*/
void handleQuit(buff *bf, comp* root){
        cleanWhite(); /*nao ha mais info na instrucao, limpa-se o input*/
	freeBuffer(bf);
	freeCompRec(root);
}


/*==========    SET    ==========*/

/* Funcao responsavel por adicionar ou modificar um valor de um caminho,
 *sempre que o comando "set" e recebido no stdin*/
void handleSet(buff *bf,comp* root){
        comp *cpath;
	short succ=1;
	short modo=0;
	short modoB=0; /*Vai haver um path no stdin*/
        pathToBuff(bf,modoB);
	cpath = getPathComp(bf->bigBuff,root,modo,&succ);
	valToBuff(bf);
	compNewValue(cpath,bf->bigBuff);
}



/*==========    PRINT    ==========*/

/* Responsavel por imprimir todos os valores e caminhos quando o programa
 * recebe a instrucao "print"*/
void handlePrint(buff *bf,comp* root){
	cleanWhite();
	resetBuff(bf);
	printAll(root,bf);


}


/*==========    FIND    ==========*/

/* Imprime o valor assocido ao caminho quando o programa recebe
 *a instrucao "find"*/
void handleFind(buff *bf,comp* root){
	comp* cpath;
	short succ=1; /*Controla se o programa teve erros*/
	short modo=1; /* Se o caminho nao existir, ha erro*/
	short modoB=0; /*Vai haver um path no stdin*/
	pathToBuff(bf,modoB);
	cpath = getPathComp(bf->bigBuff,root,modo,&succ);
	if (succ){
		if (compValNull(root)){
                printf("no data\n");
        	} else {
			printCompVal(cpath);
        	}
	}
	cleanWhite();
}


/*==========    LIST    ==========*/

/* Responsavel pela execucao do programa no comando "list"
 * Lista todos os componentes imediatos de um subcaminho*/
void handleList(buff *bf,comp* root){
	comp *cpath;
	short succ=1;
	short modo=1;
        short modoB=1; /*Pode nao haver um path no stdin*/
        pathToBuff(bf,modoB);
	if (nullBuff(bf)){ /*invocado sem argumentos*/
		listComp(root);
	} else {
		cpath = getPathComp(bf->bigBuff,root,modo,&succ);
		listComp(cpath);	
	}
	if (!nullBuff(bf)){
		cleanWhite();
	} /*Se for null, entao ja se verificou que nao havia mais input*/	
}

