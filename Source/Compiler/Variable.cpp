#include "Variable.h"
#include "../Console/Log/Log.h"

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

std::string Variable::Operation(int pos, Environement* env)
{
	// The types looks like this
	// 0: Addition
	// 1: Substraction
	// 2: Multiplication
	// 3: Division
	// 4: Incrementation
	// 5: Decrementation
	int Op;

	std::string OpSymbol = env->Syntax.at(pos).Lexeme;

	Token First = env->Syntax.at(pos - 1);
	Token Second = env->Syntax.at(pos + 1);

//	std::cout << "Operation is " << env->Syntax.at(pos).Lexeme << std::endl;

	// Recognizing symbol
	if(OpSymbol.compare("+") == 0)
	{
		Op = 0;
	}
	else if (OpSymbol.compare("-") == 0)
	{
		Op = 1;
	}
	else if (OpSymbol.compare("*") == 0)
	{
		Op = 2;
	//	Log::Warning("Multiplication aren't implemented yet");
	}
	else if (OpSymbol.compare("/") == 0)
	{
		Op = 3;
	//	Log::Warning("Divisions aren't implemented yet");
	}
	else if (OpSymbol.compare("++") == 0)
	{
		Op = 4;
	}
	else if (OpSymbol.compare("--") == 0)
	{
		Op = 5;
	}

	if (First.Identifier == INTERGER_TOKEN && Second.Identifier == INTERGER_TOKEN) // Two constant intergers
	{
		// Ok, so this is the first little optimisation
		switch (Op)
		{
		case 0: // Addition
			return std::to_string(std::stoi(First.Lexeme) + std::stoi(Second.Lexeme));
			break;
		case 1: // Substraction
			return std::to_string(std::stoi(First.Lexeme) - std::stoi(Second.Lexeme));;
			break;
		case 2: // Multiplication
			return std::to_string(std::stoi(First.Lexeme) * std::stoi(Second.Lexeme));
			break;
		case 3: // Division
			return std::to_string(std::stoi(First.Lexeme) / std::stoi(Second.Lexeme));
		//	return "12";
			break;
		case 4: // Inc
			Log::Warning("Decrementation isn't implemented yet, the specific part of the code won't be compiled");
			return "0";
			break;
		case 5: // Dec
			Log::Warning("Decrementation isn't implemented yet, the specific part of the code won't be compiled");
			return "0";
			break;
		}
	}
	else
	{

	}

	return "; addition";
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

		if (t.Identifier == ASSIGNEMENT_OPERATOR_TOKEN && !SourceSet)
		{
		//	std::cout << t.Lexeme << std::endl << std::endl;
			if (env->Syntax.at(i + 2).Identifier != ARITHMETIC_OPERATOR_TOKEN)
			{
				Source = env->Syntax.at(i + 1).Lexeme;
				SourceSet = true;
			}
		}

		if (t.Identifier == ARITHMETIC_OPERATOR_TOKEN && !SourceSet)
		{
		//	std::cout<<std::to_string(std::stoi("100") / std::stoi("10"))<<std::endl;
			Source = Variable::Operation(i,env);
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

		env->Stack = local.Position; // So the stack updates

		output.append(" [ebp-").append(std::to_string(local.Position)).append("],").append(Source).append("\n");

		return output;
	}
	else
	{
		Log::Error::Custom("Variable couldn't be assigned");
		return "; Variable registering error here";
	}
}