#pragma once

#ifdef _WIN32
#include <conio.h>
#endif

#if defined __linux__ || defined __unix__ || defined __APPLE__
#include <unistd.h>
#include <termios.h>
#include <iostream>
#endif

namespace Key
{
	char Get();
}
