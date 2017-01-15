/*
 * Element.cpp
 *
 *  Created on: 26.10.2016
 *      Author: thao
 */

#include "../includes/Element.h"

Element::Element(char* identifier, char*key) {
	this->identifier = identifier;
	this->key = key;

}

Element::~Element() {
	delete (identifier);
	delete (key);
}

char* Element::getIdentifier() {
	return this->identifier;
}

char* Element::getKey() {
	return this->key;
}

