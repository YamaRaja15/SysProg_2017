#ifndef AUTOMAT_H
#define AUTOMAT_H

#include "Token.h"

class Automat {
	private:
		typedef enum {
			START = 0,
			IDENTIFIER,	// For Identifiers and (temporarily) keywords
			SPACE,		
			INTEGER,
			SIGN,
			COLON,
			EQUAL,
			AND_SIGN,
			DOUBLE_AND,		// &&
			ASSIGN,
			EQUAL_COLON,	// =:
			EQUAL_ASSIGN,	// =:=
			COMMENT1,		// *:
			COMMENT2,		// 
			COMMENT3,
			NEWLINE,
			UNKNOWN	// For Error Tokens
		} State;

		State currentState;
		State lastFinalState;

		int startColumn;
		int startLine;
		int currentLine;
		int currentColumn;
		int putBack;		// Counts amount of characters to put back in case
							// too many have been 'looked at' during token creation process

		void setLastFinalState(State);

	public:
		Automat();
		virtual ~Automat();

		bool accept (char c);
		void reset(int bad_char_count);

		bool isSpace(char c);
		bool isIdentifier(char c);
		bool isInteger(char c);
		bool isSign(char c);
		bool isNewline(char c);

		Token::Type getType() const;
		int getBackCount() const;
		int getLine() const;
		int getColumn() const;
};

#endif /* AUTOMAT_H */
