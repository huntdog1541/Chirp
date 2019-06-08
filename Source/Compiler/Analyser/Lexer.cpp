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

	long Pos = -1;
	bool IsString = false; // If it's a string then it wont parse the words below and when the string is closed will be pushed as arguments

	for (auto& txt : this->Unclassified)
	{
		Pos++;

		Token t; // yep it's ya boi, one letter variables here
		
		if (txt.compare("int") == 0 || txt.compare("char") == 0 || txt.compare("float") == 0)
		{
			t.Identifier = VALUE_CAST_TOKEN;
			t.lexeme = txt;

			if (this->Unclassified.at(Pos + long(1)).compare(":") == 0)
			{
				// Variable
				t.Identifier = VAR_DEF_CONFIRM_TOKEN;
				t.lexeme = txt;
			}
			else
			{
				// ...
			}
		}
		else if (txt.compare("=") == 0)
		{
			t.Identifier = VAR_ASSIGN_OP_TOKEN;
			t.lexeme = txt;
		}
		else
		{
			t.Identifier = KEYWORD_UNKNOWN_TOKEN;
			t.lexeme = txt;
		}
		this->Cluster.push_back(t);
	}

	this->ParseVar();
	this->ParseFunc();
}