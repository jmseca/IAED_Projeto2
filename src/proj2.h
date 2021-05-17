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


/*Primeiro char ASCII que pode representar um valor ou componente*/
#define FIRST_ASCII 33

/*Dim das Tabelas de Dispersao para armazenar as componentes alfabeticamente*/
#define HASH_MAX 12

/*Tamanho inicial dos vetores que terao componentes por ordem de criacao*/
#define FIRST_SIZE_C 20

/*Tamanho inicial dos vetores que farao parte das Tabelas de Dispersao*/
#define FIRST_SIZE_H 8

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


/*Buffer*/

typedef struct {
	char* command;
	char* bigBuff;
} buff ;


buff* initBuffer();

void commandToBuff(buff *bf);

void pathToBuff(buff *bf);

void valToBuff(buff *bf);

void freeBuffer(buff *bf);


/*Vetores de Ponteiros de Componentes (vpc) e Componentes*/

typedef struct {
	unsigned long *size;
	unsigned long *occ;
	struct componente **info;
} vpc;


typedef struct componente{
        char* valor;
        char* nome;
        vpc** hash;
        vpc* primeiros;
} comp;


vpc* initVpc(short firstSize);

vpc* extendVpc(vpc *vetor);

comp* initRoot();

comp* initComp(char* path, unsigned short start, unsigned short end);

short compValNull(comp *c1);

void compNewValue(comp* c1, char* val);

void printCompVal(comp *c1);

void updateVpc(comp *c1, vpc *vetor, unsigned long ind);

void addToHashVpc(comp* cNew,vpc* vetor,unsigned long ind);

void addToFirstVpc(comp* cNew, vpc* vetor);

unsigned long getBinInd(unsigned long *size, unsigned long ind,
                short up, unsigned long maxInd);

short getBinRes(char *cName, vpc *vetor, long ind,unsigned short start,
                unsigned short end);

unsigned long binarySearch(char *cName, vpc *vetor, short *found,
                unsigned short start, unsigned short end);

comp* addNewComp(comp *c1, char* path, vpc *vetorHash, unsigned long ind,
                unsigned short start, unsigned short end);

comp* belongsToComp(comp *c1, char *path, short *found,
                unsigned short start, unsigned short end);

comp* getPathComp(char* path, comp* root);

void freeVpc(vpc* vetor);

void freeHash(vpc** hash);

void freeHash(vpc** hash);

void freeCompRec(comp* c1);



/*Funcoes dos Comandos*/

short commandId(char* str);

short checkCommand(buff *bf,comp* root);

void handleHelp();

void handleQuit(buff *bf, comp* root);

void handleSet(buff *bf, comp* root);




