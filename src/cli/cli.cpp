#include "cli.h"
#include "log.h"
#include "build.h"

#include <fstream>

/*
Open the file and returns the content.. duh
*/
std::string openFile(const std::string& filename)
{
    std::ifstream reader(filename);

    char letter;
    std::string file;

    if(!reader)
    {
        cli::log(ERROR,"Couldn't open file " + filename);
        exit(0);
        return "";
    }

    for(int i = 0; ! reader.eof(); i++)
    {
        reader.get(letter);
        file.append(1,letter);
    }

    reader.close();

    file.pop_back(); // this is a lazy but "efficient" fix

    return file;
}

namespace cli
{
    void parse_Command(const std::vector<std::string>& args)
    {
        //std::cout<<"I hope dis works"<<std::endl;
        std::string inputFile;
        std::string outputFile;

        int pos = 0;
        
        for(std::string word : args)
        {
            if(word == "-o")
            {
                // outputFile = word.at(pos + 1);
            }
            else
            {
                if(pos == 0)
                {
                    inputFile = word;
                }
            }
            pos++;
        }

        run_Command(inputFile,outputFile);
    }
    void run_Command(const std::string& inputArgs, const std::string& outputArgs)
    {
        std::string input;
        std::string output;

        bool error = false;

        if(inputArgs == "")
        {
            error = true;
            log(ERROR, "No input file specified.");
            exit(0);
        }
        else
        {
            input = inputArgs;
        }

        if(outputArgs == "")
        {
            log(WARNING,"No output file specified, using default.");

            output = input;

            output.pop_back();
            output.pop_back();

            output += 'o';
        }
        else
        {
            output = outputArgs;
        }

        if(error != true)
        {
            compile(openFile(input));
        }
    }
}
