/* * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Buffer.h"
#include <unistd.h>

Buffer::Buffer(const char* filename) {
	this->buffer1 = new char[1024];
	this->buffer2 = new char[1024];
	this->newRead = true;
	line = 1;
	column = 1;
	rememberColumn = 1;
	end=1;
	this->handle = open(filename, O_RDWR, S_IREAD);
	if (handle == -1) {
		printf("File konnte nicht geöffnet werden");
	} else {
		end = read(handle, buffer1, 1024);

	}
	this->next = buffer1;

}

Buffer::~Buffer() {
	close(handle);
	delete[] buffer1;
	delete[] buffer2;

}

char Buffer::getChar() {
	if(end !=0){

	if (*next == NULL ) {
		if (next == &buffer1[1024]) {/* am Ende der ersten Hälfte*/
			// lade die zweite Hälfte neu;
			if (newRead ) {
				read(handle, buffer2, 1024);

			}
			newRead = true;
			next = buffer2;		//Den Nullzeiger korrigieren

		} else if (next == &buffer2[1024]) { /* am Ende der zweite Hälfte*/
			// lade die erste Hälfte neu;
			if (newRead) {
				read(handle, buffer1, 1024);
			}
			newRead = true;
			next = buffer1;

		} else {

			return -1;
		}
	}
	column++;

	if (*next == '\n') {
		line++;
		rememberColumn = column;
		column = 1;
	}
	next++;

	return *(next - 1);

	}else{
		return -1;
	}

}

void Buffer::ungetChar() {
	if (column == 1) {
		line--;
		column = rememberColumn;
	}
	column--;

	if (next == &buffer1[0]) {
		next = &buffer2[1023]; //1024 zeigt auf NULL!
		newRead = false;

	} else if (next == &buffer2[0]) {
		next = &buffer1[1023];
		newRead = false;
	} else {
		next--;
	}

}
int Buffer::getColumn() const {
	return column;
}

int Buffer::getLine() const {
	return line;
}

