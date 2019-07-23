#pragma once

#include <vector>
#include <string>

class node
{
    public:
    // Default constructor
    node(std::string);

    // Adds a new child to current node
    void addChild(std::unique_ptr<node>);

    // Returns the size of the Child vector
    int getChildSize();

    // Returns the child at given position
    node& getChild(int);

    const node& operator[](const std::string& node_name) const;
    
    node& operator[](const std::string& node_name);

    // Node's value
    std::string value;
    private:
    std::vector<std::unique_ptr<node>> childs;
};

class tree
{
    public:
    // Tree constructor
    tree();

    //Traverse the tree and returns the id in order of each nodes.
    std::vector<std::string> traverse();

    // Sets the root node
    void setRoot(std::unique_ptr<node>);

    // Returns the root node
    node& getRoot();
    private:
    std::unique_ptr<node> root;
};
