#include "Variable.h"

#include <iostream>

void Variable::Register(int pos, Environement* env)
{
	Object Var; // New variable
	bool Failure = false;

	bool hasName = false;
	bool hasType = false;

	std::string Name;
	std::string Type;

	Token t = env->Cluster.at(pos);

	try
	{
		Name = env->Cluster.at(pos + 1).Lexeme; // type : >name<
		Type = env->Cluster.at(pos - 1).Lexeme; // >type< : name
	}
	catch (std::out_of_range)
	{
		Log::Error::Custom("Error at variable definiton scouting"); // Scouting, is exploring to see what are the values
		Failure = true;
	}

	if (!Failure)
	{
		Var.Name = Name;

		if (Type.compare("int") == 0) // 2 bytes
		{
			Var.Size = 2;
		}
		if (Type.compare("char") == 0 || Type.compare("bool") == 0) // 1 byte
		{
			Var.Size = 1;
		}
		if (Type.compare("string") || Type.compare("float") == 0) // 4 bytes
		{
			Var.Size = 4;
		}
		else // Size for all occasions
		{
			Var.Size = 2;
		}

		env->ObjectList.push_back(Var);
	}
}

std::string Variable::Assign(int pos, Environement* env)
{
	bool Failure = false;
	bool TargetSet = false; //This should look like int: Target = Source
	bool SourceSet = false; 

	std::string Target; // Variable to be assigned

	for (int i = pos; i < env->Cluster.size() - 1; i++) // This has ok efficiency
	{
	//	Node n = env->ParseTree.GetNode(env->Index.at(i));
		Token t = env->Cluster.at(i);

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