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
		// VAR >VAR_DEC< OBJECT_TYPE CONFIRM OBJECT_NAME
		Name = env->Syntax.at(pos + 2).Lexeme; // type : >name<
		Type = env->Syntax.at(pos + 1).Lexeme; // >type< : name
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
	bool SourceSet = false; // Can be another variable id or value

	std::string Target; // Variable to be assigned
	std::string Source;

	for (int i = pos; i < env->Syntax.size() - 1; i++) // This has ok efficiency
	{
	//	Node n = env->ParseTree.GetNode(env->Index.at(i));
		Token t = env->Syntax.at(i);

		if (t.Identifier == OBJECT_ID_TOKEN)
		{
			if (!TargetSet) // Setting target
			{
				Target = t.Lexeme;
				TargetSet = true;
			}
			else // Is source
			{

			}
		}
		if (t.Identifier == INTERGER_TOKEN && !SourceSet)
		{
			Source = t.Lexeme;
			SourceSet = true;
		}

		if (Failure)
		{
			break;
		}
		if (SourceSet && TargetSet)
		{
			break;
		}
	}

	if (!Failure)
	{
		Object local;
		local = Obj::FindByName(Target,env->ObjectList);
		std::string output = "mov ";

		if (local.Size == 1) // Writing the approriate size
		{
			local.Position = env->Stack + 1;
			output.append("byte");
		}
		else if (local.Size == 2)
		{
			local.Position = env->Stack + 2;
			output.append("word");
		}
		else if (local.Size == 4)
		{
			local.Position = env->Stack + 4;
			output.append("dword");
		}
		else if (local.Size == 8)
		{
			local.Position = env->Stack + 8;
			output.append("qword");
		}

		output.append(" [ebp-").append(std::to_string(local.Position)).append("],").append(Source).append("\n");

		return output;
	}
	else
	{
		Log::Error::Custom("Variable couldn't be assigned");
		return "; Variable registering error here";
	}
}