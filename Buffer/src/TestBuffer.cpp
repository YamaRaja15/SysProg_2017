#include "../includes/Buffer.h"

int main(int argc, char *argv[]) {

	Buffer* buffer;

	buffer = new Buffer(argv[1]);
	int l, c;

	for (int i = 0; i < 1030; i++) {
		l = buffer->getLine();
		c= buffer->getColumn();
	printf("%d %c Line: %d Column: %d \n", i, buffer->getChar(),
			l,c);

}
printf("ZURÜCKLEGEN \n");
for (int i = 0; i < 10; i++) {

	buffer->ungetChar();
	printf("Line: %d Column: %d \n", buffer->getLine(), buffer->getColumn());

}
printf("ERNEUT LESEN \n");
for (int i = 0; i < 10; i++) {

	printf("%c Line: %d Column: %d \n", buffer->getChar(), buffer->getLine(),
			buffer->getColumn());

}

}

