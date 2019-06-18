#include "Syntax.h"

#include "../Variable.h"

#include <iostream>

void Parser::ReadIndex()
{
	for (auto& pos : this->Index)
	{
		Node node = this->ParseTree.NodeList.at(pos);

		if (node.Value.Identifier == VAR_TOKEN) // If token is variable
		{
			std::cout << "Detected a variable" << std::endl;
		}
	}
}