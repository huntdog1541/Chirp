/*
Phase 1: Preprocessing

This file is tasked with making the strings into vectors readable by the lexer & other parts of the compiler. It also executes
preprocessor commands.
*/
#include "preprocessor.h"

std::vector<std::string> preprocess(std::string source)
{
    std::vector<std::string> processed;

    std::string word;
    int pos = 0;

    for(char& c : source)
    {
        pos++;
        if(isspace(c) || c == '\n')
        {
            if(word.compare("") != 0)
            {
                processed.push_back(word);
                word.erase();
            }
        }
        else
        {
            if(c == '=' || c == ':' || c == '(' || c == ')' || c == '{' || c == '}')
            {
                if(word.compare("") != 0)
                {
                    processed.push_back(word);
                    word.clear(); // no idea why it isn't "erase()", but this works
                }
                word.append(1,c);
                processed.push_back(word);
                word.clear();
            }
            else
            {
                word.append(1,c);
            }

            if(pos >= source.length())
            {
                processed.push_back(word);
                word.erase();
            }
        }
    }
    return processed;
}