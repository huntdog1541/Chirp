#pragma once

#include "Parser.h"

namespace Output
{
	void Generate (Environment&);
	void Write (Environment&); // Writes inside a file the ouput of env
	std::string Reg (const std::string&,Environment&);
}
