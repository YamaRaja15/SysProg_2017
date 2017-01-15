/*
 * Node.cpp
 *
 *  Created on: 26.10.2016
 *      Author: thao
 */

#include "../includes/Node.h"
#include <stdlib.h>

Node::Node(Element* element) {
	this->element = element;
	this->successor = NULL;
}

Node::~Node() {
	delete (element);
	delete (successor);
}

void Node::setSuccessor(Node* successor) {
	this->successor = successor;
}

Node* Node::getSuccessor() {
	return this->successor;
}

Element* Node::getElement() {
	return this->element;
}

/**
 * Methode prüft, ob zwei char arrays gleich sind.
 */
bool Node::compareArray(char* array1, char* array2) {
	int i = 0;
	while (array1[i] != '\0' && array2[i] != '\0') {
		if (array1[i] != array2[i]) {
			return false;
		}
		i++;
	}
	if (array1[i] != '\0' || array2[i] != '\0') {
		return false;
	}
	return true;
}

/**
 * Methode prüft, ob ein Lexem in dem Knoten oder in dem seiner Nachfolger
 * vorhanden ist.
 */
bool Node::contains(char* lexem) {
	if (compareArray(this->element->getIdentifier(), lexem)) {
		return true;
	} else if (this->successor != NULL) {
		return this->successor->contains(lexem);
	}
	return false;
}

/**
 * Methode gibt passendes Lexem zum übergebenem Key zurück. Existiert der
 * Eintrag nicht, wird NULL zurückgegeben.
 */
char* Node::getLexem(char* key) {
	if (compareArray(this->element->getKey(), key)) {
		return this->element->getIdentifier();
	} else if (this->successor != NULL) {
		return this->successor->getElement()->getIdentifier();
	}
	return NULL;
}
