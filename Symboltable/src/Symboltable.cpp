/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Symboltable.h"
#include <stdio.h>

Symboltable::Symboltable() {
	this->tablelength = 1024;
	this->table = new List*[tablelength];
	for( int i = 0; i < tablelength; i++) {
		table[i] = new List();
	}
	initSymbols();	// fill with keywords.
}

Symboltable::~Symboltable() {
	delete(table);
}

/**
 * Methode fügt ein Lexem in die Symboltabelle hinzu, falls das Lexem nicht
 * schon bereits vorhanden ist.
 */
char* Symboltable::insert(char* lexem){
	if(lexem == NULL){
		return NULL;
	}
	char* key = createKey(lexem);
	int i = hashing(key);

	if(! table[i]->contains(lexem)){
		printf("true ");
		table[i]->addNode(new Element (lexem, key));
	}
	return key;
}

/**
 * Methode gibt das passende Lexem zu einem gegebem Key zurück. Falls das
 * Lexem nicht vorhanden ist, wird NULL zurückgegeben.
 */
char* Symboltable::lookup(char* key){
	if(key == NULL){
		return NULL;
	}
	int i = hashing(key);
	return table[i]->getLexem(key);

}

/**
 * Methode erzeugt Einträge der bekannten Schlüsselworte der Grammatik, die immer
 * benötigt werden, und daher bei Initialisierung des Konstruktors aufgerufen wird.
 */
void SymbolTable::initSymbols() {
	// special identifiers
	insert("while"); insert("WHILE");
	insert("if"); insert("IF");
	
/**
 * Methode erstellt einen Key, welcher sich aus dem Lexem und dem Wort "Key"
 * zusammensetzt.
 */
char* Symboltable::createKey(char* lexem){
	//Zählt Länge des Lexems bis Nullterminator
	int length = 0;
	while(lexem[length] != '\0'){
		length++;
	}
	char* key = new char[length + 4];
	for(int i = 0; i < length; i++){
		key[i]=lexem[i];
	}
	key[length] = 'k';
	key[length + 1] = 'e';
	key[length + 2] = 'y';
	key[length + 3] = '\0';

	return key;

}

/**
 * Methode erstellt aus Key einen Zahlenwert von 0 bis Länge der Symboltabelle
 */
int Symboltable::hashing(char* key){
	unsigned int h = 0;
	while (*key) {
		h = h << 1 ^ *key++;
	}
	return h % tablelength;
}
