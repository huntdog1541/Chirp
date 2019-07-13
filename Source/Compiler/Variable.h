#pragma once

#include "Parser.h"

namespace Variable
{
	void Register (int,Environment&); // Register the variable so it remembers
	std::string Operation (int, Environment&); // Return the asm to do an operation
	std::string Assign (int,Environment&);  // Assign a variable and return the asm
}
