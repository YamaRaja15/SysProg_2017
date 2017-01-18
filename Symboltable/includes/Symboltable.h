/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_INCLUDES_SYMBOLTABLE_H_
#define SYMBOLTABLE_INCLUDES_SYMBOLTABLE_H_
#include "../includes/List.h"
#include <stdlib.h>

class Symboltable {
public:
	Symboltable();
	virtual ~Symboltable();
	void SymbolTable::initSymbols();	// für Keywords
	char* insert(char* lexem);
	char* lookup(char* key);

private:
	List** table;
	int tablelength;
	char* createKey(char* lexem);
	int hashing(char* key);

};


#endif /* SYMBOLTABLE_H_ */
