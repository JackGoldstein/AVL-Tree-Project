//
// Created by Jack on 10/2/2023.
//

#ifndef PROJECT1_NODE_H
#define PROJECT1_NODE_H
#include <string>
using namespace std;


class Node
{
    int height = 0;

public:
    int UFID = 0;
    string name;

    Node* left = nullptr;
    Node* right;

    //Default constructor
    Node(int id, string _name);

    int getHeight();
    void setHeight(int _height);


};
#endif //PROJECT1_NODE_H
