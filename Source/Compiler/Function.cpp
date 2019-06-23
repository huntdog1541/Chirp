#include "Function.h"
#include "Output.h"

#include <iostream>

namespace Function
{
	void GenOpen(Environement* env)
	{
	//	std::string Output = "push ebp \nmov ebp,esp \n";

		std::string Out = "push ";
		Out.append(Output::Reg("bp",env));
		Out.append("\nmov ");
		Out.append(Output::Reg("bp",env));
		Out.append(", ");
		Out.append(Output::Reg("sp",env));
		Out.append("\n");

		env->Text.append(Out);
	}
	void GenClose(Environement* env)
	{
	//	std::string Output = "mov esp,ebp \npop ebp \nret 0 \n";
		std::string Out = "mov ";
		Out.append(Output::Reg("sp",env));
		Out.append(", ");
		Out.append(Output::Reg("bp",env));
		Out.append("\npop ");
		Out.append(Output::Reg("bp",env));
		Out.append("\nret 0 \n");
		
		env->Text.append(Out);
	}
	void RegisterFunction(int pos,Environement* env)
	{
		// I'm gonna write it, in the next 1-2 commits
	}
	std::string WriteFunction(int pos,Environement* env)
	{
		bool Failure = false;

		bool HasName = false;
		bool IsEntry = false;
		bool InArgs = false;
		bool HasArgs = false;

		std::string Name;

		for (int i = pos; i < env->Syntax.size() - 1; i++)
		{
			Token t = env->Syntax.at(i);

			if (InArgs)
			{
				if (t.Identifier == VAR_DEC_TOKEN)
				{
				//	std::cout << "Var dec inside function" << std::endl;
				}
			}

			if (t.Identifier == GATE_ARG_TOKEN) // Doesn't take into account for example this-> (a()), but I wonder why anyone would do this
			{
				if (InArgs)
				{
				//	std::cout << "closing args" << std::endl;
					InArgs = false;
					HasArgs = true;
				}
				else
				{
				//	std::cout << "open args" << std::endl;
					InArgs = true;
				}
			}

			if (t.Identifier == OBJECT_ID_TOKEN && !HasName && !InArgs && !HasArgs)
			{
				if (t.Lexeme.compare(env->EntryLabel) == 0)
				{
					Name = "_start";
				}
				else
				{
					Name = t.Lexeme;
				}
				HasName = true;
			}

			if (HasName && HasArgs)
			{
				break;
			}
		}

		if (!Failure)
		{
			std::string head = "global ";
			head.append(Name).append("\n");
			env->Header.append(head);

			std::string out = Name;
			Name.append(": \n");
			return Name;
		}

	}
	std::string CallFunction(int pos, Environement* env)
	{
		bool Failure = false;
		bool HasName = false;

		bool HasArgs = false; // For the moment
		bool InArgs = false;

		std::string Name; // Name(), should I call it identifier instead ?

		for (int i = pos; i < env->Syntax.size() - 1; i++)
		{
			Token t = env->Syntax.at(i);

			if (t.Identifier == OBJECT_ID_TOKEN && !HasName && !InArgs)
			{
				Name = t.Lexeme;
				HasName = true;
			}

			if (t.Identifier == GATE_ARG_TOKEN && !HasArgs)
			{
				if (InArgs)
				{
					HasArgs = true;
					InArgs = false;
				}
				else
				{
					InArgs = true;
				}
			}

			if (HasName && HasArgs)
			{
				// The breakpoint ins't in the same line.
				break;
			}
		}

		if (!HasName)
		{
			Failure = true;
		}

		if (!Failure)
		{
			std::string Output = "call ";
			Output.append(Name);
			Output.append("\n");
			return Output;
		}
		else
		{
			return ";error at function call";
		}
	}
}