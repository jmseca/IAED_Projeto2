#include "proj2.h"


int main(){
	char control=ZERO;
	unsigned int number=0;
	mother* M;
	M = initMother();
	do {
		commandToBuff(M->bf);
		checkCommand(M,&control,&number);
	} while (!control);

	return 0;

}
