#include "Commands.h"

#include "../Compiler/Analyser/Parser.h"
#include "../Compiler/Analyser/Syntax.h"
#include "../Compiler/Output.h"
#include "../Build.h"
#include "Log/Log.h"
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

		Data.pop_back();

		return Data;
	}
}

namespace Command
{
	void Run(std::vector<std::string> Args)
	{
		// Once the -i flag is declared, this is on.Until there is another flag
		bool IncludeFlag = false;
		bool OutputFlag = false;

		// Temporary
		bool In = false;
		bool Out = false;
		bool Arched = false; // Architecture
		bool DebugMenu = false;

		std::string InputFile;
		std::string OutputFile;
		std::string Architecture; // 32 = x86, 64 = x64
		int Arch;

		// Start
		// This code is litteraly one of the first lines of code, of the whole 
		// compiler. I am already 1-2 months in the project and I think I am
		// already 10x better because this is horrible. - Ya boi binkiklou
		for (const auto& Arg : Args)
		{
			if (Arg.compare("-i") == 0)
			{
				IncludeFlag = true;
				OutputFlag = false;
			}

			else if (Arg.compare("-o") == 0)
			{
				IncludeFlag = false;
				OutputFlag = true;
			}

			else if (Arg.compare("-debug_menu") == 0)
			{
				DebugMenu = true;
			}

			else if (Arg.compare("-arch") == 0)
			{
				Arched = true;
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
				else if (Arched == true)
				{
					Architecture = Arg;
				}
			}
		}
		//End

		bool Error = false;

		if (InputFile.empty())
		{
			std::cout << "Error, No input files are specified!" << std::endl;
			Error = true;
		}

		else
		{
			std::cout << "Input file is: " << InputFile << std::endl;
		}

		if (OutputFile.empty())
		{
			std::cout << "Error, No output file are specified!" << std::endl;
			Error = true;
		}

		else
		{
			std::cout << "Output file is: " << OutputFile << std::endl;
		}

		if (Architecture.empty())
		{
			Log::Warning("No architecture has been set, defaulted to x86 32 bit");
			Arch = 32;
		}
		else
		{
			if (Architecture.compare("x86") == 0)
			{
				Arch = 32;
			}
			else if (Architecture.compare("x64") == 0)
			{
				Arch = 64;
			}
			else
			{
				Log::Warning("Unrecognized architecture, defaulted to 32 bit");
				Arch = 32;
			}
		}

		if (Error == false) // Lets compile now
 		{
			// Ok we can finally get started on doing real stuff

			std::string FileData = Read (InputFile);
		//	std::string Asm = InputFile.append (".asm");

			// Setup
			Environement e;
			e.Architecture = Arch;
			e.InFile = InputFile;
			e.OutFile = OutputFile;
			e.AltFile = OutputFile.append(".asm");
			
			Object undefined; // To keep away from errors
			undefined.Name = "undefined";
			undefined.Id = "unefined";
			undefined.Size = 1;
			e.ObjectList.push_back(undefined);
			
			// Parsing
			Parser::Setup(FileData,e);
			Lexer::Tokenize (e);
			Syntax::MakeSyntax(e);
			Output::Generate(e);

			// Building
			Output::Write(e);
			Tools::Build (e.AltFile, e.OutFile,e.Architecture);

			// Debugging
			if (DebugMenu)
			{
				Menu DebugUI;
				Debug::MakeMenu();
		    }
		}
	}
}
