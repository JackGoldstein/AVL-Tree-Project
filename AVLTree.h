//
// Created by Jack on 10/2/2023.
//
#ifndef PROJECT1_AVLTREE_H
#define PROJECT1_AVLTREE_H
#include "Node.h"
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class AVLTree
{

private:

    bool twoChild = false;
    int nodeCount = 0;
    int nameSearchAmt = 0;

public:

    //for use in other functions (O(1))
    int getNodeCount();

    //for the search name function, this is to allow the program to set the search amt back to zero after
    //the search amt is returned.  (O(1))
    void setSearchAmt(int val);

    //also for use in the search name function. Allows program to see whether any names were found
    //within the search function or not (and how many names found)  (O(1))
    int getSearchAmt();

    //checks the balance of an individual root, good for use within insert and delete function
    //because it will ignore null nodes (O(1))
    int checkBalance (Node* root);

    //returns the height of a passed in node, good for use in balance calculations because it will ignore any
    //null children of a node (O(1))
    int returnHeight (Node* root);

    //right rotation and the heights of the altered nodes are updated, (O(1))
    Node* rotateRight (Node* root);

    //left rotation and the heights of the altered nodes are updated, (O(1))
    Node* rotateLeft(Node* root);

    //inserts a new node into the tree if the ID is unique, (O(log(n))) worst case
    Node* insert(Node* root, int id, string name);

    //removes a node that matches id input, (O(log(n))) worst case
    Node* remove(Node* root, int id);

    //removes a node from a given index in the tree's in-order traversal, (O(n)) worst case
    Node* removeInorder (Node* root,int n);

    //pre-order traversal of the AVL tree, (O(n))
    vector<string> preOrder(Node* root,vector<string> outcome);

    //in-order traversal of the AVL tree, (O(n))
    vector<string> inOrder(Node* root,vector<string> outcome);

    //post-order traversal of the AVL tree, (O(n))
    vector<string> postOrder(Node* root,vector<string> outcome);

    //searches the tree for a matching ID, displays the name associated with the unique ID, (O(log(n))) worst case
    void searchID(Node* root, int id);

    //uses pre-order traversal to search tree for matching names, displays multiple id's if there are duplicate names,
    //(O(n)) worst case
    void searchName(Node* root, string name);
};
#endif //PROJECT1_AVLTREE_H