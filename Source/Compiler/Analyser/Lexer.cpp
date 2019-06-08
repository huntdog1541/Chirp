#include "Lexer.h"

#include "Parser.h"

#include <iostream>

/*
Actually parses the words in the Parsed class then start the whole thing.
*/
void Parsed::Tokenize()
{
	// Now, here you separate unclassified strings into tokens that will then be analyzed
	// and made into assembly.

	int Pos = -1;
	bool IsString = false; // If it's a string then it wont parse the words below and when the string is closed will be pushed as arguments



	for (auto& txt : this->Unclassified)
	{
		if (txt.compare("int") == 0)
		{
		}
	}

	this->ParseVar();
	this->ParseFunc();
}