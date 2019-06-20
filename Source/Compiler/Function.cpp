#include "Function.h"

#include <iostream>

namespace Function
{
	void GenOpen(Environement* env)
	{
		std::string Output = "push ebp \n mov ebp,esp \n";
		env->Text.append(Output);
	}
	void GenClose(Environement* env)
	{
		std::string Output = "mov esp,ebp \n pop ebp \n ret 0 \n";
		env->Text.append(Output);
	}
}