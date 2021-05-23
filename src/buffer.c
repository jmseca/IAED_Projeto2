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
 *  - char* command (guarda o comando a executar)
 *  - char* bigBuff (guarda a instrucao para alem do comando)
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
	bf->command = (char*) malloc(sizeof(char)*MAX_COMMAND_SIZE);
	bf->bigBuff = (char*) malloc(sizeof(char)*BUFF_SIZE);
	bf->bigBuff2 = (char*) malloc(sizeof(char)*BUFF_SIZE);
	bf->start = 0;
	bf->end = 0;
	bf->occ = 0;
	return bf;
}


/* Guarda no buffer o comando recebido pelo input*/
void commandToBuff(buff *bf){
	printf("PREV Command->%s\n",bf->command);
	scanf("%s",bf->command);
	
}

/* Guarda no buffer o caminho recebido pelo input
 * modoB indica se e para verificar se ha path ou nao*/
void pathToBuff(buff *bf, short modoB){
	char c;
	bf->start = 0;
	bf->end = 0;	
	if (modoB){ /*verificar se o stdin nao esta "vazio"*/
		c = cleanWhite();
		if (c!='\n'){
			*(bf->bigBuff) = c;
			scanf("%s",&(bf->bigBuff[1]));
		} else {
			resetBuff(bf);
		}
			
	} else {
		scanf("%s",bf->bigBuff);
	}
}

/* Guarda no buffer o valor recebido pelo input*/
void valToBuff(buff *bf){
	inputGetNameW(bf->bigBuff2);
}

/* Coloca bigBuff a Null String*/
void resetBuff(buff *bf){
	*(bf->bigBuff) = '\0';
	*(bf->bigBuff2) = '\0';
}

/* Verifica se bigBuff e Null ou nao*/
short nullBuff(buff* bf){
	return *(bf->bigBuff)=='\0';
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


/* O ponteiro do buffer para componentes passa a apontar para "c1"*/
void compToBuff(comp* c1, buff* bf){
	bf->c = c1;
}

/* Devolve o ponteiro de componente guardado no buffer*/
comp* getBuffComp(buff* bf){
	return bf->c;
}


/* insere uma "occ" na occ do buffer*/
void occToBuff(unsigned long occ, buff* bf){
	bf->occ = occ;
}


/* Inicializar a variavel do buffer que servira como
 * condicao de paragem*/
void buffStart(buff* bf){
	occToBuff(ZERO,bf);
}

/* Colocar no buffer o valor que corresponde a condicao de paragem*/
void buffStop(buff* bf){
        occToBuff(ONE,bf);
}


/* Usado como condicao de paragem*/
char buffCheckStop(buff* bf){
	return bf->occ == ONE;
}

/* Devolve a occ do buffer*/
unsigned long getBuffOcc(buff* bf){
	return bf->occ;
}

/* Faz free ao buffer*/
void freeBuffer(buff *bf){
	free(bf->command);
	free(bf->bigBuff);
	free(bf->bigBuff2);
	free(bf);
}



/* Adiciona ao bigBuff o nome da componente no fim*/
void addToBuff(buff* bf, comp* c1){
	unsigned short i=0;
	unsigned short a=0;
	for (;bf->bigBuff[i]!='\0';i++){;}
	bf->bigBuff[i++] = '/';
	do {
		bf->bigBuff[i++] = c1->nome[a];
	} while (c1->nome[a++] != '\0');
}



/* Retira a ultima componente de BigBuff*/
void removeFromBuff(buff* bf){
	unsigned short i=0;
	unsigned short a=0;
	for (;bf->bigBuff[i]!='\0';i++){
		if (bf->bigBuff[i]=='/')  a=i;
	}
	bf->bigBuff[a] = '\0';
}



/* Retira a ultima componente de bigBuff1 e
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
	printf("B1->%s\nB2->%s\n",bf->bigBuff,bf->bigBuff2);
	i = i-a;
        while (bf->bigBuff2[--i]=='/'){
                /*so quero o nome do componente (sem '/')*/
                bf->bigBuff2[i]='\0';
        }
}
