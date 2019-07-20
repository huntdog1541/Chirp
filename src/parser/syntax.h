#pragma once

#include "lexer.h"
#include "tree.h"
#include "parser.h"

namespace syntax
{
    void parse(parser*,tree*);
}