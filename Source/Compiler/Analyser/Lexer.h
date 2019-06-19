#pragma once

#include <string>

// Token macro's below
// Note: They may or may not be in order, but they are grouped
#define TREE_START_TOKEN 0
#define TREE_UNDEFINED_TOKEN 2

#define VAR_TOKEN 3 // First node of any variable related structure
#define VAR_DEF_TOKEN 4
#define VAR_DEC_TOKEN 5	
#define VAR_ASSIGN_OP_TOKEN 9 // The = symbol
#define VAR_CONFIRM_TOKEN 12 // The : in int: a...

#define VALUE_INTERGER_TOKEN 9

#define GATE_STRING_TOKEN 7
#define GATE_SCOPE_TOKEN 10
#define GATE_ARG_TOKEN 11

#define OBJECT_ID_TOKEN 8
#define OBJECT_TYPE_TOKEN 6 // Cast Type

#define KEYWORD_UNKNOWN_TOKEN 1 // When stuff is unknown, then spooky
#define KEYWORD_ENTRY_TOKEN 13
#define KEYWORD_CONST_TOKEN  14 // const keyword
#define KEYWORD_INNER_TOKEN 15

#define UNPARSED_TOKEN 16

class Token
{
public:
	int Identifier; // Is defined somewhere
	std::string Lexeme;
};
