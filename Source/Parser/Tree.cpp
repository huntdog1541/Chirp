#include "Tree.h"

void Tree::MakeStart(Node n)
{
	int yeet = this->NodeList.size();
	n.SelfPos = yeet;
	this->NodeList.push_back(n);
}

void Tree::AddChild(int pos, Node n)
{
	try
	{
		int yeet = this->NodeList.size();
		n.SelfPos = yeet;
		this->NodeList.push_back(n);
	}
	catch (std::out_of_range)
	{
		Log::Error::Custom("Couldn't find Node to add Child to, on the tree.");
	}
}

void Tree::AddChild(Node* p, Node n) // p is for parent, n for node
{

}

Node Tree::FindNode(std::string lexeme)
{
	Node n;

	return n;
}


Node Tree::FindChild(Node* node, std::string lexeme)
{
	Node n;

	return n;
}

Node Tree::GetNode(int pos)
{
	Node n;

	try
	{
		n = this->NodeList.at(pos);
	}
	catch (std::out_of_range)
	{
		Log::Error::Custom("Couldn't find node at given position.");
	}

	return n;
}