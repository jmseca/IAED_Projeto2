/*
 * Ficheiro: proj2.h
 * Autor: Joao Fonseca
 * Descricao: Ficheiro header do projeto. Contem todas as declaracoes das
 * funcoes, as definicoes dos struct e as constantes.
*/

#ifndef _PROJ_2_
#define _PROJ_2_


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

/*Mensagens de erro*/
#define NOT_FOUND "not found\n"
#define NO_DATA "no data\n"


/*0 e 1*/
#define ZERO 0
#define ONE 1

/*Tamanhos de alguns tipos de dados*/
#define AVLHEAD 24
#define COMP 96

/*Tamanho para o buffer que ira receber o caminho/valor (inclui '\0')*/
#define BUFF_SIZE 65533

/*Comandos ID*/
#define HELP 425
#define QUIT 451
#define SET 332
#define PRINT 441
#define FIND 417
#define LIST 444
#define SEARCH 427
#define DELETE 410

/* Tamanho da Hash Table que vamos usar*/
#define HASH_SIZE 1000003 


/*STRUCTS*/

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
        struct head *follow;
        struct componente *motherComp;
        struct componente *nextValue;
        unsigned short prof;
} comp;


typedef struct componente* node;

typedef struct {
        char* bigBuff; 
	char* bigBuff2;
	node c;
	unsigned short start;
	unsigned short end;
	unsigned long occ;
} buff ;

typedef struct head {
	unsigned long occ;
	node rootAlfa;
	node rootOrder;
} avlHead;


typedef struct {
        node *tabela;
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

char nullStr(char* str);

short inputGetNameW(char out[]);

void pathClean(char* path, unsigned short *ind);

unsigned short findSepar(char* path, unsigned short ind);

void myStrCpy(char* dest, buff* bf);

short myStrCmp(char* s1, buff* bf);
/*for testing*/
void myPrint(char* s1, unsigned short start, unsigned short end);


/*Componentes (e Node)*/

node initComp(mother* M);

unsigned short calculProf(node c1);

avlHead* getCompFollow(node c1);

void freePreComp(node c1);

void compNewValue(node c1, mother* M);

char compValNull(node c1);

void printCompVal(node c1);

void printCompName(node c1);

void printPath(node c1);

void printMaster(node c1);

node getPathComp(short modo, mother* M);

avlHead* getDeleteAVL(mother* M);

void freeCompR(node c1);

/*--node--*/

unsigned long getOrder(node c1);

char* getAlfa(node c1);

char* getValue(node c1);

short compareAlfaBuff(char* alfa,buff* bf);

void cpyAlfa(buff* bf, char *alfa);

char compareOrder(unsigned long order1, unsigned long order2);

unsigned short getProf(node c1);

node getMotherNode(node c1);

node getNextValue(node c1);

node removeFromHashAux(node c1, node c2);


/*Hash*/

hash* initHash();

unsigned long getHashSize(hash* h);

hash* addToHash(hash *h,node c1);

node getFirstHashEl(hash *h, node c1);

unsigned long hashU(char *v, unsigned long M);

long coef(node c1,node c2);

char compInsertOrder(node c1, node c2);

node getItem(char* value,mother *M);

void freeHash(hash* h);

void removeFromHash(node c1, hash* h);


/*Buffer*/

buff* initBuffer();

void nodeToBuff(node c1, buff* bf);

node getBuffNode(buff* bf);

char* getBuff(buff* bf);

char* getBuff2(buff* bf);

unsigned short getBuffStart(buff* bf);

unsigned short getBuffEnd(buff* bf);

void cpyBuffs(buff* bf);

void commandToBuff(buff *bf);

void pathToBuff(buff *bf, short modoB);

void valToBuff(buff *bf);

void resetBuff(buff *bf);

short nullBuff(buff* bf);

unsigned int getVsize(buff* bf);

void setSizeBuffStart(buff* bf,char modo);

void orderToBuff(unsigned long occ, buff* bf);

unsigned long buffOrder(buff* bf);

void freeBuffer(buff *bf);

void buffSwitchComp(buff* bf);


/* AVL + Componentes*/

avlHead* initHead(char* control);

unsigned short height(node h, char modo);

node rotL(node h, char modo);

node rotR(node h, char modo);

node max(node h, char modo);

node rotLR(node h,char modo);

node rotRL(node h, char modo);

int balance(node h, char modo);

node AVLbalance(node h, char modo);

short findFunc(node c1, char modo, buff* bf);

node findComp(node root, char modo, buff* bf);

node insertComp(node root, char modo,char* exists, mother* M);

node insertAll(avlHead* root, mother* M);

node deleteAux(node c1, char modo, buff* bf);

node delete1(node  root, char* exists, buff* bf);

node delete2(node root, buff* bf);

avlHead* deleteComp(avlHead *head, mother *M);

void avlSortAlfa(void (*f)(node),node c1);

void avlSortOrderDeep(void (*f)(node),node c1);

void avlPostOrder(void (*f)(node),node c1);

void freeHead(avlHead *head);


/*Mother*/

mother* initMother();

buff* getMotherBuff(mother* M);

hash* getMotherHash(mother* M);

avlHead* getMotherHead(mother* M);

unsigned short getMBuffStart(mother* M);

unsigned short getMBuffEnd(mother* M);

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


#endif
