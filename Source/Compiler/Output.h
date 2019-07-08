#pragma once

#include "Parser.h"

namespace Output
{
	void Generate (Environement&);
	void Write (Environement&); // Writes inside a file the ouput of env
	std::string Reg (const std::string&,Environement&);
}
