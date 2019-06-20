#include "Output.h"
#include "../Console/Log/Error.h"

#include <fstream>

namespace Output
{
	void Generate(Environement* env)
	{

	}

	void Write(Environement* env)
	{
		std::ofstream Write(env->AltFile);

		if (!Write)
		{
			Log::Error::Custom("Couldn't write assembly output");
		}
		else
		{
			Write << env->Header.append(env->Text) << std::endl;
			Write.close();
			// Succes
		}
	}
}