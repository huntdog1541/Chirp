#include "Variable.h"

#include <iostream>

std::string Variable::WriteVarDec(int pos,Environement* env)
{
	Object Var; // New variable
	bool Failure = false;

	bool hasName = false;
	bool hasType = false;

	for (int i = pos; i < env->Index.size() - 1; i++) // This has ok efficiency
	{
		Node n = env->ParseTree.GetNode(env->Index.at(i));
		
		if (hasName && hasType)// So it does read another variable dec
		{
			break;
		}

		if (n.Value.Identifier == OBJECT_TYPE_TOKEN)
		{
			if (n.Value.Lexeme.compare("int") == 0) // 2 Bytes
			{
				Var.Size = 2;
			}
			else // Default size, 4 byte
			{
				Var.Size = 4;
			}
			hasType = true;
		}
		if (n.Value.Identifier == OBJECT_ID_TOKEN)
		{
			Var.Name == n.Value.Lexeme;
			hasType = true;
		}
	}

	if (!Failure)
	{
		env->ObjectList.push_back(Var);
	}

	return "; error at variable writing";
}

std::string Variable::WriteVarDef(int pos, Environement* p)
{
	return "Yet";
}