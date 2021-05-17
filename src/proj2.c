#include "proj2.h"







int main(){
	/*Inicializar as vars globais*/
	short control;
	comp* Root;
	buff* Buffer;
	Root = initRoot();
	Buffer = initBuffer();
	
	do {
		commandToBuff(Buffer);
		control = checkCommand(Buffer, Root);
	} while (!control);

	return 0;

}
