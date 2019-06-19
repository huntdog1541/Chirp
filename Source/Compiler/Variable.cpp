#include "Variable.h"

#include <iostream>

std::string Variable::WriteVarDec(int pos,Environement* env)
{
	Object Var; // New variable
	bool Failure = false;

	for (int i = pos; i < env->Index.size() - 1; i++) // This has ok efficiency
	{
		Node n = env->ParseTree.GetNode(env->Index.at(i));
		
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

std::string Variable::WriteVarDef(int pos, Environement* p)
{
	return "Yet";
}