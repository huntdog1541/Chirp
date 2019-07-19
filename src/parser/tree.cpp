/*
This does tree related stuff, like a tiny library inside the main source code.
*/

#include "tree.h"

tree::tree()
{

}

// geeksforgeek generic  tree level-order traversal tutorial really helped for this
std::vector<std::string> tree::traverse()
{
    node* root = this->root;

    std::vector<node *> queue; // traversal queue
    std::vector<std::string> order; // order in which has been traversed
    queue.push_back(root);

    while(!queue.empty())
    {
        int n = queue.size();
        while(n > 0)
        {
            // Dequeue item
            node* p = queue.front();
            queue.pop_back();

            order.push_back(p->value);

            // Queue all childs of dequeued item
            for(auto& c : p->child)
            {
                queue.push_back(c);
            }
            n--;
        }
    }
    return order;
}