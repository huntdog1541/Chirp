#pragma once
#include "tree_interface.hpp"


class node:public node_interface
{
    public:
    // Default constructor
    node(std::string);

    // Adds a new child to current node
    void addChild(std::unique_ptr<node_interface>) override;

    // Returns the size of the Child vector
    int getChildSize() override;

    // Returns the child at given position
    node_interface& getChild(int) override;

    // Returns child with given value
    node_interface& getChild(std::string) override;

    const node_interface& operator[](const std::string& node_name) const override;

    node_interface& operator[](const std::string& node_name) override;

    // Returns true if has child at given position
    bool hasChild(int) override;

    // Returns true if has child with given value
    bool hasChild(std::string) override;

    // Returns child vector
    std::vector<std::unique_ptr<node_interface>>& getAllChilds() override;

};

class tree : public tree_interface
{
    public:
    // Tree constructor
    tree();

    //Traverse the tree and returns the id in order of each nodes.
    std::vector<node_interface*> traverse();
    
    // Sets the root node
    void setRoot(std::unique_ptr<node_interface>) override;

    // Returns the root node
    node_interface& getRoot() override;
};
