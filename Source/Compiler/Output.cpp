#include "Output.h"

#include "Variable.h"
#include "Function.h"
#include "../Console/Log/Error.h"

#include <fstream>
#include <iostream>

namespace Output
{
	void Generate(Environement* env)
	{
	//	std::cout << "Starting assembly generator" << std::endl;

		int Position = 0;
		bool InVar = false; // Inside a variable

		for (auto& tkn : env->Syntax)
		{
			if (tkn.Identifier == VAR_TOKEN)
			{
		//		std::cout << "Inside a variable" << std::endl;
				InVar = true;
			}
			if (tkn.Identifier == VAR_DEC_TOKEN && InVar)
			{
			//	std::cout<<"Registering"<<std::endl;
				Variable::Register(Position,env);
			}
			if (tkn.Identifier == EXPRESSION_TOKEN && InVar)
			{
			//	std::cout << "Assigning" << std::endl;
				env->Text.append(Variable::Assign(Position - 1,env)); // pos - 1 so it starts at name
			}
			if (tkn.Identifier == FUNC_TOKEN)
			{
				env->Text.append(Function::WriteFunction(Position, env));
			}
			if (tkn.Identifier == GATE_SCOPE_TOKEN)
			{
				if (tkn.Lexeme.compare("{") == 0)
				{
					Function::GenOpen(env);
				}
				if (tkn.Lexeme.compare("}") == 0)
				{
					Function::GenClose(env);
				}
			}
			Position++;
		}
	}

	void Write(Environement* env)
	{
		std::ofstream Write(env->AltFile);

		if (!Write)
		{
			Log::Error::Custom("Couldn't write assembly output");
		}
		else
		{
			Write << "section .text \n"; // Stupid problems need lazy solutions
			Write << env->Header.append(env->Text) << std::endl;
			Write.close();
			// Succes
		}
	}
}