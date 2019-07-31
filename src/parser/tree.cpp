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

void node::addChild(std::unique_ptr<node_interface> child)
{
    this->childs.push_back(std::move(child));
}

int node::getChildSize()
{
    return this->childs.size();
}

node_interface& node::getChild(int pos)
{
    return *childs.at(pos);
}

node_interface& node::getChild(std::string val)
{
    const auto match = std::find_if(childs.begin(), childs.end(), [val](const std::unique_ptr<node_interface>& n) { return n->value == val; } );
    if(childs.end() == match){
        std::stringstream ss;
        ss << val << " not found in " << value;
        throw std::runtime_error(ss.str());
    }
    return **match;
}

const node_interface& node::operator[](const std::string& node_name) const {
    const auto match = std::find_if(childs.begin(), childs.end(), [node_name](const std::unique_ptr<node_interface>& n) { return n->value == node_name; } );
    if(childs.end() == match){
        std::stringstream ss;
        ss << node_name << " not found in " << value;
        throw std::runtime_error(ss.str());
    }
    return **match;
}

node_interface& node::operator[](const std::string& node_name) {
    const auto match = std::find_if(childs.begin(), childs.end(), [node_name](const std::unique_ptr<node_interface>& n) { return n->value == node_name; } );
    if(childs.end() == match){
        std::stringstream ss;
        ss << node_name << " not found in " << value;
        throw std::runtime_error(ss.str());
    }
    return **match;
}

bool node::hasChild(int p)
{
    bool res = false;

    if(p > childs.size())
    {
        res = false;
    }
    else
    {
        res = true;
    }

    return res;
}

bool node::hasChild(std::string v)
{
    bool res = false;

    return res;
}

std::vector<std::unique_ptr<node_interface>>& node::getAllChilds()
{
    return this->childs;
}
const std::vector<std::unique_ptr<node_interface>>& node::getAllChilds() const
{
    return this->childs;
}
// === TREE === 

tree::tree()
{
    // does tree stuff
}

// geeksforgeek generic tree level-order traversal tutorial really helped for this
std::vector<node_interface*> tree::traverse()
{
    cli::log(cli::log_level::debug,"-=- TREE TRAVERSAL BEGIN -=-");
    std::vector<node_interface*> path;

    if(this->root == NULL)
    {
        return path;
    }

    std::queue<node_interface*> q;
    q.push(root.get());

    while(!q.empty())
    {

        auto* p = q.front();
        
        // std::cout << __PRETTY_FUNCTION__ << " Traversing " << p->value << "\n"; 
        
        q.pop();

        try{
            path.push_back(p);
            cli::log(cli::log_level::debug, "Succesfully pushed value: " + p->value);
        }
        catch(...)
        {
            cli::log(cli::log_level::warning, "Error while adding value to traversal");
        }

        // Range-based loop gave segfaults
        for(int i = 0; i < p->getChildSize(); i++){
            q.push(&p->getChild(i));
        }
    }
    cli::log(cli::log_level::debug,"-=- TREE TRAVERSAL END -=-");
    return path;
}

void tree::setRoot(std::unique_ptr<node_interface> newRoot)
{
    this->root = std::move(newRoot);
}

node_interface& tree::getRoot()
{
    return *this->root;
}

const node_interface& tree::getRoot() const
{
    return *this->root;
}
