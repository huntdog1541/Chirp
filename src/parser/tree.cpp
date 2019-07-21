/*
This does tree related stuff, like a tiny library inside the main source code.
*/

#include "tree.h"
#include "log.h"

#include <queue>
#include <iostream>

// === NODE ===

node::node(std::string value)
{
    this->value = value;
}

void node::addChild(node* child)
{
    this->childs.push_back(child);
    //std::cout<<this->childs.at(this->childs.size())->value<<std::endl;
}

int node::getChildSize()
{
    return this->childs.size();
}

node* node::getChild(int pos)
{
    return this->childs.at(pos);
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

    std::queue<node *> q;
    q.push(this->root);

    while(!q.empty())
    {
        int n = q.size();

        while(n > 0)
        {
            node* p = q.front();
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
            for(int i = 0; i < p->getChildSize(); i++)
                q.push(p->getChild(i));
            n--;
        }
    }
    return treeResult;
}

void tree::setRoot(node* newRoot)
{
    this->root = newRoot;
}

node* tree::getRoot()
{
    return this->root;
}
