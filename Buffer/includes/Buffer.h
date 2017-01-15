/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include <stdio.h>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>

#ifndef BUFFER_H_
#define BUFFER_H_
using namespace std;

class Buffer {
public:
	Buffer(const char* filename);
	~Buffer();
	char getChar();
	void ungetChar();

	int getColumn() const;

	int getLine() const;

private:
	char* buffer1;
	char* buffer2;
	char* next;
	int handle;
	bool newRead; //Noch nicht im nächsten Buffer-Array drin gewesen. Soll erneutes einlesen durch ungetChar() an der Grenze des Buffers vermeiden.
	int line;
	int column;
	int rememberColumn;
	int end;

};

#endif /* BUFFER_H_ */
