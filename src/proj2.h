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

/*0 e 1*/
#define ZERO 0
#define ONE 1

/*Tamanhos de alguns tipos de dados*/
#define SHORT 2
#define INT 4
#define LONG 8
#define AVLHEAD 24
#define COMP 96

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

#define HASH_SIZE 3571 /*500º Primo*/

#define APAGAR "FGsxL@bOZGfNLGV"
#define APAGAR2 "1517"

/*STRUCTS*/

typedef struct {
        char* command;
        char* bigBuff; 
	char* bigBuff2;
	struct componente *c;
	unsigned short start;
	unsigned short end;
	unsigned long occ;
} buff ;

typedef struct {
	unsigned long occ;
	struct componente *rootAlfa;
	struct componente *rootOrder;
} avlHead;

typedef struct componente {
	char* nome;
	char* valor;
	unsigned long occ;
	unsigned short alfaHeight;
	unsigned short orderHeight;
	struct componente *alfaRight;
	struct componente *alfaLeft;
	struct componente *orderRight;
	struct componente *orderLeft;
	avlHead* follow;
	struct componente *motherComp;
	struct componente *nextValue;
	unsigned short prof;
} comp;

typedef struct {
        comp **tabela;
        unsigned long hSize;
} hash;

/* Estrutura para guardar o buffer a raiz e a hash*/
typedef struct {
	buff* bf;
	avlHead *motherRoot;
	hash* h;
} mother;

/*Complement*/

void endProgram(mother* M);

void* myMalloc(short typeSize, unsigned int vSizei, char* control);

char cleanWhite();

short notWhite(char c);

char notEndPath(char c);

short inputGetNameW(char out[]);

void pathClean(char* path, unsigned short *ind);

unsigned short findSepar(char* path, unsigned short ind);

void myStrCpy(char* dest, buff* bf);

short myStrCmp(char* s1, buff* bf);

/*DELETE*/
void myPrint(char* s1, unsigned short start, unsigned short end);

/*Hash*/

hash* initHash();

hash* addToHash(hash *h,comp* c1);

comp* getFirstHashEl(hash *h, comp* c1);

unsigned long hashU(char *v, unsigned long M);

long coef(comp* c1,comp* c2);

char compInsertOrder(comp *c1, comp *c2);

comp* getItem(char* value,mother *M);

void freeHash(hash* h);

void removeFromHash(comp* c1, hash* h);

comp* removeFromHashAux(comp *c1, comp *c2);

/*Buffer*/

buff* initBuffer();

void commandToBuff(buff *bf);

void pathToBuff(buff *bf, short modoB);

void valToBuff(buff *bf);

void resetBuff(buff *bf);

short nullBuff(buff* bf);

unsigned int getVsize(buff* bf);

void setSizeBuffStart(buff* bf,char modo);

void compToBuff(comp* c1, buff* bf);

comp* getBuffComp(buff* bf);

void occToBuff(unsigned long occ, buff* bf);

void buffStart(buff* bf);

void buffStop(buff* bf);

char buffCheckStop(buff* bf);

unsigned long getBuffOcc(buff* bf);

void freeBuffer(buff *bf);

void addToBuff(buff* bf, comp* c1);

void removeFromBuff(buff* bf);

void buffSwitchComp(buff* bf);


/* AVL + Componentes*/

avlHead* initHead(char* control);

comp* initComp(mother* M);

unsigned short getCompProf(comp* c1);

mother* initMother();

void freePreComp(comp *c1);

unsigned short height(comp* h, char modo);

comp* rotL(comp* h, char modo);

comp* rotR(comp* h, char modo);

comp* max(comp* h, char modo);

comp* rotLR(comp* h,char modo);

comp* rotRL(comp* h, char modo);

int balance(comp* h, char modo);

comp* AVLbalance(comp* h, char modo);

short findFunc(comp *c1, char modo, buff* bf);

comp* findComp(comp* root, char modo, buff* bf);

comp* insertComp(comp* root, char modo,char* exists, mother* M);

comp* insertAll(avlHead* root, mother* M);

comp* deleteAux(comp *c1, char modo, buff* bf);

comp* delete1(comp* root, char* exists, buff* bf);

comp* delete2(comp* root, buff* bf);

avlHead* deleteComp(avlHead *head, mother *M);

void compNewValue(comp* c1, mother* M);

short compValNull(comp *c1);

void printCompVal(comp *c1);

void printCompName(comp* c1);

void printPath(comp* c1);

comp* getPathComp(short modo, mother* M);

avlHead* getDeleteAVL(mother* M);

void avlSortAlfa(void (*f)(comp*),comp* c1);

void avlSortOrderDeep(void (*f)(comp*,buff*),comp* c1,buff* bf);

void avlSortOrderStop(void (*f)(comp*,buff*),comp* c1,buff* bf);

void avlPostAlfa(void (*f)(comp*),comp* c1); 

void avlPostOrder(void (*f)(comp*),comp* c1);

void printComp(comp *c1, buff *bf);

void printCompsR(comp* c1, buff* bf);

void findValueR(comp* c1, buff* bf);

void freeHead(avlHead *head);

void freeCompR(comp *c1);

void freeMother(mother *M);

/*Funcoes dos Comandos*/

short commandId(char* str);

void checkCommand(mother* M,char* control);

void handleHelp();

void handleQuit(mother *M);

void handleSet(mother *M);

void handlePrint(mother *M);

void handleFind(mother *M);

void handleList(mother *M);

void handleSearch(mother *M);

void handleDelete(mother *M);
