#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct ola {
	int a;
	int b;
	long c;
	char ola[10];
} Ola;


int main(){
	printf("%ld\n",sizeof(Ola));
	printf("%ld\n",sizeof(Ola*));
	return 0;
}
