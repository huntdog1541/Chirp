#include "Variable.h"

#include <iostream>

std::string Variable::Register(int pos,Environement* env)
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
			else if (n.Value.Lexeme.compare("char") == 0 || n.Value.Lexeme.compare("bool") == 0) // 1 byte
			{
				Var.Size = 1;
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

	return "; Debug: Object has been pushed to vector";
}

std::string Variable::Assign(int pos, Environement* env)
{
	bool Failure = false;
	bool TargetSet = false; //This should look like int: Target = Source
	bool SourceSet = false; 
	std::string Target; // Variable to be assigned

	for (int i = pos; i < env->Index.size() - 1; i++) // This has ok efficiency
	{
		Node n = env->ParseTree.GetNode(env->Index.at(i));

		std::cout << "pos is " << i << std::endl; 

		if (n.Value.Identifier == OBJECT_ID_TOKEN)
		{
			if (!TargetSet) // Setting target
			{
				Target = n.Value.Identifier;
				TargetSet = true;
			}
			else // Is source
			{

			}
		}
		if (n.Value.Identifier == VALUE_INTERGER_TOKEN)
		{
			std::cout << "yeet int val " << std::endl;
		}
	}

	if (!Failure)
	{
		std::cout << "does it have a name" << std::endl;
		return "frf";
	}
	else
	{
		Log::Error::Custom("Variable couldn't be assigned");
		return "; Error here";
	}
}