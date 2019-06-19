#include "Commands.h"

#include "../Compiler/Analyser/Parser.h"
#include "../Compiler/Analyser/Syntax.h"
#include "../Build.h"
#include "Debug.h"

#include <iostream>
#include <fstream>

std::string Read (std::string File)
{
	char Char;
	std::string Data; 
	std::ifstream Read (File);

	if (!Read)
	{
		// Error while reading file
		return "";
	}

	else
	{
		for (int I = 0; ! Read.eof (); I++)
		{
			Read.get (Char);
			Data.append (1, Char);
		}

		return Data;
	}
}

namespace Command
{
	void Run (std::vector<std::string> Args)
	{
		// Once the -i flag is declared, this is on.Until there is another flag
		bool IncludeFlag = false;
		bool OutputFlag = false;

		// Temporary
		bool In = false;
		bool Out = false;
		bool DebugMenu = false;

		std::string InputFile;
		std::string OutputFile;

		// Start
		for (const auto& Arg : Args)
		{
			if (Arg.compare ("-i") == 0)
			{
				IncludeFlag = true;
				OutputFlag = false;
			}

			else if (Arg.compare ("-o") == 0)
			{
				IncludeFlag = false;
				OutputFlag = true;
			}

			else if (Arg.compare("-debug_menu") == 0)
			{
				DebugMenu = true;
			}

			else
			{
				if (IncludeFlag == true)
				{
					// Wait maybe you should have only one input, so the input is the main file
					// and include other stuff from there, but the code here is easy to make it run
					// multiple files.

					if (In == false)
					{
						InputFile = Arg;
						In = true;
					}
					else
					{
						// Temporary, should make&use Logger's error
						std::cout << "Error, cannot currently include more than one file" << std::endl;
					}
				}

				else if (OutputFlag == true)
				{
					// You shouldn't be able to have more than one input, i think.
					if (Out == false)
					{
						OutputFile = Arg;
						Out = true;
					}

					else
					{
						std::cout << "Error, cannot output to more than one file" << std::endl;
					}
				}
			}
		}
		//End

		bool Error = false;

		if (InputFile.empty ())
		{
			std::cout << "Error, No input files are specified!" << std::endl;
			Error = true;
		}

		else
		{
			std::cout << "Input file is: " << InputFile << std::endl;
		}

		if (OutputFile.empty ())
		{
			std::cout << "Error, No output file are specified!" << std::endl;
			Error = true;
		}

		else
		{
			std::cout << "Output file is: " << OutputFile << std::endl;
		}

		if (Error == false) // Lets compile now
 		{
			// Ok we can finally get started on doing real stuff

			std::string FileData = Read (InputFile);
			std::string Asm = InputFile.append (".asm");

			Parser p;
			p.Setup(FileData); // I'm really impressed this works
			p.Tokenize ();
			p.MakeTree();
			p.MakeIndex();
			Syntax::ReadIndex(&p);

			Tools::Build (Asm, OutputFile);

			if (DebugMenu)
			{
				Menu DebugUI;
				Debug::MakeMenu();
		    }
		}
	}
}
