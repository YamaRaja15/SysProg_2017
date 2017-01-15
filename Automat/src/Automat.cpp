#include "../includes/Automat.h"

Automat::Automat() {
	currentState = START;
	lastFinalState = START;
	startColumn = 1;
	startLine = 1;
	currentLine = 1;
	currentColumn = 1;
	back = 0;
}

Automat::~Automat() {
	// nothing to to here
}

/**
 * CHECKS FOR THE STATES OF THE MACHIN
 */

bool Automat::isSpace(char c) {
	return c == ' ' || c == '\t';
}

bool Automat::isIdentifier(char c) {
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9' && currentState == IDENTIFIER));
}

bool Automat::isInteger(char c) {
	return c >= '0' && c <= '9';
}

bool Automat::isSign(char c) {
	char signs[] = { '+', '-', ':', '*', '<', '>', '=', '!', '&', ';', '(', ')',
			'{', '}', '[', ']' };
	for (int i = 0; i < 16; i++) {
		if (signs[i] == c)
			return true;
	}
	return false;
}

bool Automat::isNewline(char c) {
	return c == '\n' || c == '\r';
}

/**
 * insert next char into the machine
 * if this returns false, you can check the lastfinalstate and back via getters.
 * afterwards do not forget to call reset() before inserting new chars
 * @param  c char to insert
 * @return   returns false if it is not possible that further insertions will lead to a valid state.
 */
bool Automat::accept(char c) {
	currentColumn++;
	switch (currentState) {

	/**
	 * #################
	 * START STATE
	 * #################
	 */
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

		} else if (isSign(c) && c != ':' && c != '=' && c != '&') {
			/** ANYSIGN **/
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
			back++;
			return true;

		} else if (isNewline(c)) {
			/** NEWLINE **/
			currentState = NEWLINE;
			setLastFinalState(NEWLINE);
			currentLine++;
			currentColumn = 1;

			return true;

		} else {

			back++;
			return false;
		}
	}

		/**
		 * #################
		 * IDENTIFIER STATE
		 * #################
		 */
	case IDENTIFIER: {
		if (isIdentifier(c)) {

			return true;
		} else {
			currentState = START;

			back++;
			return false;
		}
	}

		/**
		 * #################
		 * SPACE STATE
		 * #################
		 */
	case SPACE: {
		if (isSpace(c)) {

			return true;
		} else {
			currentState = START;

			back++;
			return false;
		}
	}

		/**
		 * #################
		 * INTEGER STATE
		 * #################
		 */
	case INTEGER: {
		if (isInteger(c)) {

			return true;
		} else {
			currentState = START;

			back++;
			return false;
		}
	}

		/**
		 * #################
		 * NEWLINE STATE
		 * #################
		 */
	case NEWLINE: {
		if (isNewline(c)) {
			currentColumn = 1;
			currentLine++;

			return true;

		} else {
			currentState = START;

			back++;
			return false;
		}
	}

		/**
		 * #################
		 * COLON STATE
		 * #################
		 */
	case COLON: {
		if (c == '*') {
			currentState = COMMENT1;
			setLastFinalState(COMMENT1);

			return true;
		} else if (c == '=') {
			currentState = START;
			setLastFinalState(ASSIGN);

			return false;

		} else {
			currentState = START;

			back++;
			return false;
		}
	}

		/**
		 * #################
		 * EQUAL STATE
		 * #################
		 */
	case EQUAL: {
		if (c == ':') {
			currentState = EQUAL_COLON;
			setLastFinalState(EQUAL);

			back++;

			return true;

		} else {
			currentState = START;

			back++;
			return false;
		}
	}

		/**
		 * #################
		 * EQUAL COLON STATE
		 * #################
		 */
	case EQUAL_COLON: {
		if (c == '=') {
			currentState = START;
			setLastFinalState(EQUAL_ASSIGN);
			back--;
			return false;
		} else {

			back++;
			return false;
		}
	}

		/**
		 * #################
		 * COMMENT1 STATE
		 * #################
		 */
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
		/**
		 * #################
		 * COMMENT2 STATE
		 * #################
		 */
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

		/**
		 * #################
		 * AND STATE
		 * #################
		 */
	case AND_SIGN: {
		if (c == '&') {
			currentState = START;
			setLastFinalState(DOUBLE_AND);

			return false;
		} else {
			back++;
			return false;
		}
	}
		/**
		 * #################
		 * ANYSIGN STATE
		 * #################
		 */

		/**
		 * #################
		 * SIGN5 STATE
		 * #################
		 */

	default: {
		back++;
		return false;
	}
	}
}

/**
 * translate final states of the machine into token types
 * @return last final state of the machine as token type. if there is no valid last final state, this will 
 * return the token type UNKNOWN
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
 * how many chars were invalid after the last final state
 * @return number of invalid chars after the last final state
 */
int Automat::getBack() const {
	return back;
}

/**
 * get the start line of the last recognized lexem
 * @return [description]
 */
int Automat::getLine() const {
	return startLine;
}

/**
 * get the column of the last recognized lexem
 * @return [description]
 */
int Automat::getColumn() const {
	return startColumn;
}

/**
 * reset the machine to start processing the next lexem
 * @param bad_char_count how many chars back
 */
void Automat::reset(int bad_char_count) {
	// we go back in the buffer, so do not count these chars
	currentColumn -= bad_char_count;
	back = 0;
	lastFinalState = UNDEFINED;
	currentState = START;
	startLine = currentLine;
	startColumn = currentColumn;
}

/**
 * set last final state. this is a separate method as it is easy to forget resetting back = 0
 * @param state the last final state
 */
void Automat::setLastFinalState(State state) {
	lastFinalState = state;
	back = 0;
}

