#include <AVLTree.h>

int AVLTree::getNodeCount() {return nodeCount;}

void AVLTree::setSearchAmt(int val) {nameSearchAmt = val;}

int AVLTree::getSearchAmt() {return nameSearchAmt;}

int AVLTree::checkBalance(Node *root)
{
    if (root == nullptr) {
        return 0;
    } else {
        //the balance for a given node is the difference of the left child's height minus the
        //right child's height
        return (returnHeight(root->left) - returnHeight(root->right));
    }
}

int AVLTree::returnHeight(Node *root)
{
    if (root == nullptr) {
        return 0;
    } else {
        return root->getHeight();
    }
}

Node *AVLTree::rotateRight(Node *root)
{
    Node* left = root->left;
    Node* leftRight = left->right;

    left->right = root;
    root->left = leftRight;

    root->setHeight(1+max(returnHeight(root->left), returnHeight(root->right)));
    left->setHeight(1+max(returnHeight(left->left), returnHeight(left->right)));

    return left;
}

Node *AVLTree::rotateLeft(Node *root)
{
    Node* right = root->right;
    Node* rightLeft = right->left;

    right->left = root;
    root->right = rightLeft;

    root->setHeight(1+max(returnHeight(root->left), returnHeight(root->right)));
    right->setHeight(1+max(returnHeight(right->left), returnHeight(right->right)));

    return right;
}

