#include "Variable.h"

#include <iostream>

std::string Variable::WriteVarDec(int pos,Parser* p)
{
	Object Var; // New variable
	bool Failure = false;

	for (int i = pos; i < p->Index.size() - 1; i++) // This has ok efficiency
	{
		Node n = p->ParseTree.GetNode(p->Index.at(i));
		
		if (n.Value.Identifier == OBJECT_TYPE_TOKEN)
		{
			if (n.Value.Lexeme.compare("int") == 0) // 2 Bytes
			{
				std::cout << "Variable is an interger" << std::endl;
				Var.Size = 2;
			}
			else // Default size, 4 byte
			{
				Var.Size = 4;
			}
		}
		if (n.Value.Identifier == OBJECT_ID_TOKEN)
		{
			
		}
	}

	if (!Failure)
	{

	}

	return "; error at variable writing";
}

std::string Variable::WriteVarDef(int pos, Parser* p)
{
	return "Yet";
}