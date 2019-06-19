#include "Syntax.h"

#include "../Variable.h"

#include <iostream>

void Syntax::ReadIndex(Environement* env)
{
	int pos = 0;

	bool InVar;

	std::cout << "Index is " << env->Index.size() - 1 << std::endl;

	for (auto& n : env->Index)
	{
		Node node = env->ParseTree.GetNode(n);

		if (node.Value.Identifier == VAR_TOKEN) // If token is variable
		{
			env->Text.append(Variable::WriteVarDec(pos,env));
		}
		
		pos++;
	}
}