#include <iostream>
#include "../includes/Automat.h"
#include <string>
#include <cstdlib>
#include <cstring>


// Ausgabemethode
void giveParameter(Automat& automat) {
	std::cout << "Type: ";
	std::cout << Token::token_type_as_string(automat.getType()) << std::endl;

	std::cout << "Back: ";
	std::cout << automat.getBack() << std::endl;
	std::cout << "Column: ";
	std::cout << automat.getColumn() << std::endl;

	std::cout << "Line: ";
	std::cout << automat.getLine() << std::endl;
	std::cout << "RESET";

	std::cout << std::endl;
	automat.reset(automat.getBack());

	std::cout << "Column: ";
	std::cout << automat.getColumn() << std::endl;

	std::cout << "Line: ";
	std::cout << automat.getLine() << std::endl;

	std::cout << std::endl;
}

/*
 * ##################
 * Testmethoden
 * ##################
 */

void IdentifierTest() {
	Automat automat;

	automat.accept('S');
	automat.accept('y');
	automat.accept('s');
	automat.accept('P');
	automat.accept('r');
	automat.accept('o');
	automat.accept('g');


	// break
	automat.accept('.');

	giveParameter(automat);
}

void IntegerTest() {
	Automat automat;

	automat.accept('4');
	automat.accept('2');
	automat.accept('4');
	automat.accept('2');
	automat.accept('4');
	automat.accept('2');


	// abbrechen
	automat.accept('y');

	giveParameter(automat);
}

void CommentTest() {
	Automat automat;

	automat.accept(':');
	automat.accept('*');
	automat.accept('K');
	automat.accept('o');
	automat.accept('m');
	automat.accept('m');
	automat.accept('e');
	automat.accept('*');
	automat.accept('n');
	automat.accept('t');
	automat.accept(':');
	automat.accept('a');
	automat.accept('r');
	automat.accept('*');
	automat.accept(':');
	giveParameter(automat);

	// break
	automat.accept('p');

	giveParameter(automat);
}

void SpacesTest() {
	Automat automat;

	automat.accept(' ');
	automat.accept(' ');
	automat.accept(' ');
	automat.accept(' ');


	// abbrechen
	automat.accept('3');

	giveParameter(automat);
}

void NewLineTest() {
	Automat automat;

	automat.accept('\n');
	automat.accept('\n');
	automat.accept('\n');
	automat.accept('\n');
	automat.accept('\n');
	automat.accept('\n');

	// abbrechen
	automat.accept(' ');

	giveParameter(automat);
}

void EqualAssignTest() {
	Automat automat;

	automat.accept('=');
	automat.accept(':');
	automat.accept('=');
	giveParameter(automat);

	// abbrechen
	automat.accept('b');

	giveParameter(automat);
}

void SignTest() {
	Automat automat;

	automat.accept(':');

	automat.accept(';');

	automat.accept('.');

	automat.accept('<');
	giveParameter(automat);

	// abbrechen
	automat.accept('3');

	giveParameter(automat);
}



int main(int argc, char* argv[]) {


	//IdentifierTest();
	//
	//IntegerTest();
	//
	//CommentTest();
	//
	//SpacesTest();
	//
	//NewLineTest();
	//
	//EqualAssignTest();
	//
	SignTest();
}

