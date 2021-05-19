#include <string.h>
#include <stdlib.h>
#include <stdio.h>

short inZeros(short ind, short* zeros,short size){
	short i;
	for (i=0;i<size;i++){
		if ((ind)==(*(zeros+i))){
			ind++;
			return 1+inZeros(ind,zeros,size);
		}
	}
	return 0;
	/*Até posso usar pointer, para apenas mudar o valor*/
}


/* Funcao auxiliar do binarySearch que devolve o proximo
 *indice a verificar e atualiza o valor da
 *variavel size (atraves do uso de pointer)*/
short getBinInd(short *size, short ind,
                short up, short maxInd){
        short soma;
        soma = *size/2;
        *size = *size%2 ? (*size/2)+1 : *size/2;
        if (up){
                ind += soma;
        } else {
                ind = ind>soma ? ind-soma : soma-ind;
        }
        return ind<maxInd ? ind : ind-1;
}


/* Devolve o valor que resulta de comparar o nome do componente em analise 
 *com o que se quer comparar*/
short getBinRes(short val, short ind, short* vetor,short acc){
        short out;
	printf("Comparador indice: %d\n",ind+acc);
	printf("The comparasor:%d\n",*(vetor+ind+acc));
        out = val - *(vetor+ind+acc);
        return out;
}



/* Funcao de procura e insercao binaria responsavel por devolver
 *o indice pretendido (que seja para encontrar ou inserir)*/
short binarySearch(short val, short* vetor, short vSize, short* zeros, short zsize){
        short up=1;
        short res=0,found=0;
        short size = vSize;
        short ind=0;
	short acc=0;
        short maxInd = vSize;
        if (size){
                size += size%2 ? 0 : 1;
                do {
                        ind = getBinInd(&size, ind, up, maxInd);
			printf("ind pre zeros->%d\n",ind);
			acc = inZeros(ind,zeros,zsize);
                        res = getBinRes(val, ind, vetor,acc);
                        if (!res){
                                found=1;
                        }
                        up = res>0 ? 1 : 0;
			printf("ind in bin->%d\n",ind);
                } while (size!=1 && !(found));
        }
	printf("Was it found?->%d\n",found);
        if (ind<maxInd && !found){
                ind = res>0 ? ind+1 : ind;
        }
        return ind;
}





int main(){
	short vetor[31] = {1,2,3,4,0,0,6,7,8,9,0,11,12,13,0,15,16,17,19,0,0,0,0,0,0,0,0,0,0,0,0};
	/*short vetor[31] = {0,0,0,0,0,0,0,0,0,1,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}*/
	short size = 31;
	short zeros[16] = {4,5,10,14,19,20,21,22,23,24,25,26,27,28,29,30};
	short zsize = 16;
	/*short vetor[21] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
	short size = 21;
	short zeros[] = {0};
	short zsize = 0;*/
	short ind;
	short valor = 18;
	ind = binarySearch(valor,vetor,size,zeros,zsize);
	printf("ind->%d\n",ind);

	return 0;
}
