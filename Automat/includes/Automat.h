#ifndef AUTOMAT_H
#define AUTOMAT_H

#include "Token.h"

class Automat {
	private:
		typedef enum {
			START = 0,
			IDENTIFIER,
			SPACE,
			INTEGER,
			SIGN,
			COLON,
			EQUAL,
			AND_SIGN,
			DOUBLE_AND,
			ASSIGN,
			EQUAL_COLON,
			EQUAL_ASSIGN,
			COMMENT1,
			COMMENT2,
			COMMENT3,
			NEWLINE,
			UNKNOWN
		} State;

		State currentState;
		State lastFinalState;

		int startColumn;
		int startLine;
		int currentLine;
		int currentColumn;
		int back;

		void setLastFinalState(State);

	public:
		Automat();
		virtual ~Automat();

		bool accept (char c);
		void reset(int line, int column);

		bool isSpace(char c);
		bool isIdentifier(char c);
		bool isInteger(char c);
		bool isSign(char c);
		bool isNewline(char c);

		Token::Type getType() const;
		int getBack() const;
		int getLine() const;
		int getColumn() const;
		
};

#endif /* AUTOMAT_H */
