#include <iostream>
#include <iomanip>
#include <regex>
#include "AVLTree.h"
#include "Node.h"
using namespace std;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

bool validWord(const string& word) {
    return regex_match(word, std::regex("^[A-Za-z ]+$"));
}

bool validID(const string& ID)
{
    return ID.find_first_not_of("0123456789") == std::string::npos;
}


int main()
{
    AVLTree tree;
    Node* root = nullptr;
    int commandCount = 0;

    //Welcome Message
    cout << "This is the main interface for Gator AVL! Use the menu below to "
            "see the available functions." << endl;
    cout << "" << endl;


//Main Menu
    cout << "1.) insert" << endl;
    cout << "2.) remove" << endl;
    cout << "3.) search" << endl;
    cout << "4.) printInorder" << endl;
    cout << "5.) printPreorder" << endl;
    cout << "6.) printPostorder" << endl;
    cout << "7.) printLevelCount" << endl;
    cout << "8.) removeInorder" << endl;
    cout << "" << endl;


//User input for total amount of commands
    cout << "Please enter a value for the total amount of commands you will use, then input commands."
            " Be sure that your command exactly matches the ones listed in the menu! " << endl;
    cin >> commandCount;

    for (int i = 0; i < commandCount; i++)
    {
        //user input for command operations
        string command;
        cin >> command;

        //inserts a new node into the AVL tree
        if (command == "insert") {
            cout << "Name Format: Case sensitive, only characters are valid." << endl;
            cout << "ID Format: Only numbers, must be 8 digits no more no less." << endl;
            cout << "Enter the name and UFID of student. Please follow input format directly." << endl;

            string name;
            cin >> quoted(name);

            //check if name is valid
            if (validWord(name)) {
                //get UFID info
                string temp;
                cin >> temp;

                //check if the length and the values of the ID are valid
                if (temp.length() == 8 && validID(temp)) {
                    //convert temp to int and insert the two values
                    int UFID = stoi(temp);
                    root = tree.insert(root,UFID,name);
                } else {
                    //the entered UFID was either too short or too long/had unexpected values
                    cout << "unsuccessful" << endl;
                }
            } else {
                //the entered name had unexpected values
                cout << "unsuccessful" << endl;
                cin.clear();
                fflush(stdin);
            }

        //removes the node matching the UFID taken from user input
        } else if (command == "remove") {

            cout << "Please enter the UFID of the student you would like to remove." << endl;

            string temp;
            cin >> temp;

            if (temp.length() == 8 && validID(temp)) {
                //convert temp to int and insert the two values
                int UFID = stoi(temp);
                root = tree.remove(root,UFID);
            } else {
                //the entered UFID was either too short or too long/had unexpected values
                cout << "unsuccessful" << endl;
                cin.clear();
                fflush(stdin);
            }

        //searches and returns the node matching UFID taken from user input
        } else if (command == "search") {

            cout << "Enter either the name (case sensitive) or UFID of the student you would like to display." << endl;
            string temp;
            cin >> quoted(temp);

            //searching for a name
            if (validWord(temp)) {
                tree.searchName(root,temp);
                if (tree.getSearchAmt() == 0) {
                    cout << "unsuccessful" << endl;
                }
                tree.setSearchAmt(0);
            //searching for an id
            } else if (validID(temp) && temp.length() == 8) {
                int UFID = stoi(temp);
                tree.searchID(root,UFID);
            } else {
                //neither a valid name nor id was entered
                cout << "unsuccessful" << endl;
            }

        //prints the whole tree using in order traversal
        } else if (command == "printInorder") {

            vector<string> outcome;
            outcome = tree.inOrder(root,outcome);
            for(int j = 0; j < outcome.size(); j++) {\
                if(j == outcome.size()-1) {
                    cout << outcome[j];
                } else {
                    cout << outcome[j] << ", ";
                }
            }
            cout << endl;

        //prints the whole tree using pre-order traversal
        } else if (command == "printPreorder") {

            vector<string> outcome;
            outcome = tree.preOrder(root,outcome);
            for(int j = 0; j < outcome.size(); j++) {
                if(j == outcome.size()-1) {
                    cout << outcome[j];
                } else {
                    cout << outcome[j] << ", ";
                }
            }
            cout << endl;

        //prints the whole tree using post-order traversal
        } else if (command == "printPostorder") {

            vector<string> outcome;
            outcome = tree.postOrder(root,outcome);
            for(int j = 0; j < outcome.size(); j++) {
                if(j == outcome.size()-1) {
                    cout << outcome[j];
                } else {
                    cout << outcome[j] << ", ";
                }
            }
            cout << endl;

        //prints the # of levels in the tree
        } else if (command == "printLevelCount") {

            if (tree.getNodeCount() == 0) {
                cout << "0" << endl;
            } else {
                cout << root->getHeight() << endl;
            }

        //removes the node at the index "n" of in order traversal taken from user input
        } else if (command == "removeInorder") {

            cout << "Input the index of the node you wish to remove." << endl;

            bool validIndex = false;
            string index;
            cin >> index;
            int n = 0;

            if (validID(index)) {
                n = stoi(index);
                validIndex = true;
            }

            if (n+1 > tree.getNodeCount() || validIndex == false) {
                cout << "unsuccessful" << endl;
            } else {
                root = tree.removeInorder(root,n);
            }

        //the user input an invalid command
        } else {

            cout << "unsuccessful" << endl;
            cin.clear();
            fflush(stdin);

        }
    }
	return 0;
}




