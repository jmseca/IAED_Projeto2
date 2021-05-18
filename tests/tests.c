#include <string.h>
#include <stdlib.h>
#include <stdio.h>



void f(){
	static short oi;
	oi++;
	printf("%d\n",oi);
}

int main(){
	f();
	f();
	f();

	return 0;
}
