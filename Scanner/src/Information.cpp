#include "../includes/Information.h"

Information::Information(char* lexem) {
	this->lexem = lexem;

}

Information::~Information() {
	// nothing to do as the string is stored in the
	// symboltable
}

/**
 * returns a pointer to the lexem in the string table
 * @return pointer to the lexem in the string table
 */
const char* Information::getLexem() const {
	return lexem;
}

/**
 * compares another lexem with this lexem.
 * @param  other_lexem pointer to the other lexem. string should be terminated with \0
 * @return             true if the lexems match, else false
 */
bool Information::matchesLexem(const char* other_lexem) {
	int i = 0;
	while((lexem[i] != '\0') || (other_lexem[i] != '\0')) {
		if(lexem[i] != other_lexem[i])
			return false;
		i++;
	}
	return true;
}
