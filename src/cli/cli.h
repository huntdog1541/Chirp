#include <iostream>
#include <string>
#include <vector>

namespace cli
{
    /*
    Parses the command
    */
    void parse_Command(const std::vector<std::string>&);
    /*
    Runs the command
    */
    void run_Command(const std::string&, const std::string&);
    bool draw_tree();
}
