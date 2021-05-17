/*
 * Ficheiro: buffer.c
 * Autor: Joao Fonseca
 * Descricao: Definicao das funcoes que manipulam a estrutura
 * de dados buffer, que sera necessaria para receber o stdin
*/


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
char* valToBuff(buff *bf){
	inputGetNameW(bf->bigBuff);
}
