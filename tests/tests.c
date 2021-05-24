#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int* f(int* a){
	if (a==NULL){
		return NULL;
	}
	*a = 3;
	return a;
}


int main(){
	int *v = (int*) malloc(sizeof(int));
	int *s = (int*) malloc(sizeof(int)); 
	v=NULL;
	s = NULL;

	s = f(v);
	v = f(s);

	
	return 0;
	
}
