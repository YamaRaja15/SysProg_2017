#include "../includes/Automat.h"

/**
 * Array with all sign characters available in the Grammar.
 */
static char SIGN_CHARACTERS[] = { '+', '-', ':', '*', '<', '>', '=', 
		'!', '&', ';', '(', ')', '{', '}', '[', ']' };

Automat::Automat() {
	currentState = START;
	lastFinalState = START;
	startColumn = 1;
	startLine = 1;
	currentLine = 1;
	currentColumn = 1;
	putBack = 0;
}

Automat::~Automat() {
	// nothing to do here
}


// #####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~####
// #####	Methods for checking states 	####
// #####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~####

bool Automat::isSpace(char c) {
	return c == ' ' || c == '\t';
}

bool Automat::isInteger(char c) {
	return c >= '0' && c <= '9';
}

bool Automat::isLetter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * An Identifier is any string made up of letters and numbers,
 * starting with a letter.
 */
bool Automat::isIdentifier(char c) { 
	return (isLetter(char c)
			|| isInteger(c) && currentState == IDENTIFIER));
}

bool Automat::isSign(char c) {
//	char signs[] = { '+', '-', ':', '*', '<', '>', '=', '!', '&', ';', '(', ')',
//			'{', '}', '[', ']' };
	for (int i = 0; i < std::sizeof(SIGN_CHARACTERS); i++) {
		if (SIGN_CHARACTERS[i] == c)
			return true;
	}
	return false;
}

bool Automat::isNewline(char c) {
	return c == '\n' || c == '\r';
}

/**
// #####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~####
// #####	Method for iterating through	#### 
// #####	the characters of the buffer 	####
// #####~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~####
 * Purpose:	insert next char into the machine
 * Hints:
 * 	- If "false"; you can retrieve lastfinalstate via getters.
 	  In that case, call reset() before inserting new chars.
 * @param  c char to insert
 * @return   false, if it is not possible to reach a valid state with further insertions
 */
bool Automat::accept(char c) {
	currentColumn++;
	switch (currentState) {

	//##(0.)##	Start -- For initial method call
	case START: {
		if (isIdentifier(c)) {
			currentState = IDENTIFIER;
			setLastFinalState(IDENTIFIER);

			return true;
		} else if (isSpace(c)) {
			/** SPACE **/
			currentState = SPACE;
			setLastFinalState(SPACE);

			return true;

		} else if (isInteger(c)) {
			/** INTEGER **/
			currentState = INTEGER;
			setLastFinalState(INTEGER);

			return true;
		// Check if special sign (potential 'composite sign'; like ":=" "=:=" "&&")
		} else if (isSign(c) && c != ':' && c != '=' && c != '&') {
			/** currentState START? **/
			currentState = SIGN;
			setLastFinalState(SIGN);

			return false;

		} else if (c == ':') {
			/**SIGN 2 **/
			currentState = COLON;
			setLastFinalState(COLON);

			return true;

		} else if (c == '=') {
			/**SIGN 3 **/
			currentState = EQUAL;
			setLastFinalState(EQUAL);

			return true;

		} else if (c == '&') {
			/**SIGN 3 **/
			currentState = AND_SIGN;
			putBack++;
			return true;

		} else if (isNewline(c)) {
			/** NEWLINE **/
			currentState = NEWLINE;
			setLastFinalState(NEWLINE);
			currentLine++;
			currentColumn = 1;

			return true;

		} else {
			// No recognized lexeme. Ignore error Token.
			setLastFinalState(UNKNOWN);
			// don't go back, keep reading.
			return false;
		}
	}

	//	#(1.)#		Switch through possible reading states
	
	//#(1_A)#	IDENTIFIER STATE
	case IDENTIFIER: {
		if (isIdentifier(c)) {
			return true;
		} else {
			currentState = START;			
			putBack++;
			return false;
		}
	}

	//#(1_B)#	SPACE STATE
	case SPACE: {
		if (isSpace(c)) {
			return true;
		} else {
			currentState = START;
			putBack++;
			return false;
		}
	}

	//#(1_C)#	INTEGER STATE	
	case INTEGER: {
		if (isInteger(c)) {
			return true;
		} else {
			currentState = START;
			putBack++;
			return false;
		}
	}

	//#(1_D)# 	NEWLINE STATE
	case NEWLINE: {
		if (isNewline(c)) {
			currentColumn = 1;
			currentLine++;
			return true;
		} else {
			currentState = START;
			putBack++;
			return false;
		}
	}

	//#(1_E)# 	COLON STATE
	case COLON: {
		if (c == '*') {
			currentState = COMMENT1;	// :*
			setLastFinalState(COMMENT1);
			return true;
			
		} else if (c == '=') {
			currentState = START;
			setLastFinalState(ASSIGN);	// :=
			return false;

		} else {
			// already start of next token; put back
			currentState = START;
			putBack++;
			return false;
		}
	}

	//#(1_E)# 	EQUAL STATE
	//#			last read:		=
	case EQUAL: {
		if (c == ':') {
			currentState = EQUAL_COLON;
			setLastFinalState(EQUAL);

			putBack++;

			return true;

		} else {
			currentState = START;

			putBack++;
			return false;
		}
	}

	//#(1_F)# 	EQUAL STATE
	//#			last read:				=:
	//#			check:	=		for		=:=
	case EQUAL_COLON: {
		if (c == '=') {
			currentState = START;
			setLastFinalState(EQUAL_ASSIGN);
			putBack--;
			return false;
		} else {

			putBack++;
			return false;
		}
	}

	//#(1_E)# 	COMMENT1 STATE
	//#			last read:	:*[...] (currently in comment)
	//# 		check:	*	for		*:	
	case COMMENT1: {
		if (c == '*') {
			currentState = COMMENT2;
			setLastFinalState(COMMENT2);

			return true;
		} else if (isNewline(c)) {
			currentColumn = 1;
			currentLine++;
			return true;
		} else {

			return true;
		}
	}

		//#(1_F)# 	EQUAL STATE
		//#			last read:		*:	[...]	*	(currently in comment)
		//#			check:	:	for	*:
	case COMMENT2: {
		if (c == ':') {
			currentState = COMMENT3;
			setLastFinalState(COMMENT3);

			return true;

		} else if (c == '*') {

			return true;

		} else if (isNewline(c)) {
			currentColumn = 1;
			currentLine++;
			return true;
		} else {
			currentState = COMMENT1;
			setLastFinalState(COMMENT1);

			return true;
		}
	}

	//#(1_G)# 	& STATE
	//#			last read:	&
	//#			check		& for &&
	case AND_SIGN: {
		if (c == '&') {
			currentState = START;
			setLastFinalState(DOUBLE_AND);

			return false;
		} else {
			putBack++;
			return false;
		}
	}

	//#(1_H)# 	FAULTY STATE
	//#			last read:	unknown symbol
	default: {
		
		putBack++;
		return false;
	}
	}//end: state switch
}

