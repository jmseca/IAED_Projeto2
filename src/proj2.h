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
#define MAX_COMAND_SIZE 7

/*Tamanho para o buffer que ira receber o caminho/valor (inclui '\0')*/
#define BUFF_SIZE

/*Comandos*/
#define HELP "help"
#define QUIT "quit"
#define SET "set"
#define PRINT "print"
#define FIND "find"
#define LIST "list"
#define SEARCH "search"
#define DELETE "delete"





/*Buffer*/

typedef struct {
	char* command;
	char* bigBuff;
} buff ;

/*Componentes*/

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


unsigned short hashFun(char* str);


/*Funcoes dos Comandos*/

void handleHelp();

