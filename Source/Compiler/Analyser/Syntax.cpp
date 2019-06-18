#include "Syntax.h"

#include "../Variable.h"

#include <iostream>

void Parser::ReadIndex()
{
	int pos = 0;

	for (auto& n : this->Index)
	{
		Node node = this->ParseTree.GetNode(n);

		if (node.Value.Identifier == VAR_TOKEN) // If token is variable
		{
			Variable::MakeVar(pos);
		}
		
		pos++;
	}
}