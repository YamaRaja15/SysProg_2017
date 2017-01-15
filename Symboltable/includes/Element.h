/*
 * Element.h
 *
 *  Created on: 26.10.2016
 *      Author: thao
 */

#ifndef SYMBOLTABLE_INCLUDES_ELEMENT_H_
#define SYMBOLTABLE_INCLUDES_ELEMENT_H_

class Element {
public:
	Element(char* identifier, char*key);
	virtual ~Element();
	char* getIdentifier();
	char* getKey();

private:
	char* identifier;
	char* key;
};


#endif /* SYMBOLTABLE_SRC_ELEMENT_H_ */
