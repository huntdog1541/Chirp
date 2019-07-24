#pragma once
#include "asm.h"
#include "ir.h"

namespace gen
{
    std::string make_asm(std::vector<ir::operation>);
}