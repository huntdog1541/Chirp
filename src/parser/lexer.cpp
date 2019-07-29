/*
Phase 1-2: Lexing

This should take the ouput of the preprocessor, and assign tokens to each word & symbols.
*/
#include "lexer.h"
#include "../cli/log.h"

#include <iostream>
#include <cctype>

#define enumString(name) # name

namespace lexer
{
    bool read_chars(std::string::const_iterator &it, std::string::const_iterator end, const std::string &toread)
    {
        std::string::const_iterator loop_it = it;
        size_t idx = 0, len = toread.length();
        while(idx < len) {
            if(loop_it == end || toread[idx] != *loop_it) {
                return false;
            }
            loop_it++;
            idx++;
        }
        // Success, update it to new position in string
        it = loop_it;
        return true;
    }

    token read_inline_asm(std::string::const_iterator &it, std::string::const_iterator end)
    {
        token tkn(token_name::error, "");
        std::string buf;
        std::string::const_iterator i = it;

        if(!read_chars(it, end, "@asm")) {
            tkn.value.push_back(*it++);
            return tkn;
        }

        while(true) {
            if(it == end) {
                tkn.value.erase();
                return tkn;
            }
            if(*it == '@') {
                if(read_chars(it, end, "@end")) {
                    break;
                }
            }
            tkn.value.push_back(*it++);
        }
        tkn.name = token_name::asm_code;
        return tkn;
    }

    token read_quoted_literal(std::string::const_iterator &it, std::string::const_iterator end, char variant = '\'')
    {
        token tkn(token_name::error, "");

        tkn.value.push_back(*it);
        if(*it++ != variant) {
            return tkn;
        }
        tkn.name = token_name::litteral;
        while(*it != variant) {
            tkn.value.push_back(*it++);
        }
        tkn.value.push_back(*it++);
        return tkn;
    }


    token tokenize_punct(std::string::const_iterator &it, std::string::const_iterator end)
    {
        token tkn(token_name::error, "");
        switch(*it) {
            case '+':
            case '-':
            case '*':
            case '/':
                tkn.name = token_name::math_op;
                tkn.value.push_back(*it++);
                break;
            case '{':
                tkn.name = token_name::lbracket;
                tkn.value.push_back(*it++);
                break;
            case '}':
                tkn.name = token_name::rbracket;
                tkn.value.push_back(*it++);
                break;
            case '(':
                tkn.name = token_name::lparen;
                tkn.value.push_back(*it++);
                break;
            case ')':
                tkn.name = token_name::rparen;
                tkn.value.push_back(*it++);
                break;
            case ',':
                tkn.name = token_name::comma;
                tkn.value.push_back(*it++);
                break;
            case ':':
                tkn.name = token_name::confirm;
                tkn.value.push_back(*it++);
                break;
            case '=':
                tkn.name = token_name::assign_op;
                tkn.value.push_back(*it++);
                if(it != end && *it == '=') {
                    tkn.name = token_name::equal_op;
                    tkn.value.push_back(*it++);
                }
                break;
            case '@':
                tkn = read_inline_asm(it, end);
                break;
            case '\'':
            case '"':
                tkn = read_quoted_literal(it, end, *it);
            default:
                tkn.value.push_back(*it++);
                break;
        }
        return tkn;
    }

    token tokenize_number(std::string::const_iterator &it, std::string::const_iterator end)
    {
        token tkn(token_name::litteral, "");
        while(std::isdigit(static_cast<unsigned char> (*it))) {
            tkn.value.push_back(*it++);
        }
        return tkn;
    }

    token tokenize_ident_keyword(std::string::const_iterator &it, std::string::const_iterator end)
    {
        token tkn(token_name::error, "");
        if(std::isalpha(static_cast<unsigned char> (*it))) {
            tkn.name = token_name::identifier;
            tkn.value.push_back(*it++);
            while(std::isalnum(static_cast<unsigned char> (*it)) || *it == '_') {
                tkn.value.push_back(*it++);
            }
            if(tkn.value == "int" || tkn.value == "char" || tkn.value == "bool") {
                tkn.name = token_name::data_type;
            } else if(tkn.value == "entry") {
                tkn.name = token_name::entry;
            } else if(tkn.value == "if") {
                tkn.name = token_name::if_keyword;
            } else if(tkn.value == "else") {
                tkn.name = token_name::else_keyword;
            } else if(tkn.value == "or") {
                tkn.name = token_name::or_op;
            } else if(tkn.value == "and") {
                tkn.name = token_name::and_op;
            } else if(tkn.value == "true" || tkn.value == "false") {
                tkn.name = token_name::litteral;
            }
        }
        return tkn;
    }

    std::vector<token> tokenize(const std::string &source)
    {
        std::vector<token> tokens;
        size_t pos = 0;
        std::string::const_iterator it = source.begin();
        while(it != source.end()) {
            char c = static_cast<unsigned char> (*it);
            if(std::isspace(c)) {
                it++;
                continue;
            } else if(std::isalpha(c) || c == '_') {
                tokens.push_back(tokenize_ident_keyword(it, source.end()));
            } else if(std::isdigit(c)) {
                tokens.push_back(tokenize_number(it, source.end()));
            } else if(std::ispunct(c)) {
                // token tkn = tokenize_punct(it, source.end());
                // if(tkn.name == token_name::asm_code) {
                //     // tokens.push_back(token(token_name::asm_prep, "@asm"));
                //     tokens.push_back(tkn);
                //     // tokens.push_back(token(token_name::end_prep, "@end"));
                // } else {
                //     tokens.push_back(tkn);
                // }
                tokens.push_back(tokenize_punct(it, source.end()));
            } else {
                tokens.push_back(token(token_name::error, std::string(1, *it++)));
            }
        }

        token eos(token_name::end_of_string,"");
        tokens.push_back(eos);
        return tokens;
    }
}
