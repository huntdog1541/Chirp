#include "chirp.h"

#include "cli/log.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> args;

   for(int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        args.push_back(arg);
        //std::cout<<arg<<std::endl;
    }

    cli::parse_Command(args);
    return 0;
}