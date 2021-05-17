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
		/*case PRINT:
			handlePrint(bf, root);
			break;
		case FIND:
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
			break;*/
		default:
			printf("Erro Fatal - checkCommand");
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
	pathToBuff(bf);
	cpath = getPathComp(bf->bigBuff,root);
	valToBuff(bf);
	compNewValue(cpath,bf->bigBuff);
}







