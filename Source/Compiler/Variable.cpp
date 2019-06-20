#include "Variable.h"

#include <iostream>

std::string Variable::Register(int pos,Environement* env)
{
	Object Var; // New variable
	bool Failure = false;

	bool hasName = false;
	bool hasType = false;

	for (int i = pos; i < env->Cluster.size() - 1; i++)
	{
	//	Node n = env->ParseTree.GetNode(env->Index.at(i));
		Token t = env->Cluster.at(env->Index.at(i));
		
		if (hasName && hasType)// So it does read another variable dec
		{
			break;
		}

		if (t.Identifier == OBJECT_TYPE_TOKEN)
		{
			if (t.Lexeme.compare("int") == 0) // 2 Bytes
			{
				Var.Size = 2;
			}
			else if (t.Lexeme.compare("char") == 0 || t.Lexeme.compare("bool") == 0) // 1 byte
			{
				Var.Size = 1;
			}
			else // Default size, 4 byte
			{
				Var.Size = 4;
			}

			hasType = true;
		}
		if (t.Identifier == OBJECT_ID_TOKEN)
		{
			Var.Name == t.Lexeme;
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
	//	Node n = env->ParseTree.GetNode(env->Index.at(i));
		Token t = env->Cluster.at(env->Index.at(i));

		if (t.Identifier == OBJECT_ID_TOKEN)
		{
			if (!TargetSet) // Setting target
			{
				Target = t.Identifier;
				TargetSet = true;
			}
			else // Is source
			{

			}
		}
		if (t.Identifier == VALUE_INTERGER_TOKEN)
		{
		}
	}

	if (!Failure)
	{
		return "frf";
	}
	else
	{
		Log::Error::Custom("Variable couldn't be assigned");
		return "; Error here";
	}
}