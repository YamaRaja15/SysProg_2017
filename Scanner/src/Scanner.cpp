#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include "../includes/Scanner.h"

Scanner::Scanner(const char* filename) {
	buffer = new Buffer(filename);
	automat = new Automat();
	symboltable = new Symboltable();
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete symboltable;
}

/**
 * parses the file until the next lexem's found. Creates a token for it.
 * @return A wonderful token or N<ull, when the end of the file was reached
 */
Token* Scanner::nextToken() {
	char c;

	do {
		c = buffer->getChar();
		if (c == -1) {
			// can not get more chars
			break;
		}
		if (char_count < SCANNER_BUFFER_SIZE) {
			// buffer the char in local buffer
			scanner_buffer[char_count++] = c;
		} else {
			// more chars to buffer than the scanner buffer can handle
			printf("Lexem larger than buffer size ");
		}
	} while (automat->accept(c));

	if (char_count == 0) {
		// if there are no more chars we reached the end
		return NULL;
	};
	return analyse(c, char_count);
}
// Start analyzing...
Token* Scanner::analyse(char c, int char_count) {

	Token::Type lexem_type = automat->getType();
	int bad_char_count = automat->getBack();

	if (lexem_type == Token::NEWLINE || lexem_type == Token::SPACE) {
		// ignore the token types newline, spaces...
		prepareForNextLexem(bad_char_count);

		return nextToken();
	} else if (lexem_type == Token::UNKNOWN) {
		Token* token = new Token(Token::UNKNOWN, automat->getColumn(),
						automat->getLine(), NULL, 0);
				prepareForNextLexem(0);

				return token;
		// reset 0 chars as they are unknown. if we read them again
		// this will result in a endless loop!
		prepareForNextLexem(0);

		return nextToken();
	} else if (lexem_type == Token::COMMENT) {
		// don't make a token for a comment
		scanner_buffer[char_count - bad_char_count] = '\0';
		prepareForNextLexem(bad_char_count);

		return nextToken();
	} else if (lexem_type == Token::ASSIGN) {

		Token* token = new Token(Token::ASSIGN, automat->getColumn(),
				automat->getLine(), NULL, 0);
		prepareForNextLexem(bad_char_count);

		return token;

	} else if (lexem_type == Token::EQUAL) {

		Token* token = new Token(Token::EQUAL, automat->getColumn(),
				automat->getLine(), NULL, 0);

		prepareForNextLexem(bad_char_count);

		return token;

	} else if (lexem_type == Token::COLON) {

		Token* token = new Token(Token::COLON, automat->getColumn(),
				automat->getLine(), NULL, 0);

		prepareForNextLexem(bad_char_count);

		return token;

	} else if (lexem_type == Token::EQUAL_ASSIGN) {

		Token* token = new Token(Token::EQUAL_ASSIGN, automat->getColumn(),
				automat->getLine(), NULL, 0);

		prepareForNextLexem(bad_char_count);

		return token;

	} else if (lexem_type == Token::DOUBLE_AND) {

		Token* token = new Token(Token::DOUBLE_AND, automat->getColumn(),
				automat->getLine(), NULL, 0);

		prepareForNextLexem(bad_char_count);

		return token;

	} else if (lexem_type == Token::SIGN) {

		if (c == '+') {
			lexem_type = Token::PLUS;
		}
		if (c == '-') {
			lexem_type = Token::MINUS;
		}
		if (c == '*') {
			lexem_type = Token::ASTERIK;
		}
		if (c == '<') {
			lexem_type = Token::SMALLER;
		}
		if (c == '>') {
			lexem_type = Token::LARGER;
		}
		if (c == '!') {
			lexem_type = Token::EXCLAMATION_MARK;
		}
		if (c == ';') {
			lexem_type = Token::SEMICOLON;
		}
		if (c == '[') {
			lexem_type = Token::SQUARE_BRACKET_OPEN;
		}
		if (c == ']') {
			lexem_type = Token::SQUARE_BRACKET_CLOSE;
		}
		if (c == '(') {
			lexem_type = Token::PARANTHESE_OPEN;
		}
		if (c == ')') {
			lexem_type = Token::PARANTHESE_CLOSE;
		}
		if (c == '{') {
			lexem_type = Token::CURLY_BRACKET_OPEN;
		}
		if (c == '}') {
			lexem_type = Token::CURLY_BRACKET_CLOSE;
		}

		Token* token = new Token(lexem_type, automat->getColumn(),
				automat->getLine(), NULL, 0);

		prepareForNextLexem(bad_char_count);

		return token;

	} else if (lexem_type == Token::INTEGER) {
		// make an Integer Token
		int column = automat->getColumn();
		int line = automat->getLine();

		// parse to integer
		scanner_buffer[char_count - bad_char_count] = '\0';
		long int value = strtol(scanner_buffer, NULL, 10);

		prepareForNextLexem(bad_char_count);

		// this might fail
		if (errno == EINVAL) {
		} else if (errno == ERANGE) {
		} else {
			Token* token = new Token(lexem_type, column, line, NULL, value);
			return token;
		}

		// if this could not be parsed, continue with the next token.
		return nextToken();
		// Check if identifier is either keyword "if" or "while"
	} else if (lexem_type == Token::IDENTIFIER) {

		int lexem_length = char_count - bad_char_count;
		scanner_buffer[lexem_length] = '\0';
		Information* info = new Information(scanner_buffer);
		
		// Lexemtyp anpassen bei Keyword?
		if (compareArray(scanner_buffer, "IF") ||
				compareArray(scanner_buffer, "if")){
				lexem_type = Token::IF;
			
		} else if (compareArray(scanner_buffer, "WHILE") ||
				compareArray(scanner_buffer, "while")){
				lexem_type = Token::WHILE;
		} else{
			// Ansonsten Identifier in SymbolTabelle einfügen
			symboltable->insert(scanner_buffer);
		}
			// Token für erkanntes Lexem erzeugen.
			Token* token = new Token(lexem_type, automat->getColumn(),
					automat->getLine(), info, 0);
			prepareForNextLexem(bad_char_count);
			return token;
	}
	return NULL;
}
void Scanner::prepareForNextLexem(int back) {

	for (int i = 0; i < back; i++) {
		buffer->ungetChar();
	}
	automat->reset(buffer->getLine(), buffer->getColumn());
	char_count = 0;
}

// For checking whether an identified identifier is a keyword.
// used by: analyse()

/**
 * Methode prüft, ob zwei char arrays gleich sind.
 */
bool Scanner::compareArray(char* array1, char* array2) {
	int i = 0;
	while (array1[i] != '\0' && array2[i] != '\0') {
		if (array1[i] != array2[i]) {
			return false;
		}
		i++;
	}
	if (array1[i] != '\0' || array2[i] != '\0') {
		return false;
	}
	return true;
}

