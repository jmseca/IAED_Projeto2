#include <string.h>
#include <stdlib.h>
#include <stdio.h>



int main(){
	char a[20] = "Bom dia";
	short n=0;

	printf("%c\n",*(a + n++));
	printf("%c\n",*(a+n));
	
	return 0;
}
