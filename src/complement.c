/*
 * Ficheiro: complement.c
 * Autor: Joao Fonseca
 * Descricao: Definicao de funcoes auxiliares bastante uteis para 
 * o bom funcionamento do programa 
*/

#include "proj2.h"

/*Devolve o proximo char do stdin que nao seja ' ' ou '\t'*/
char cleanWhite(){
	char c=getchar();
	while((c==' ') || (c=='\t')){
		c=getchar();
	}
	return c;
}

/* Verifica se 'c' nao e ' ', '\t' ou '\n'*/
short notWhite(char c){
	return !(c==' ' || c=='\t' || c=='\n');
}

/* Passa o que esta escrito no input para out, ate encontrar '\n' 
 * Eliminando os espacos desnecessarios*/
short inputGetNameW(char out[]){
        short control=0,n=0;
        short wInd; /*Controla o indice do primeiro espaco*/
        char c=getchar();
        while ((c==' ' || c=='\t')){ /*Passar espacos brancos a frente*/
                c = getchar();
        }
        while (c!='\n'){
                if (c==' ' || c=='\t'){
                        if (!control){  /*1o espaco encontrado*/
                                wInd = n;
                                control=1;
                        }
                } else {
                        control = 0;
                }
                out[n++] = c;
                c = getchar();
        }
        n = control ? wInd : n; /*desta maneira eliminamos os espacos finais*/
        out[n] = '\0';
        return 0;
}


/* Funcao responsavel por ignorar os '/' num caminho*/
void pathClean(char* path, unsigned short *ind){
	while (*(path+(*ind))=='/'){
		(*ind)++;
	}
}

/* Funcao que encontra o proximo '/' num caminho*/
unsigned short findSepar(char* path, unsigned short ind){
	char c =  *(path+ind);
	while (c!='/' && c!='\0'){
		c = *(path+(++ind));
        }
	return ind;
}


/*Copia a string "src" do indice "start" ate "end" (exclusive) para "dest"*/
void myStrCpy(char* dest, char* src, unsigned short start, unsigned short end){
	unsigned short i=0;
	for(;start<end;start++){
		*(dest+i) = *(src+start);
		i++;
	}
}

/*Compara a string "s1" do indice "start" ate "end" (exclusive) com "s2"*/
short myStrCmp(char* s1, char* s2, unsigned short start, unsigned short end){
	unsigned short i=0;
	short out=0;
	printf("----------------");
	printf("%s---%s",s1,s2);
	while (start<end && !out){
		printf("%c---%c\n",*(s1+start),*(s2+i));
		out = *(s1+start) - *(s2+i);
		i++;
		start++;
	}
	return out;
}

