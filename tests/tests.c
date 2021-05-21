#include <string.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int f(char* str){
	unsigned int size =  strlen(str);
	return size;
}

int main(){
	char ola[20] = "Boa tarde pessoas";
	unsigned int siz;
	siz = f(ola);
	printf("%d\n",siz);
	return 0;
}
