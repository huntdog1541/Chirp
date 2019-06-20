#include "Syntax.h"

#include "../Variable.h"

#include <iostream>

void Syntax::MakeSyntax(Environement* env)
{
	int pos = 0;

	for (auto& t : env->Cluster)
	{
		if (t.Identifier == OBJECT_TYPE_TOKEN)
		{
			if (env->Cluster.at(pos + 1).Identifier == VAR_CONFIRM_TOKEN) // Is a variable
			{
				Token Var;
				Var.Identifier = VAR_TOKEN;
				env->Syntax.push_back(Var);

				env->Syntax.push_back(env->Cluster.at(pos - 1));

				Token Name;
				Name.Identifier = OBJECT_ID_TOKEN;
				Name.Lexeme = env->Cluster.at(pos + 1).Lexeme;

				env->Syntax.push_back(Name); // After type, so it's in order
			}
			else // Is probably a function
			{

			}
		}
		if (t.Identifier == VAR_ASSIGN_OP_TOKEN) // Assign operator
		{
			Token Exp; // Expression
			Exp.Identifier = EXPRESSION_TOKEN;
		}
		pos++;
	}
}