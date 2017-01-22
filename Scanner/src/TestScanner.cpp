#include "../includes/Scanner.h"

#include <cstddef>
#include <iostream>
#include <fstream>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	// check if a path to a text file is provided
	cout << "processing..." << '\n';

	if (argc == 3) {
		Scanner* scanner = new Scanner(argv[1]);

		Token* token = scanner->nextToken();

		std::ofstream output_file;
		output_file.open(argv[2]);

		while (token != NULL) {
			if(token->getType()==Token::UNKNOWN){
				cout << "Token: "
									<< Token::token_type_as_string(token->getType()) << '\t';
				cout << "Line: " << token->getLine() << ' ';
				cout << "Column: " << token->getColumn() << ' ';

							cout << '\n';
			}
			output_file << "Token: "
					<< Token::token_type_as_string(token->getType()) << '\t';
			output_file << "Line: " << token->getLine() << ' ';
			output_file << "Column: " << token->getColumn() << ' ';
			if (token->getType() == Token::INTEGER) {
				output_file << "Value: " << token->getValue() << '\n';
			} else if (token->getType() == Token::IDENTIFIER) {
				output_file << "Lexem: " << token->getInformation()->getLexem()
						<< '\n';
			} else {
				output_file << '\n';
			}

			token = scanner->nextToken();
		}
		printf("stop");

		cout << "stop";

		output_file.close();
		delete scanner;
	} else {
		std::cout
				<< "Call the test with a path to a test file and a path to the output file!"
				<< std::endl;
	}
}
