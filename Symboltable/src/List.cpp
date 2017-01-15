/*
 * List.cpp
 *
 *  Created on: 26.10.2016
 *      Author: thao
 */

#include "../includes/List.h"

List::List() {
	this->firstNode = NULL;
	this->lastNode = NULL;
}

List::~List() {
	delete (firstNode);
	delete (lastNode);
}

/**
 * Methode erstellt einen Knoten und fügt dieser zur Liste hinzu.
 */
void List::addNode(Element* element) {
	//Wenn die Liste leer ist, wird Knoten als Anfang und Endeknoten hinzugefügt
	if (firstNode == NULL) {
		firstNode = new Node(element);
		lastNode = firstNode;
	}

	//Wenn die Liste bereits Knoten enthält, wird neuer Knoten am Ende gesetzt
	else {
		lastNode->setSuccessor(new Node(element));
		lastNode = lastNode->getSuccessor();
	}
}

/**
 * Methode prüft, ob Liste ein Lexem enthält
 */
bool List::contains(char* lexem) {
	if (firstNode != NULL) {
		return firstNode->contains(lexem);
	}

	return false;
}

/**
 * Methode holt das Lexem zum passenden Schlüssel. Ist die Liste leer, wird
 * NULL zurückgegeben.
 */
char* List::getLexem(char* key) {
	if (firstNode != NULL) {
		return firstNode->getLexem(key);
	}

	return NULL;
}

