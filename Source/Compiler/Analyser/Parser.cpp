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
			if (Word.compare("") != 0)
			{
				this->Processed.push_back(Word);
				Word.erase();
			}
		}
		else
		{
			if (c == '=' || c == '"' || c == ':' || c == '(' || c == ')' || c == '{' || c == '}')
			{
				if (Word.compare("") != 0) // hmm
				{
					this->Processed.push_back(Word);
					Word.clear();
				}
				Word.append(1, c);
				this->Processed.push_back(Word);
				Word.clear();
			}
			else
			{
				Word.append(1, c);
			}

			if (Pos >= txt.length())
			{
				// Ending
				this->Processed.push_back(Word);
				Word.erase();
			}
		}
	}
}

void Parsed::MakeTree()
{
	Node Start;
	Start.Value.Identifier = TREE_START_TOKEN;
	this->ParseTree.MakeStart(&Start);

/*	Node First;
	First.Value.Identifier = KEYWORD_UNKNOWN_TOKEN;
	this->ParseTree.AddChild(Start.SelfPos,&First);

	Node Second;
	Second.Value.Identifier = KEYWORD_UNKNOWN_TOKEN;
	this->ParseTree.AddChild(Start.SelfPos,&Second);

	Node Third;
	Third.Value.Identifier = KEYWORD_UNKNOWN_TOKEN;
	this->ParseTree.AddChild(First.SelfPos,&Third);

	Node Fifth;
	Fifth.Value.Identifier = KEYWORD_UNKNOWN_TOKEN;
	this->ParseTree.AddChild(First.SelfPos,&Fifth);

	Node Sixth;
	Sixth.Value.Identifier = 666;
	this->ParseTree.AddChild(Second.SelfPos, &Sixth); */
	

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

					if(Cluster.at(pos + 4).Identifier == KEYWORD_UNKNOWN_TOKEN)
                	{
                    	Node Val;
                    	Val.Value.Identifier = VALUE_INTERGER_TOKEN;
                    	ParseTree.AddChild(Val.SelfPos, &Val);
                	}
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

void Parsed::MakeIndex()
{
	bool Finished = false;
	bool Climbing = false; // Will climb until it find the earliest way to fall down

	Node Current;

	Current = this->ParseTree.NodeList.at(this->ParseTree.StartPos); // This isn't pushed to index

	while (!Finished) 
	{
		// This is more understandable if you just think of the positon as a cube
		// pushing agaisnt gravity and falling in holes. Wait no, it doesn't help at all


		if (this->Index.size() == this->ParseTree.NodeList.size())
		{
			Finished = true;
		}

		if (Current.ChildPos.size() == 0) // Can only go up or right
		{
			if (Current.PosInNode < this->ParseTree.GetNode(Current.ParentPos).ChildPos.size() - 1) // Can go to the right
			{
				Current = this->ParseTree.GetNode(this->ParseTree.GetNode(Current.ParentPos).ChildPos.at(Current.PosInNode + 1)); // Go left
			//	this->Index.push_back(Current.SelfPos);
			}
			else // Last child in node that doesn't have child so only choice is to go up 
			{
				if (this->Index.back() == Current.SelfPos) // That means, it start looping on itself
				{
					Finished = true; // Kill
					break;
				}
				Climbing = true;
				this->Index.push_back(Current.SelfPos);
			}
		}
		else // Go down
		{
			Current = this->ParseTree.GetNode(Current.ChildPos.at(0));
			this->Index.push_back(Current.SelfPos);
			Climbing = false;
		}

		if (Climbing) // Go up
		{
			Current = this->ParseTree.GetNode(Current.ParentPos);

			if (Current.PosInNode < this->ParseTree.GetNode(Current.ParentPos).ChildPos.size() - 1) // Check if parent has a sideway node, by now Current should already be the parent
			{
				Current = this->ParseTree.NodeList.at(this->ParseTree.GetNode(Current.ParentPos).ChildPos.at(Current.PosInNode + 1)); // Go left
			}
		}
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

 The order should look like this:

		1
		|
		2
	  /   \
     3     6
	/ \    |
   4   5   7

When climbing up it does not count
*/