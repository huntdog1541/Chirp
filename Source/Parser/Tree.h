#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "../Logger/Error.h" // Moved that here, so I wouldn't have to include it twice

// Token macro's below
// Note: They may or may not be in order, but they are grouped
#define TREE_START_TOKEN 0
#define TREE_UNDEFINED_TOKEN 2

#define VAR_TOKEN 3
#define VAR_DEF_TOKEN 4
#define VAR_DEC_TOKEN 5	
#define VAR_ASSIGN_OPERATOR_TOKEN 9

#define VALUE_CAST_TOKEN 6 // Cast Type
#define VALUE_INTERGER_TOKEN 9

#define GATE_STRING_TOKEN 7

#define OBJECT_IDENTIFIER_TOKEN 8

/*
Node in tree class. The elements like parents and child aren't actual other nodes but
the location inside the Tree's Node vector.
*/
class Node
{
public:
	int ParentPos; // Position inside the Node Vector
	int SelfPos; // Position inside the node vector
	std::vector<int> ChildPos; // Positions of the childs inside the Node Vector

	int Token; // Pretty much the type
	std::string Lexeme; // Not used most of the time but is really usefull in some cases
};

/*
Main class to create a tree
*/
class Tree
{
public:
	int StartPos; // Position of the start node
	std::vector<Node> NodeList;

	void MakeStart(Node); // Makes the first node inside the tree

	void AddChild(int, Node); // Adds node to other node at given position
	void AddChild(Node*, Node); // Adds node to other node with given node

	Node GetNode(int); // Returns the node at a specific positon

	Node FindNode(std::string); // Find a node in all the tree, with given Lexeme
	Node FindChild(Node*, std::string); // Find a child of node with given lexeme
};