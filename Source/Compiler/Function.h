#pragma once

#include "Parser.h"

namespace Function
{
	void GenOpen (Environment&); // Generate the function opening
	void GenClose (Environment&); // Generate the function close
	void RegisterFunction (int, Environment&);
	std::string WriteFunction (int,Environment&);
	std::string CallFunction (int, Environment&);
}
