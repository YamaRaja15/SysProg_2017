#ifndef TOKEN_H
#define TOKEN_H

#include "../../Scanner/includes/Information.h"

class Token {

	public:
		enum Type {
			//Special cases
			NEWLINE = 0, // ensure start counting at 0
			SPACE,
			UNKNOWN,
			COMMENT,
			SIGN,// For returning 'sign' to scanner
			

			// Identifier and Keywords
			IDENTIFIER,
			INTEGER,
			WHILE,
			IF,
	
			// Special signs and special sign compounds
			PLUS,				// +
			MINUS,				// -
			COLON,				// :
			ASTERIK,			// *
			SMALLER,			// 
			LARGER,				// 
			EQUAL,				// =
			ASSIGN,				// :
			EQUAL_ASSIGN,		// :=
			EXCLAMATION_MARK,	// !
			DOUBLE_AND,			// &&
			SEMICOLON,			// ;

			// Brackets
			SQUARE_BRACKET_OPEN, // [
			SQUARE_BRACKET_CLOSE,// ]
			PARANTHESIS_OPEN, 	 // (
			PARANTHESIS_CLOSE,
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
				"SIGN",
				
				"Identifier",
				"Integer",
				"while",
				"if",

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
				"Paranthesis open", // (
				"Paranthesis close",
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
