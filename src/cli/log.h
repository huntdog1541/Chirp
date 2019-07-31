#include <iostream>
#include <string>
namespace cli
{

    enum class log_level{ log, warning, error, success, debug };
    enum class output_col{ black, white, red, yellow, green, blue };

    /*
    Logs a message to the console. Uses 3 different level of status,
    
    LOG: Writes message in default color
    WARNING: Writes message in yellow
    ERROR: Writes message in red
    */
    void log(const log_level,const std::string&);
    std::string write_color(const output_col, const std::string&);
    void verbose_enable();
}
