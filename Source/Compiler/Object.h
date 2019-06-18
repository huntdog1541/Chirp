#pragma once

#include <string>

#define INT_OBJECT 1
#define FLAOT_OBJECT 2
#define CHAR_OBJECT 3 
#define STRING_OBJECT 4

class Object
{
public:
	std::string Name;
	int Position; // Position in specific vector
	int Type; // 0 = Var, 1 = Func
	int DecScope;
	int NewScope;
};