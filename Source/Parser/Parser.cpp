#include "Parser.h"
#include "Variable.h"

#include "Value.h"

#include <iostream>

//=TREE FUNCTIONS

void Tree::MakeStart(Node n)
{
	int yeet = this->NodeList.size();
	n.SelfPos = yeet;
	this->NodeList.push_back(n);
}

void Tree::AddChild(int pos, Node n)
{
	try
	{
		int yeet = this->NodeList.size();
		n.SelfPos = yeet;
		this->NodeList.push_back(n);
	}
	catch (std::out_of_range)
	{
		Log::Error::Custom("Couldn't find Node to add Child to, on the tree.");
	}
}

Node Tree::FindNode(std::string lexeme)
{
	Node n;

	return n;
}

Node Tree::FindChild(Node* node,std::string lexeme)
{
	Node n;

	return n;
}

Node Tree::GetNode(int pos)
{
	Node n;

	try
	{
		n = this->NodeList.at(pos);
	}
	catch(std::out_of_range)
	{
		Log::Error::Custom("Couldn't find node at given position.");
	}

	return n;
}

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

/*
Actually parses the words in the Parsed class then start the whole thing.
*/
void Parsed::Tokenize()
{
	// Now, here you separate unclassified strings into tokens that will then be analyzed
	// and made into assembly.

	int Pos = -1;
	bool IsString = false; // If it's a string then it wont parse the words below and when the string is closed will be pushed as arguments
	
	Node StartPoint;
	StartPoint.Token = TREE_START_TOKEN;
	this->ParseTree.MakeStart(StartPoint);

	for (auto& txt : this->Unclassified)
	{
		Pos++;
		Node n;
		this->ParseTree.AddChild(0,n);
	}

	this->ParseVar();
	this->ParseFunc();
}