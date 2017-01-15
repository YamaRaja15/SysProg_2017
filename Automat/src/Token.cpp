/*
 * Token.cpp
 *
 *  Created on: 08.11.2016
 *      Author: johanna
 */
#include <stdlib.h>
#include <errno.h>

#include "../includes/Token.h"

Token::Token(Token::Type type, int column, int line, Information* information,
		long int value) {
	this->type = type;
	this->column = column;
	this->line = line;
	this->information = information;
	this->value = value;
}

Token::~Token() {
	// do not delete information object here, references to Information might cause problems
}


Information* Token::getInformation() const {
	return information;
}

Token::Type Token::getType() const {
	return type;
}

int Token::getColumn() const {
	return column;
}

int Token::getLine() const {
	return line;
}

long int Token::getValue() const {
	return value;
}

