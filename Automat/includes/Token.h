#ifndef TOKEN_H
#define TOKEN_H

#include "../../Scanner/includes/Information.h"

class Token {

	public:
		enum Type {
			NEWLINE = 0, // ensure start counting at 0
			SPACE,
			UNKNOWN,
			COMMENT,

			IDENTIFIER,
			INTEGER,
			WHILE,
			IF,
			ELSE,


			SIGN,
			PLUS,
			MINUS,
			COLON,
			ASTERIK,
			SMALLER,
			LARGER,
			EQUAL,
			ASSIGN,
			EQUAL_ASSIGN,
			EXCLAMATION_MARK,
			DOUBLE_AND,
			SEMICOLON,

			SQUARE_BRACKET_OPEN, // [
			SQUARE_BRACKET_CLOSE,
			PARANTHESE_OPEN, // (
			PARANTHESE_CLOSE,
			CURLY_BRACKET_OPEN, // {
			CURLY_BRACKET_CLOSE,

			ENUM_END_MARKER // marker to know how many elements the enum contains
		};

		// string representation of the Token::Type enum
		static const char* token_type_as_string(Type type) {
			const char* token_type_as_string[ENUM_END_MARKER] = {


				"NEWLINE",
				"SPACE",
				"UNKNOWN",
				"COMMENT",

				"Identifier",
				"Integer",
				"while",
				"if",
				"else",


				"SIGN",
				"Plus",
				"Minus",
				"Colon",
				"Star",
				"Smaller",
				"Larger",
				"Equal",
				"Assign",
				"Equal Assign",
				"Exclamation mark",
				"And and",
				"Semicolon",
				"Square bracket open", // [
				"Square bracket close",
				"Paranthese open", // (
				"Paranthese close",
				"Curly bracket open", // {
				"Curly bracket close"
			};
			return token_type_as_string[type];
		}

		Token(Type type, int column, int line, Information* information, long int value);

		virtual ~Token();

		Information* getInformation() const;
		Type getType() const;
		int getColumn() const;
		int getLine() const;
		long int getValue() const;


	private:
		Information* information;
		int column;
		int line;
		long int value;
		Type type;
};

#endif /* TOKEN_H */
