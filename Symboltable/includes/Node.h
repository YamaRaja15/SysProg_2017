/*
 * Node.h
 *
 *  Created on: 26.10.2016
 *      Author: thao
 */

#ifndef SYMBOLTABLE_INCLUDES_NODE_H_
#define SYMBOLTABLE_INCLUDES_NODE_H_
#include "../includes/Element.h"

class Node {
public:
	Node(Element* element);
	virtual ~Node();
	void setSuccessor(Node* successor);
	Node* getSuccessor();
	bool contains(char*lexem);
	char* getLexem(char* key);
	Element* getElement();

private:
	Element* element;
	Node* successor;
	bool compareArray(char* array1, char* array2);
};

#endif /* SYMBOLTABLE_SRC_NODE_H_ */
