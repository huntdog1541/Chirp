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
	Node Start;
	Start.Value.Identifier = TREE_START_TOKEN;
	this->ParseTree.MakeStart(Start);

	int pos = 0;

	for (auto& token : this->Cluster) // Loops trough token cluster
	{
		if (token.Identifier == OBJECT_CAST_TOKEN) // var or func ? hmm
		{
			// When token is here, you should be there:
			// int: a = 123 | int: a | int a()
			// ^^^            ^^^      ^^^
			if (Cluster.at(pos + 1).Identifier == VAR_CONFIRM_TOKEN) // the : symbol
			{
				Node Variable;
				Variable.Value.Identifier = VAR_TOKEN;
				ParseTree.AddChild(Start.SelfPos,&Variable);

				Node Declaration;
				Declaration.Value.Identifier = VAR_DEC_TOKEN;
				ParseTree.AddChild(Variable.SelfPos,&Declaration);

				Node Name;
				Name.Value.Identifier = OBJECT_ID_TOKEN;
				Name.Value.Lexeme = Cluster.at(pos + 2).Lexeme;
				ParseTree.AddChild(Declaration.SelfPos,&Name);

				if (Cluster.at(pos + 3).Identifier == VAR_ASSIGN_OP_TOKEN) // has def
				{
					Node Definition;
					Definition.Value.Identifier = VAR_DEF_TOKEN;
					ParseTree.AddChild(Variable.SelfPos, &Definition);

					// Link dat tree
					ParseTree.SetChild(Definition.SelfPos,&Name);
				}
                if(Cluster.at(pos + 4).Identifier == KEYWORD_UNKNOWN_TOKEN)
                {
                    Node Val;
                    Val.Value.Identifier = VALUE_INTERGER_TOKEN;
                    ParseTree.AddChild(Val.SelfPos, &Val);
                }
			}
			else // function
			{
				// ...
			}
		}
		pos++;
	}
}

/*
A tree can look like this

		TREE_START_TOKEN	
		       |
			VAR_TOKEN
			/       \
 VAR_DEC_TOKEN      VAR_DEF_TOKEN

 then there is other stuff
*/