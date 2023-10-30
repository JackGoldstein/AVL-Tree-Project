#include <Node.h>

Node::Node(int id, std::string _name)
{
    UFID = id;
    name = _name;
    left = nullptr;
    right = nullptr;
    height = 1;
}

int Node::getHeight() {return height;}

void Node::setHeight(int _height) {height = _height;}