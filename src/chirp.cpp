#include "chirp.h"

#include "cli/log.h"

bool debug_mode;
int main(int argc, char* argv[])
{
    debug_mode = true;
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