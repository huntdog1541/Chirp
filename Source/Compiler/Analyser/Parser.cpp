#include "Parser.h"

#include "../Variable.h"
#include "../Value.h"

#include <iostream>

//=CLASS CONSTRUCTORS


Value::Value()
{

}

Variable::Variable()
{
	this->stackPos = 4;
}


Scope::Scope()
{

}

Statement::Statement()
{

}


/*
Makes the string into processable code
*/
Parsed::Parsed(std::string txt)
{
// Ok so basically in here let's seperate words.
// and make them in seperate keywords, but let's not touch any assembly code
// because the nicely parsed objects will be forwared to the assembly portion
// of the compiler.

	std::string Word;
	int Pos = 0;

	for (char& c : txt) // The eagle eyed among, may have noticed this look like something from Powerscript
	{
		Pos++;
		if (isspace(c) || c == '\n')
		{
			//p_b
			if (Word.compare("") != 0)
			{
				this->Unclassified.push_back(Word);
				Word.erase();
			}
		}
		else
		{
			if (c == '=' || c == '"' || c == ':' || c == '(' || c == ')' || c == '{' || c == '}')
			{
				if (Word.compare("") != 0) // hmm
				{
					this->Unclassified.push_back(Word);
					Word.clear();
				}
				Word.append(1, c);
				this->Unclassified.push_back(Word);
				Word.clear();
			}
			else
			{
				Word.append(1, c);
			}

			if (Pos >= txt.length())
			{
				// Ending
				this->Unclassified.push_back(Word);
				Word.erase();
			}
		}
	}
}

void Parsed::Parse()
{

}