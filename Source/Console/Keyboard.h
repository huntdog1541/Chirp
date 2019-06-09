#pragma once

#ifdef _WIN32
#include <conio.h>
#endif

#ifdef __linux__
#include <unistd.h>
#include <termios.h>
#endif

namespace Key
{
	char Get();
}