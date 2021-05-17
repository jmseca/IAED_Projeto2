#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ola "ola"

int main(){
	char ol[4] = "ola";
	int d;
	d = strcmp(ol,ola);

	printf("%d\n",d);
	return 0;
}