/**
 * Purpose:		translates final states of the machine
 * 				into token types
 * @return 		- The last final state of the machine as token type.
 * Comment:		- If there is no valid state, returns type UNKNOWN.
 */
Token::Type Automat::getType() const {
	switch (lastFinalState) {
	case SPACE:
		return Token::SPACE;
	case IDENTIFIER:
		return Token::IDENTIFIER;
	case NEWLINE:
		return Token::NEWLINE;
	case INTEGER:
		return Token::INTEGER;
	case SIGN:
		return Token::SIGN;
	case COLON:
		return Token::COLON;
	case EQUAL:
		return Token::EQUAL;
	case EQUAL_ASSIGN:
		return Token::EQUAL_ASSIGN;
	case COMMENT1:
		return Token::COMMENT;
	case COMMENT2:
		return Token::COMMENT;
	case COMMENT3:
		return Token::COMMENT;
	case DOUBLE_AND:
		return Token::DOUBLE_AND;
	case ASSIGN:
		return Token::ASSIGN;
	default:
		return Token::UNKNOWN;
	}
}

/**
 * Purpose:	Getter for count of chars that were invalid after the last final state.
 * 			Used to tell the buffer how many characters 'to put back' on the machine.
 * @return number of invalid chars after the last final state
 */
int Automat::getBackCount() const {
	return putBack;
}

/**
 * Purpose:	Getter for starting line of the last recognized lexeme
 * @return The index of the starting line
 */
int Automat::getLine() const {
	return startLine;
}

/**
 * Purpose:	Getter for the column of the last recognized lexeme
 * @return The column index of the last lexeme
 */
int Automat::getColumn() const {
	return startColumn;
}

/**
 * Purpose:	Resets the machine to start; for processing the next lexeme
 * @param bad_char_count amount of chars required 'to be put back'
 */
void Automat::reset(int bad_char_count) {
	// we go back in the buffer, so do not count these chars
	currentColumn -= bad_char_count;
	back = 0;
	lastFinalState = UNKNOWN;
	currentState = START;
	startLine = currentLine;
	startColumn = currentColumn;
}

/**
 * Purpose: Setter for last final state.
 * 			Also resets the count that keeps track of the characters required to move back.
 * @param state the desired state
 */
void Automat::setLastFinalState(State state) {
	lastFinalState = state;
	back = 0;	// reset count for putting characters back
}

