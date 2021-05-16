#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct oi {
	int q;
	int *oa;
}Oi;


int main(){
	Oi* ola;
	Oi* ola2;
	ola = (Oi*) malloc(sizeof(Oi));
	ola->oa = (int*) malloc(sizeof(int)*20);
	ola2 = (Oi*) malloc(sizeof(Oi));
	ola2->oa = (int*) realloc(ola->oa,sizeof(int)*40);
	/*free(ola->oa);*/
	free(ola);
	free(ola2->oa);
	free(ola2);
	return 0;
}
