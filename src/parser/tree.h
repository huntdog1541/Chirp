#include <vector>
#include <string>

// I dont know if it's possible to make a class with an object of self-type, like this
struct node
{
    std::string value;
    std::vector<node*> child;
};

class tree
{
    public:
    tree();
    node* root;
    /*
    Traverse the tree and returns the id in order of each nodes.
    */
    std::vector<std::string> traverse();
};