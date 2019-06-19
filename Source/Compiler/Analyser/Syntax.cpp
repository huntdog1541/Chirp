#include "Syntax.h"

#include "../Variable.h"

#include <iostream>

void Syntax::ReadIndex(Parser* p)
{
	int pos = 0;

	std::cout << "Index is " << p->Index.size() - 1 << std::endl;

	for (auto& n : p->Index)
	{
		Node node = p->ParseTree.GetNode(n);

		if (node.Value.Identifier == VAR_TOKEN) // If token is variable
		{
			Variable::WriteVarDec(pos,p);
		}
		
		pos++;
	}
}