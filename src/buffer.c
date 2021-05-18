/*
 * Ficheiro: buffer.c
 * Autor: Joao Fonseca
 * Descricao: Definicao das funcoes que manipulam a estrutura
 * de dados buffer, que sera necessaria para receber o stdin
*/

#include "proj2.h"

/* Inicializa uma estrutura buffer, alocando-lhe memoria*/
buff* initBuffer(){
	buff* bf;
	bf = (buff*) malloc(sizeof(buff));
	bf->command = (char*) malloc(sizeof(char)*MAX_COMMAND_SIZE);
	bf->bigBuff = (char*) malloc(sizeof(char)*BUFF_SIZE);
	return bf;
}


/* Guarda no buffer o comando recebido pelo input*/
void commandToBuff(buff *bf){
	scanf("%s",bf->command);
	
}

/* Guarda no buffer o caminho recebido pelo input*/
void pathToBuff(buff *bf){
	scanf("%s",bf->bigBuff);
}

/* Guarda no buffer o valor recebido pelo input*/
void valToBuff(buff *bf){
	inputGetNameW(bf->bigBuff);
}

/* Coloca bigBuff a Null String*/
void resetBuff(buff *bf){
	*(bf->bigBuff) = '\0';
}

void freeBuffer(buff *bf){
	free(bf->command);
	free(bf->bigBuff);
	free(bf);
}

/* Comandos para o printAll (onde usamos o bigBuff)*/

/* Adiciona ao bigBuff o nome da componente no fim*/
void addToBuff(buff* bf, comp* c1){
	unsigned short i=0;
	unsigned short a=0;
	for (;bf->bigBuff[i]!='\0';i++){;}
	if (!isRoot(c1)){
		bf->bigBuff[i++]='/'; /*1o addiciona-se o separador*/
	} /* No print, isto so ira acontecer na root*/
	do {
		bf->bigBuff[i++] = c1->nome[a];
	} while (c1->nome[a++] != '\0');
}


void removeFromBuff(buff* bf, comp* c1){
	unsigned short i=0;
	unsigned short a=0;
	for (;bf->bigBuff[i]!='\0';i++){;}
	for (;c1->nome[a]!='\0';a++){;}
	i=i-a+1;
	bf->bigBuff[i] = '\0';

}
