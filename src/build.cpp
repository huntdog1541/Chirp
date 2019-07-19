#include "build.h"
#include "preprocessor.h"
#include "log.h"
#include "parser/parser.h"

#include <iostream>

void compile(std::string source)
{
    std::vector<std::string> prep = preprocess(source);

    cli::log(SUCCESS,"Nothing wen't wrong, and this is all it can do right now");

    node root("root");
    node a("some_node");
    node b("another_node");
    node c("some_child_node");
    
    root.addChild(&a);
    root.addChild(&b);

    parser.parseTree.setRoot(&root);

    std::vector<std::string> result = parser.parseTree.traverse();

    for(std::string value : result)
    {
        std::cout<<value<<std::endl;
    }
}

void build()
{

}