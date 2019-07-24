#include <iostream>
#include <string>
namespace cli
{

    enum class log_level{ log, warning, error, success, debug };
    /*
    Logs a message to the console. Uses 3 different level of status,
    
    LOG: Writes message in default color
    WARNING: Writes message in yellow
    ERROR: Writes message in red
    */
    void log(const log_level,const std::string&);
    
    void verbose_enable();
}
