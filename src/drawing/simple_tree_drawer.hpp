#pragma once
#include "tree_drawer.hpp"

class simple_tree_drawer : public tree_drawer{
public:
    simple_tree_drawer(const std::string& fname):tree_drawer(fname){}
    void draw(tree_interface& t) const override{

    }

};

