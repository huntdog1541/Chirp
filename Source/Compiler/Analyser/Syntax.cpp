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
				// >int< : a = 123
				Token Var;
				Var.Identifier = VAR_TOKEN;
				env->Syntax.push_back(Var);

				Token Dec; // Declaration
				Dec.Identifier = VAR_DEC_TOKEN;
				env->Syntax.push_back(Dec);

				env->Syntax.push_back(env->Cluster.at(pos)); // Data type
				
				Token Name;
				Name.Identifier = OBJECT_ID_TOKEN;
				Name.Lexeme = env->Cluster.at(pos + 2).Lexeme;
				env->Syntax.push_back(Name); // After Assignement, so it's in order
			}
			else // Is probably a function
			{

			}
		}
		if (t.Identifier == ASSIGNEMENT_OPERATOR_TOKEN) // Assignement
		{
			Token Exp; // Expression
			Exp.Identifier = EXPRESSION_TOKEN;
			env->Syntax.push_back(Exp);

			env->Syntax.push_back(t);
			
			Token Value; // Very very very very temporary
			Value.Identifier = INTERGER_TOKEN;
			Value.Lexeme = env->Cluster.at(pos + 1).Lexeme;
			env->Syntax.push_back(Value);
		}
		if (t.Identifier == GATE_SCOPE_TOKEN)
		{
			env->Syntax.push_back(t);
		}
		if (t.Identifier == KEYWORD_ENTRY_TOKEN) // Entry functions
		{
			Token Func;
			Func.Identifier = FUNC_TOKEN;
			env->Syntax.push_back(Func);

			env->Syntax.push_back(t);

			Token Name;
			Name.Identifier = OBJECT_ID_TOKEN;
			Name.Lexeme = env->Cluster.at(pos + 1).Lexeme;

			if (Name.Lexeme.compare("(") == 0)
			{
				Name.Lexeme = "undefined";
				env->Syntax.push_back(Name);
			}
			else
			{
				env->Syntax.push_back(Name);
			}

			env->EntryLabel = Name.Lexeme;

			Token Arg;
			Arg.Identifier = GATE_ARG_TOKEN;
			Arg.Lexeme = "(";
			env->Syntax.push_back(Arg);
			Arg.Lexeme = ")";
			env->Syntax.push_back(Arg);
		}
		pos++;
	}
}