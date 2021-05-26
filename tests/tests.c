#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define A 31415
#define B 27183

int main(){
	long i=0,i2=1;
	unsigned long a = 999;
	while (a!=0){
		printf("set ");
		for (i=0;i<i2;i++){
			printf("%ld",'N'+(a%30));
		}
		printf(" ola\n");
	if (!a%30){
		i2++;	
	}
	}
	
	return 0;
	
}
