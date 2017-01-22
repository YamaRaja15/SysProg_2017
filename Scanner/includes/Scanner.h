#ifndef SCANNER_H_
#define SCANNER_H_

#define SCANNER_BUFFER_SIZE 4096

#include "../../Buffer/includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include "../../Symboltable/includes/Symboltable.h"

class Scanner {
	public:
		Scanner(const char* filename);
		virtual ~Scanner();
		Token* nextToken();
	private:
		char scanner_buffer [SCANNER_BUFFER_SIZE];
		int char_count;
		Token* analyse(char c, int char_count );
		Buffer* buffer;
		Automat* automat;
		Symboltable* symboltable;
		bool compareArray(char* array1, char* array2);

		void prepareForNextLexem(int bad_char_count);
};

#endif /* SCANNER_H_ */
