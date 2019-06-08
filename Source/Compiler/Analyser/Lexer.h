#pragma once

#include <string>

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
#define GATE_SCOPE_TOKEN 10
#define GATE_ARG_TOKEN 11

#define OBJECT_IDENTIFIER_TOKEN 8

/*
class Token
{
public:
	int Identifier; // Is defined somewhere
	std::string lexeme;
};
*/