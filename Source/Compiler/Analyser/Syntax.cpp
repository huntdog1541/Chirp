#include "Syntax.h"

#include <fstream>
#include <iostream>

void Parsed::ReadIndex()
{
	for (auto& pos : this->Index)
	{
		Node node = this->ParseTree.NodeList.at(pos);
		std::cout << node.Value.Lexeme << std::endl;
	}
}