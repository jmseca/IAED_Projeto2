/*
 * Ficheiro: proj2.h
 * Autor: Joao Fonseca
 * Descricao: Ficheiro header do projeto. Contem todas as declaracoes das
 * funcoes, as definicoes dos struct e as constantes.
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Comandos e a sua respetiva descricao*/
#define COMANDOS "help: Imprime os comandos disponíveis.\n"\
        "quit: Termina o programa.\n"\
        "set: Adiciona ou modifica o valor a armazenar.\n"\
        "print: Imprime todos os caminhos e valores.\n"\
        "find: Imprime o valor armazenado.\n"\
        "list: Lista todos os componentes imediatos de um sub-caminho.\n"\
        "search: Procura o caminho dado um valor.\n"\
        "delete: Apaga um caminho e todos os subcaminhos.\n"

/*Tamanho maximo de uma string que identifica um comando (inclui '\0')*/
#define MAX_COMMAND_SIZE 7

/*Tamanho para o buffer que ira receber o caminho/valor (inclui '\0')*/
#define BUFF_SIZE 65532

/*Comandos ID*/
#define HELP 425
#define QUIT 451
#define SET 332
#define PRINT 441
#define FIND 417
#define LIST 444
#define SEARCH 427
#define DELETE 410


/*Complement*/

char cleanWhite();

short notWhite(char c);

short inputGetNameW(char out[]);

void pathClean(char* path, unsigned short *ind);

unsigned short findSepar(char* path, unsigned short ind);

void myStrCpy(char* dest, char* src, unsigned short start, unsigned short end);

short myStrCmp(char* s1, char* s2, unsigned short start, unsigned short end);

/*DELETE*/
void myPrint(char* s1, unsigned short start, unsigned short end);

/*STRUCTS*/

typedef struct {
	char* command;
	char* bigBuff;
} buff ;



/*Buffer*/

buff* initBuffer();

void commandToBuff(buff *bf);

void pathToBuff(buff *bf, short modoB);

void valToBuff(buff *bf);

void resetBuff(buff *bf);

short nullBuff(buff* bf);

void freeBuffer(buff *bf);

void addToBuff(buff* bf, comp* c1);

void removeFromBuff(buff*, comp* c1);






/*Funcoes dos Comandos*/

short commandId(char* str);

short checkCommand(buff *bf,comp* root);

void handleHelp();

void handleQuit(buff *bf, comp* root);

void handleSet(buff *bf, comp* root);

void handlePrint(buff *bf,comp* root);

void handleFind(buff *bf,comp* root);

void handleList(buff *bf, comp* root);
