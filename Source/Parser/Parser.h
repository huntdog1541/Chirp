#pragma once

#include "../Logger/Error.h"

#include <vector>
#include <string>
#include <stdexcept> // Very important, might create errors if not there on certain system

// The macros below are based on the types, you can read them in the Chirp documentation at 
#define VAR_DEC 0
#define VAR_DEF 1
#define VAR_DEC_AND_DEF 2
#define FUNC_DEF 3
#define FUNC_CALL 4
#define INNER_KEYWORD 5

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
Class used to represent values and parse them. 
*/
class Value
{
public:
	Value();

	void Parse(std::string); // Very important function: Detect and parses

	int iValue; // Interger value
	float fValue; // Float value
	char cValue; // Character value
	std::string sValue; // String value
};

/*
Class used to represent variables that can be rewritten in assembly later.
*/
class Variable
{
public:
	Variable ();

	std::string Name;

	std::string Define ();
	std::string Declare ();

	Value val;

	int Type; // 0 - int, 1 - float, 2 - character
	bool Defined;
	bool Constant;

	int iValue; // Interger value
	float fValue; // Float value
	char cValue; // Character value
	
	int stackPos;
};

/*
Discontinued class, will be deleted soon when the parse tree will be finished. 
*/
class Statement
{
public:
	Statement ();

	int Type; // Look up the codes in Documentation/Parsing.md, it's there and it's pretty. - Binkiklou
	int Identifier; // Should I call id ? Identify in the vector of either Variable or Function depending on the type

	bool Variable;
	bool Function;
	bool Value;

	std::vector<std::string> Args; // Pretty Universal
};

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
	void AddChild(int,Node); // Adds a node to another node

	Node GetNode(int); // Returns the node at a specific positon

	Node FindNode(std::string); // Find a node in all the tree, with given Lexeme
	Node FindChild(Node*,std::string); // Find a child of node with given lexeme
};


// Thise shouldn't be called scope but it is, can't find a name
// basicallly it's either the positions of various symbols or
// thoses of conditions
class Scope
{
public:
	Scope ();

	void Set (int, std::vector<Statement>*); // Pretty much parses it

	bool hasArg;

	int ArgStart; // Position where the parenthesis opens
	int ArgStop; // Position where the parenthesis closes
	int ScopeStart; // Position where the brackets start
	int ScopeStop; // Position where the brackets stop
};

/*
This is pretty important, for function.
*/
class Function
{
public:
	std::string Name;

	int Type; // 0 - int, 1 - float, 2 - character
	bool Defined;
	bool Entry;

	Scope ThisScope; // That's like a bad but ok name

	std::string Output;
//	int OutId; // Position in parsed's fout
};

/*
Most important class for the compiler. Everything is happening here iet's a
pretty way to do stuff.
*/
class Parsed
{
public: // Ok so you can see that the lower you go, the later the compiler is gonna work on it
	Parsed(std::string);

	void Tokenize ();
	void ParseVar (); // Pretty self explanatry wait fuck..
	void ParseFunc ();

	std::string CallFunc (Statement* stat);
	Variable FindVar(std::string); // Return a variable with given name
	std::string ASMStat (Statement*); // Makes a statement inside a stack into assembly code

	void MakeAssembly ();

	Tree ParseTree;

	std::vector<std::string> Unclassified; // What if it's declassified O_o
	std::vector<Statement> Classified;

	std::vector<Variable> VariableList;
	std::vector<Function> FunctionList;
	std::vector<Value> ValueList;

	int EntryPos;

	std::string Text; // section .text
	std::string BSS; // section .bss
	std::string Data; // section .data

	std::string Output;
};