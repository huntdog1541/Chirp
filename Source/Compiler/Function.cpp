#include "Function.h"

#include <iostream>

namespace Function
{
	void GenOpen(Environement* env)
	{
		std::string Output = "push ebp \nmov ebp,esp \n";
		env->Text.append(Output);
	}
	void GenClose(Environement* env)
	{
		std::string Output = "mov esp,ebp \npop ebp \nret 0 \n";
		env->Text.append(Output);
	}
	std::string WriteFunction(int pos,Environement* env)
	{
		bool Failure = false;

		bool HasName = false;
		bool IsEntry = false;

		std::string Name;

		for (int i = pos; i < env->Syntax.size() - 1; i++)
		{
			Token t = env->Syntax.at(i);

			if (t.Identifier == OBJECT_ID_TOKEN && !HasName)
			{
				HasName = true;

				if (t.Lexeme.compare(env->EntryLabel) == 0)
				{
					Name = "_start";
				}
				else
				{
					Name = t.Lexeme;
				}
			}

			if (HasName)
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
}