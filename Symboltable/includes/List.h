/*
 * List.h
 *
 *  Created on: 26.10.2016
 *      Author: thao
 */

#ifndef SYMBOLTABLE_INCLUDES_LIST_H_
#define SYMBOLTABLE_INCLUDES_LIST_H_
#include "../includes/Node.h"
#include <stdlib.h>

class List {
public:
	List();
	virtual ~List();
	void addNode(Element* element);
	bool contains(char* lexem);
	char* getLexem(char* key);

private:
	Node* firstNode;
	Node* lastNode;

};

#endif /* SYMBOLTABLE_SRC_LIST_H_ */
