#include "Syntax.h"

#include "../Variable.h"

#include <iostream>

void Syntax::ReadIndex(Environement* env)
{
	int pos = 0;

	bool InVar;
	bool ScopeOpened;
	
	int lPos; // Local scope position

	for (auto& t : env->Cluster)
	{
	//	Node node = env->ParseTree.GetNode(n);

		if (t.Identifier == GATE_SCOPE_TOKEN) // Start new scope
		{

		}
		if (t.Identifier == VAR_TOKEN) // If token is variable
		{
			env->Text.append(Variable::Register(pos,env));
		}
		if (t.Identifier == VAR_DEF_TOKEN) // Variable operations
		{
			env->Text.append(Variable::Assign(pos,env));
		}
		
		pos++;
	}
}