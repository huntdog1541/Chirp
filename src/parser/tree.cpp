/*
This does tree related stuff, like a tiny library inside the main source code.
*/

#include "tree.h"
#include "../cli/log.h"

#include <queue>
#include <sstream>
#include <algorithm> // fixed it ;)

// === NODE ===

node::node(std::string value)
{
    this->value = value;
}

void node::addChild(std::unique_ptr<node> child)
{
    this->childs.push_back(std::move(child));
    // std::cout<< __PRETTY_FUNCTION__ << " Added " << childs.back()->value << " to " << value << "\n";
}

int node::getChildSize()
{
    return this->childs.size();
}

node& node::getChild(int pos)
{
    return *childs.at(pos);
}

const node& node::operator[](const std::string& node_name) const {
    const auto match = std::find_if(childs.begin(), childs.end(), [node_name](const std::unique_ptr<node>& n) { return n->value == node_name; } );
    if(childs.end() == match){
        std::stringstream ss;
        ss << node_name << " not found in " << value;
        throw std::runtime_error(ss.str());
    }
    return **match;
}

node& node::operator[](const std::string& node_name) {
    const auto match = std::find_if(childs.begin(), childs.end(), [node_name](const std::unique_ptr<node>& n) { return n->value == node_name; } );
    if(childs.end() == match){
        std::stringstream ss;
        ss << node_name << " not found in " << value;
        throw std::runtime_error(ss.str());
    }
    return **match;
}

// === TREE === 

tree::tree()
{
    // does tree stuff
}

// geeksforgeek generic tree level-order traversal tutorial really helped for this
std::vector<std::string> tree::traverse()
{
    std::vector<std::string> treeResult;
    if(this->root == NULL)
    {
        return treeResult; // No segfault eheh
    }

    std::queue<node*> q;
    q.push(root.get());

    while(!q.empty())
    {

        auto* p = q.front();
        
        // std::cout << __PRETTY_FUNCTION__ << " Traversing " << p->value << "\n"; 
        
        q.pop();

        try
        {
            treeResult.push_back(p->value);
            cli::log(LOG,"Succesfully pushed value: " + p->value);
        }
        catch(...)
        {
            cli::log(WARNING,"Error while adding value to traversal");
        }
        //std::cout<<p->value<<std::endl;

        // Range-based loop gave segfaults
        for(int i = 0; i < p->getChildSize(); i++){
            q.push(&p->getChild(i));
        }
    }
    return treeResult;
}

void tree::setRoot(std::unique_ptr<node> newRoot)
{
    this->root = std::move(newRoot);
}

node& tree::getRoot()
{
    return *this->root;
}
