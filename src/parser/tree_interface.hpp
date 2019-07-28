#pragma once

#include <vector>
#include <string>
#include <memory>

class node_interface
{
public:    
    virtual ~node_interface() = default;
    virtual void addChild(std::unique_ptr<node_interface>) = 0;
    virtual int getChildSize() = 0;
    virtual node_interface& getChild(int) = 0;
    virtual node_interface& getChild(std::string) = 0;
    virtual const node_interface& operator[](const std::string& node_name) const = 0;
    virtual node_interface& operator[](const std::string& node_name) = 0;
    virtual bool hasChild(int) = 0;
    virtual bool hasChild(std::string) = 0;
    virtual std::vector<std::unique_ptr<node_interface>>* getAllChilds() = 0;
    std::string value;
protected:
    std::vector<std::unique_ptr<node_interface>> childs;
};

class tree_interface
{
public:
    virtual ~tree_interface() = default;
    virtual void setRoot(std::unique_ptr<node_interface>) = 0;
    virtual node_interface& getRoot() = 0;
protected:
    std::unique_ptr<node_interface> root;
};
