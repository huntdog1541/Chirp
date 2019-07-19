#include <vector>
#include <string>

class node
{
    public:
    // Default constructor
    node(std::string);

    // Adds a new child to current node
    void addChild(node*);

    // Returns the size of the Child vector
    int getChildSize();

    // Returns the child at given position
    node* getChild(int);

    // Node's value
    std::string value;
    private:
    std::vector<node*> childs;
};

class tree
{
    public:
    // Tree constructor
    tree();

    //Traverse the tree and returns the id in order of each nodes.
    std::vector<std::string> traverse();

    // Sets the root node
    void setRoot(node*);
    private:
    node* root;
};