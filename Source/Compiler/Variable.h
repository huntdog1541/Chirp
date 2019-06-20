#pragma once

#include "Analyser/Parser.h"

namespace Variable
{
	void Register(int,Environement*);
	std::string Assign(int,Environement*);
}