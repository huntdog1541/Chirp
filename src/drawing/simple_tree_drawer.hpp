#pragma once
#include "tree_drawer.hpp"

class simple_tree_drawer : public tree_drawer{
public:
    simple_tree_drawer(const std::string& fname):tree_drawer(fname){}
    void draw(tree_interface& t) const override{
        df_draw(0, t.getRoot());
    }

private:
    void df_draw(const int indent, node_interface& n) const {
        for(int i = 1; i < indent; ++i){ std::cout <<"\t│"; }
        if(indent > 0){ std::cout << "────"; }
        std::cout << n.value << "\n";
        for(auto& child: n.getAllChilds()){
            df_draw(indent+1, *child);
        }
    }

};

