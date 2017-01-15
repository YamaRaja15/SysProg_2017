#include "../includes/Symboltable.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char **argv) {

	Symboltable* symboltable = new Symboltable();
	char* hallokey = symboltable->insert((char*)"Hallo");
	printf("%s \n", hallokey);
	printf("%s \n", symboltable->lookup(hallokey));
	printf("%s \n", symboltable->lookup((char*)"Hallokey"));
	printf("%s \n \n", symboltable->lookup((char*)"Halloke"));

	printf("%s \n", symboltable->insert((char*)"Welt1"));
	printf("%s \n \n", symboltable->lookup((char*)"Welt1key"));


	char* wieKey = symboltable->insert((char*)"Wie");
	printf("%s \n", symboltable->lookup(wieKey));
	printf("%s \n", symboltable->lookup((char*)"Wiekey"));
	printf("%s \n \n", symboltable->lookup((char*)"WieKeey"));

	if (symboltable->lookup((char*)"WeltKey") == 0)
			printf("true \n");
		if (symboltable->lookup((char*)"1") == 0)
			printf("true \n\n");

	printf("%s \n \n", symboltable->insert((char*)"Hallo")); //existiert bereits
	printf("%s \n \n", symboltable->lookup((char*)"LexemExistiertnicht."));
	printf("LookupForNull: %s \n \n", symboltable->lookup(NULL));
	printf("InsertNull: %s \n \n", symboltable->insert(NULL));

	return EXIT_SUCCESS;
}

