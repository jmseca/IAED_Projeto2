#include "proj2.h"


int main(){
	char control=ZERO;
	mother* M;

	M = initMother();
		
	do {
		commandToBuff(M->bf);
		checkCommand(M,&control);
	} while (!control);

	return 0;

}
