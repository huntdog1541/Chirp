#pragma once

#include <string>
#include <vector>

#define INT_OBJECT 1
#define FLOAT_OBJECT 2
#define CHAR_OBJECT 3 
#define STRING_OBJECT 4

class Object // Not an object in the traditional sense
{
public:
	std::string Name; // Name, isn't unique
	std::string Id; // Identifier, there are some way to find it, is unique
	int Size; // Size, pretty usefull in the stack
	int Position; // Position in stack
	int Type; // Idk
	int DecScope; // Scope where it has been declared
	int NewScope; // New scope if it created one 
};

namespace Obj
{
	Object FindByName(std::string,std::vector<Object>); // Finds an object in vector by name, then returns the object
	Object FindById(std::string,std::vector<Object>);
}
