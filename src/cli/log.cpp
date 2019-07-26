#include "log.h"

namespace cli
{
    enum class output_col{ black, white, red, yellow, green, blue };
        
    std::string write_color(const output_col,const std::string&);

    static bool debug_mode = false;

    void verbose_enable(){
        debug_mode = true;
    }
    
    std::string write_color(const output_col color, const std::string& text)
    {
        std::string result = "\u001b[";
        
        switch(color){
            case output_col::black: result += "30m";    break;
            case output_col::white: result += "37m";    break;
            case output_col::red: result += "31m";      break;
            case output_col::yellow: result += "33m";   break;
            case output_col::green: result += "32m";    break;
            case output_col::blue: result += "34m";     break;
        }

        result += text;
        result += " \u001b[0m"; // Reset code
        return result;
    }
    
    void log(const log_level lvl, const std::string& message)
    {
        switch(lvl){
            case log_level::log:
                std::cout << "LOG: " << message << "\n";
                break;
            case log_level::warning:
                std::cout << write_color(output_col::yellow, "WARNING: ") << message << "\n";
                break;
            case log_level::error:
                std::cout << write_color(output_col::red ,"ERROR: ") << message << "\n";
                exit(1);
                break;
            case log_level::success:
                std::cout << write_color(output_col::green, "SUCCESS: ") << message << "\n";
                break;
            case log_level::debug:
                if(debug_mode){
                    std::cout << write_color(output_col::blue, "DEBUG: ") << message << "\n";
                }
                break;
        }        
    }
}
