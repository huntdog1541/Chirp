#include "chirp.h"

#include "log.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> args;

    for(int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        args.push_back(arg);
    }

    cli::parse_Command(args);

    cli::log(LOG,"This works");
    cli::log(WARNING,"This may not work");
    cli::log(ERROR, "This doesn't work at all");

    return 0;
}