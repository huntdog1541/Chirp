#pragma once

// This file is very important to link the different parts of the parser, basically
// it does some very basic analyisis of the tree then send when a statement is detected
// the data will be sent the variable,function,condition.. parser to do specific stuff
// then other data will be sent to the output

#include "Parser.h"

namespace Syntax
{
	// Will read the index, to parse the syntax and generate
	// assembly
	void ReadIndex(Environement*);
}