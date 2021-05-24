/*
 * Ficheiro: buffer.c
 * Autor: Joao Fonseca
 * Descricao: Definicao das funcoes que manipulam a estrutura
 * de dados buffer, que sera necessaria para receber o stdin
*/

#include "proj2.h"


/* ============================================================================
 * Buffer (buff)
 *
 *  - char* bigBuff  |
 *  - char* bigBuff2 |- guardam istrucoes,valores, nomes, ...
 *  - unsigned short start (indice onde se comeca a analisar bigBuff)
 *  - unsigned short end (indice onde se para de analisar bigBuff)
 *  - unsigned long (guardar occ de uma componente, quando necessario)
 * ==========================================================================*/



/* Inicializa uma estrutura buffer, alocando-lhe memoria*/
buff* initBuffer(){
	/* Buffer e logo dos primeiros a ser inicializados
	 * Nunca havera "No Memory" neste processo*/
	buff* bf;
	bf = (buff*) malloc(sizeof(buff));
	bf->bigBuff = (char*) malloc(sizeof(char)*BUFF_SIZE);
	bf->bigBuff2 = (char*) malloc(sizeof(char)*BUFF_SIZE);
	bf->start = 0;
	bf->end = 0;
	bf->occ = 0;
	return bf;
}


/* O ponteiro do buffer para nodes passa a apontar para "c1"*/
void nodeToBuff(node c1, buff* bf){
	bf->c = c1;
}

/* Devolve o ponteiro de componente guardado no buffer*/
node getBuffNode(buff* bf){
	return bf->c;
}

/*Devolve Buffer*/
char* getBuff(buff* bf){
        return bf->bigBuff;
}


/*Devolve Buffer2*/
char* getBuff2(buff* bf){
	return bf->bigBuff2;
}

/*Devolve o start*/
unsigned short getBuffStart(buff* bf){
	return bf->start;
}

/*Devolve o end*/
unsigned short getBuffEnd(buff* bf){
        return bf->end;
}


/*Copia o que esta no bifBuff2 para o bigBuff*/
void cpyBuffs(buff* bf){
	strcpy(bf->bigBuff,bf->bigBuff2);
}

/* Guarda no buffer o comando recebido pelo input*/
void commandToBuff(buff *bf){
	scanf(S,bf->bigBuff);
	
}

/* Guarda no buffer o caminho recebido pelo input
 * modoB indica se e para verificar se ha path ou nao*/
void pathToBuff(buff *bf, short modoB){
	char c;
	unsigned short i=0;
	bf->start = 0;
	bf->end = 0;	
	if (modoB){ /*verificar se o stdin nao esta "vazio"*/
		c = cleanWhite();
		if (c!='\n'){
			while (c=='/'){
				c = getchar();
			} 
			while (c!='\n'){
				*(bf->bigBuff +i) = c;
				i++;
				c=getchar();	
			}
			*(bf->bigBuff +i)='\0';
		} else {
			resetBuff(bf);
		}
			
	} else {
		scanf(S,bf->bigBuff);
	}
}

/* Guarda no buffer o valor recebido pelo input*/
void valToBuff(buff *bf){
	inputGetNameW(bf->bigBuff2);
}

/* Coloca bigBuff a Null String*/
void resetBuff(buff *bf){
	*(bf->bigBuff) = ZERO;
	*(bf->bigBuff2) = ZERO;
}

/* Verifica se bigBuff e Null ou nao*/
short nullBuff(buff* bf){
	return *(bf->bigBuff)==ZERO;
}


/* Devolve o tamanho da parte do bigBuff a analisar
 *Inclui espaco para '\0'*/
unsigned int getVsize(buff* bf){
	return (bf->end)-(bf->start)+ONE;
}


/* Coloca o start a 0 e o end na posicao do primeiro '\0' do bigBuff (0)
 * ou bigBuff2 (1) dependendo do modo*/
void setSizeBuffStart(buff* bf,char modo){
	bf->start = 0;
	if (!modo){
		bf->end = strlen(bf->bigBuff);
	} else {
		bf->end = strlen(bf->bigBuff2);
	}
}





/* insere um order na occ do buffer*/
void orderToBuff(unsigned long occ, buff* bf){
	bf->occ = occ;
}

/* Devolve a order do buffer*/
unsigned long buffOrder(buff* bf){
	return bf->occ;
}

/* Faz free ao buffer*/
void freeBuffer(buff *bf){
	free(bf->bigBuff);
	free(bf->bigBuff2);
	free(bf);
}


/* Retira a ultima componente de bigBuff e
 * coloca-la no bigBuff2 (importante para o "delete")*/
void buffSwitchComp(buff* bf){
        unsigned short i=0;
        unsigned short a=0;
	
        for (;bf->bigBuff[i]!='\0';i++){
                if (bf->bigBuff[i]=='/' && notEndPath(bf->bigBuff[i+1])){
                        a=i;
                }
        }
        if (a==ZERO && bf->bigBuff[a] != '/'){
                strcpy(bf->bigBuff2,bf->bigBuff);
                bf->bigBuff[a] = '\0';
        } else {
                bf->bigBuff[a++] = '\0';
                strcpy(bf->bigBuff2,&(bf->bigBuff[a]));
        }
	i = i-a;
        while (bf->bigBuff2[--i]=='/'){
                /*so quero o nome do componente (sem '/')*/
                bf->bigBuff2[i]='\0';
		i--;
        }
}