Node *AVLTree::insert(Node *root, int id, std::string name)
{
    if(root == nullptr) {
        //the first value added to the AVL tree
        Node* node = new Node(id,name);
        nodeCount++;
        cout << "successful" << endl;
        return(node);
    } else if (id > root->UFID) {
        //id is greater than root id, this will be added to the right of the tree
        root->right = insert(root->right,id,name);
    } else if (id < root->UFID) {
        //is is let than root id, this will be added to the left of the tree
        root->left = insert(root->left,id,name);
    } else {
        //the ID was equal to one of the ID's already in the tree, there can be no duplicate ID's
        cout << "unsuccessful" << endl;
        return root;
    }

    //update the height of the current root
    root->setHeight(1+max(returnHeight(root->left), returnHeight(root->right)));

    //check the balance
    int isBalanced = checkBalance(root);

    //case 1: nodes balance is +2 (right)
    if (isBalanced > 1)
    {
        //case 2: parent is +2, child is -1 (left-right)
        if(checkBalance(root->left) < 0)
        {
            root = rotateLeft(root->left);
        }
        return rotateRight(root);
        // case 3: nodes balance is -2 (left)
    } else if (isBalanced < -1)
    {
        // case 4: parents is -2, child is +1
        if(checkBalance(root->right) > 0)
        {
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }

    return root;
}

Node *AVLTree::remove(Node *root, int id)
{
    //base case, this means that the id was not found in the tree so there is nothing to be deleted
    if (root == nullptr) {
        if(twoChild) {
            twoChild = false;
        } else {
            cout << "unsuccessful" << endl;
        }
        return root;
    }

    //the id is in the left subtree
    if (id < root->UFID) {
        root->left = remove(root->left,id);
        //the id is in the right subtree
    } else if (id > root->UFID) {
        root->right = remove(root->right,id);
        //the id was found
    } else {
        cout << "successful" << endl;
        nodeCount--;

        //case 1: one left child
        if (root->right == nullptr && root->left != nullptr) {
            //replace the removed node with its left child
            Node *temp = root->left;
            *root = *temp;
            delete (temp);
            //case 2: one right child
        } else if (root->left == nullptr && root->right != nullptr) {
            //replace the removed node with its right child
            Node *temp = root->right;
            *root = *temp;
            delete (temp);
            //case 3: no children
        } else if (root->left == nullptr && root->right == nullptr) {
            //since there are no children we can just delete this node
            Node *temp = root;
            root = nullptr;
            delete (temp);
            //case 4: two children
        } else {
            //for this case we replace the removed node with the in order successor
            Node *successorParent = root;
            Node *successor = root->right;
            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            //right child of successor becomes left child of its parent
            if (successorParent != root) {
                successorParent->left = successor->right;

                //no successor so right child of successor becomes right child of its parent
            } else {
                successorParent->right = successor->right;
            }

            root->UFID = successor->UFID;
            root->name = successor->name;

            //helper bool to stop "unsuccessful" from printing twice
            twoChild = true;
            //deletes the successor
            root->right = remove(root->right,successor->UFID);

        }

    }

    //this checks if there was only one node and returns if true
    if(root == nullptr) {
        return root;
    }

    //same height updating/balancing as insert function
    root->setHeight(1+max(returnHeight(root->left), returnHeight(root->right)));

    int isBalanced = checkBalance(root);

    if (isBalanced > 1)
    {
        if(checkBalance(root->left) < 0)
        {
            root = rotateLeft(root->left);
        }
        return rotateRight(root);

    } else if (isBalanced < -1)
    {
        if(checkBalance(root->right) > 0)
        {
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }

    return root;
}

Node *AVLTree::removeInorder(Node *root, int n)
{
    stack<Node*> inOrder;
    Node* temp = root;

    //same process as the in-order traversal function
    while (temp != nullptr || inOrder.empty() == false) {
        while(temp != nullptr) {
            inOrder.push(temp);
            temp = temp->left;
        }
        temp = inOrder.top();
        inOrder.pop();
        //keeping track of the index
        n--;

        //once we have reached the given index we can use the remove function and return the root.
        if(n+1 == 0) {
            root = remove(root,temp->UFID);
            return root;
        }

        temp = temp->right;
    }

}

vector<string> AVLTree::preOrder(Node *root, vector<std::string> outcome)
{
    stack<Node*> preOrder;
    preOrder.push(root);

    //once the stack is empty that means we have traversed through all nodes
    while(preOrder.empty() == false && root != nullptr) {
        Node* temp = preOrder.top();
        //push the current node (top of stack) into the outcome vector
        outcome.push_back(temp->name);
        preOrder.pop();
        //push the right child into the stack
        if(temp->right != nullptr) {
            preOrder.push(temp->right);
        }
        //push the left child into the stack
        if(temp->left != nullptr) {
            preOrder.push(temp->left);
        }
    }
    return outcome;
}

vector<string> AVLTree::inOrder(Node *root, vector<std::string> outcome)
{
    stack<Node*> inOrder;
    Node* temp = root;


    while (temp != nullptr || inOrder.empty() == false) {
        //traverse as left as possible, add to stack
        while(temp != nullptr) {
            inOrder.push(temp);
            temp = temp->left;
        }
        //set current node and push to outcome vector
        temp = inOrder.top();
        inOrder.pop();
        outcome.push_back(temp->name);

        temp = temp->right;
    }
    return outcome;
}

vector<string> AVLTree::postOrder(Node *root, vector<std::string> outcome)
{
    stack<Node*> postOrder1;
    stack<Node*> postOrder2;

    postOrder1.push(root);
    Node* temp;

    //step 1 sets up the second stack with the correct post-order traversal
    while (postOrder1.empty() == false && root != nullptr) {
        temp = postOrder1.top();
        postOrder1.pop();
        postOrder2.push(temp);


        if(temp->left) {
            postOrder1.push(temp->left);
        }

        if(temp->right) {
            postOrder1.push(temp->right);
        }
    }

    //step 2 pushes stack two's contents into the outcome vector from top to bottom
    while (postOrder2.empty() == false) {
        temp = postOrder2.top();
        postOrder2.pop();
        outcome.push_back(temp->name);
    }

    return outcome;
}

void AVLTree::searchID(Node *root, int id)
{
    if (root != nullptr) {
        //a matching id was found
        if (id == root->UFID) {
            cout << root->name << endl;
            return;
            //id is in left subtree
        } else if (id < root->UFID) {
            searchID(root->left,id);
            //id is in right subtree
        } else if (id > root->UFID) {
            searchID(root->right, id);
        }
    } else {
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::searchName(Node *root, std::string name)
{
    if(root != nullptr) {
        searchName(root->left,name);
        if (name == root->name) {
            cout << root->UFID << endl;
            //this value is incremented to tell the program that a name has been found
            //for (successful/unsuccessful) print
            nameSearchAmt++;
        }
        searchName(root->right,name);
    }
}