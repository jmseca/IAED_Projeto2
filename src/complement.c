/*
 * Ficheiro: complement.c
 * Autor: Joao Fonseca
 * Descricao: Definicao de funcoes auxiliares bastante uteis para 
 * o bom funcionamento do programa 
*/

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
	return (c==' ' || c=='\t' || c=='\n');
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

/* Coloca em out o primeiro nome que aparecer no input,
 *dependendo do espaco do vetor out 
 *size -> tamanho do vetor out -1 (exclui '\0')
 *Devolve: 1(acacou no final de linha), 0(caso contrario)*/
short inputGetSingleName(char out[], short size){
        short n=0;
        char c = getchar();
        while ((c==' ' || c=='\t')){ /*Passar espacos brancos a frente*/
                c = getchar();
        }
        while (!(c==' ' || c=='\t' || c=='\n') && n<size){
                out[n++] = c;
                c = getchar();
        }
        out[n] = '\0';
        return c=='\n';
}

