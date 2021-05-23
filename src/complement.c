/*
 * Ficheiro: complement.c
 * Autor: Joao Fonseca
 * Descricao: Definicao de funcoes auxiliares bastante uteis para 
 * o bom funcionamento do programa 
*/

#include "proj2.h"

/* Termina o programa, libertanto toda a memoria
 *Chamada quando nao ha mais memoria disponivel*/
void endProgram(mother* M){
	freeMother(M);	
	printf("No Memory\n");
	exit(0);
}

/* Funcao que corre o malloc e verifica se ainda ha memoria disponivel
 *Se nao houver, "control" guarda essa informacao*/
void* myMalloc(short typeSize, unsigned int vSize, char* control){
	/*Add condicao se for preciso para unsigned
	 * e no fim apagar os que nao sao necessarios*/
	void *p;
	switch (typeSize){
		case ONE: /*char*/
			p = (char*) malloc(ONE*vSize);
			break;
		case SHORT:
			p = (short*) malloc(SHORT*vSize);
			break;
		case INT:
			p = (int*) malloc(INT*vSize);
			break;
		case LONG:
			p = (long*) malloc(LONG*vSize);
			break;
		case AVLHEAD:
			p = (avlHead*) malloc(AVLHEAD*vSize);
			break;
		case COMP:
			p = (comp*) malloc(COMP*vSize);
			break;
		default:
			printf("Oops, myMalloc nao tem todos os tipos\n");
	}
	if (p==NULL){
		*control = ONE;
	}
	return p;
}


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


char notEndPath(char c){
	return !(c==' '|| c=='/' || c=='\n');
}

/* Passa o que esta escrito no input para out, ate encontrar '\n' 
 * Eliminando os espacos desnecessarios*/
short inputGetNameW(char *out){
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
                *(out + n++) = c;
                c = getchar();
        }
        n = control ? wInd : n; /*desta maneira eliminamos os espacos finais*/
        *(out+n) = '\0';
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


/*Copia a string que esta identificada no buffer para "dest"*/
void myStrCpy(char* dest, buff* bf){
	unsigned short i=0;
	char* src = bf->bigBuff;
	unsigned short start =bf->start;
	unsigned short end = bf->end;
	for(;start<end;start++){
		*(dest+i) = *(src+start);
		i++;
	} *(dest+i)='\0';
}

/* Compara a string que esta identificada no buffer com "s1"*/
short myStrCmp(char* s1, buff* bf){
	unsigned short i=0;
	char* s2 = bf->bigBuff;
        unsigned short start =bf->start;
        unsigned short end = bf->end;
	short out=0;
	while (start<end && !out){
		out = *(s2+start) - *(s1+i);
		i++;
		start++;
	}
	return out;
}


/*APAGAR SE FOR O CASO*/
void myPrint(char* s1, unsigned short start, unsigned short end){
	for(;start<end;start++){
		printf("%c",*(s1+start));
	}printf("\n");
}
