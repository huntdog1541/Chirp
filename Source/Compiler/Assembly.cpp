#include "Assembly.h"
#include "Variable.h"

#include <fstream>
#include <iostream>

void Parsed::ReadTree()
{
    bool Bottom = false;

    Node ONode; // Old Node
    Node CNode; // Current Node
    Node NNode; // Next Node

    CNode = this->ParseTree.NodeList.at(this->ParseTree.StartPos);

    int ipos = 0; // Index Position, in parent
    int pos = 0; // Position, in child

 /*   while(!Bottom)
    {
        if(pos < CNode.ChildPos.size() - 1)
        {
            pos++;
            std::cout<<"Child"<<std::endl;
        }
        if(pos == CNode.ChildPos.size() - 1)
        {
            pos = 0;
            ipos++;
            ONode = CNode;
            NNode = this->ParseTree.NodeList.at(CNode.ChildPos.at(ipos));
            CNode = NNode;
        }
        if(ipos == ONode.ChildPos.size() - 1)
        {
            ipos = 0;
            ONode = CNode;
            NNode = this->ParseTree.NodeList.at(NNode.ParentPos);
        }
        // Code ?
    } */
}