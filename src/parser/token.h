/*
This file is used to declare the token class
*/

#include <string>

// I'm pretty sure I only named it "token_name" to make munchii angry
enum token_name {
    identifier, keyword, separator, literal
};

class token
{
    public:
    // Constructor without arguments for a token
    token();
    // Constructor with arguments for a token
    token(token_name,std::string);

    token_name name; // The name/type of the token
    std::string value; // Most likely the original string
};