#include <string.h>
#include <stdlib.h>
#include <stdio.h>



int main(){
	int *io;
	io = (int*) malloc(sizeof(int));
	*io=0;
	io++;

	printf("%d\n",(*io));
	
	return 0;
}
