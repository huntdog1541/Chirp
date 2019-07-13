#include "Commands.h"
#include "Chirp.h"
#include "Parser.h"
#include "Syntax.h"
#include "Output.h"
#include "Build.h"
#include "Log/Log.h"
#include "Debug.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

#include "boost/program_options.hpp"

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
    void ShowVersion(std::ostream& os){
        os << "Chirp Verion " << Chirp::Version << "\n";
    }

	void Run(const int argc, char** argv)
	{
        namespace po = boost::program_options;

        const std::unordered_map<std::string, int> supportedArchitectures{
            {"x64", 64},
            {"x86", 32}
        };

        auto arch = std::string{};
        auto output = std::string{};
        auto input = std::string{};
            
        auto desc = po::options_description("Options");
        desc.add_options()
            ( "help,h", "Help Screen")
            ( "input,i", po::value<std::string>(&input), "Input File")
            ( "output,o", po::value<std::string>(&output)->default_value("exec.out"), "Output filename")
            ( "arch,a", po::value<std::string>(&arch)->default_value("x64"), "Architecture")
            ( "version", "Show chirp version")
            ( "debug-menu,d", "Show debug menu");

        auto vm = po::variables_map();
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    
        if(vm.count("version")){
            ShowVersion(std::cout);
            return;
        }

        if(vm.count("help")){
            ShowVersion(std::cout);
            std::cout << desc;
            return;
        }

        if(!vm.count("input")){
            std::cerr << "Must specify an input file\n";
            return;
        }

        auto e = Environement{};
        e.Architecture = supportedArchitectures.at(arch);
        e.InFile = input;
        e.OutFile = output;
        e.AltFile = output + ".asm";
        
        Object undefined; // To keep away from errors
        undefined.Name = "undefined";
        undefined.Id = "unefined";
        undefined.Size = 1;
        e.ObjectList.push_back(undefined);
        
        std::string FileData = Read (input);
        // Parsing
        Parser::Setup(FileData,e);
        Lexer::Tokenize (e);
        Syntax::MakeSyntax(e);
        Output::Generate(e);

        // Building
        Output::Write(e);
        Tools::Build (e.AltFile, e.OutFile,e.Architecture);

        // Debugging
        if (vm.count("debug-menu"))
        {
            Menu DebugUI;
            Debug::MakeMenu();
        }
	}
}
