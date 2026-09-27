
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;
// Node class
class Node
{
public: // No specification in the assignment to keep class vars private. Public is easier
    // Node structure consists of the data, height, and left and right connections
    int data;
    int height;
    Node *left;
    Node *right;

    // Nodes are made at leaf points, where height is 1, and no children
    Node(int data) : data(data), height(1), left(nullptr), right(nullptr) {};
};

class AVLTree
{
public:
    // Root
    Node *root;

    // default constructor
    AVLTree()
    {
        root = nullptr;
    }

    // Define wrapper for inOrder recursion.
    vector<int> inOrder(Node *root)
    {
        vector<int> inOrderResults;
        inOrderAdd(root, inOrderResults);
        return inOrderResults;
    }
    // Wrapper for preOrder recursion
    vector<int> preOrder(Node *root)
    {
        vector<int> preOrderResults;
        preOrderAdd(root, preOrderResults);
        return preOrderResults;
    }
    // Wrapper for postOrder recursion
    vector<int> postOrder(Node *root)
    {
        vector<int> postOrderResults;
        postOrderAdd(root, postOrderResults);
        return postOrderResults;
    }

    // Actual recursive inOrder. All traversal functions take in a
    // results vector by reference which is updated acordingly.
    void inOrderAdd(Node *root, vector<int> &results)
    {

        if (root == nullptr)
        {
            return;
        }
        // For in order. left->middle->right
        inOrderAdd(root->left, results);
        results.push_back(root->data);
        inOrderAdd(root->right, results);
    }

    void preOrderAdd(Node *root, vector<int> &results)
    {

        if (root == nullptr)
        {
            return;
        }
        // for pre order middle->left->right
        results.push_back(root->data);
        preOrderAdd(root->left, results);
        preOrderAdd(root->right, results);
    }

    void postOrderAdd(Node *root, vector<int> &results)
    {
        if (root == nullptr)
        {
            return;
        }
        // for post order left->right->middle
        postOrderAdd(root->left, results);
        postOrderAdd(root->right, results);
        results.push_back(root->data);
    }

    // function to get height of a node
    int getHeight(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        return root->height;
    }

    // Update height to be maximum height of children + 1.
    void updateHeight(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    }

    // Determines balance. Left is taken to be positive, right as negative similar to lecture notes
    int getBalance(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        return (getHeight(root->left) - getHeight(root->right));
    }

    Node *rotateLeft(Node *root)
    {
        // Left rotation sets left child as new root
        Node *newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;

        // Update height of root and new root. Root goes first as it is now the child.
        updateHeight(root);
        updateHeight(newRoot);

        return newRoot;
    }

    Node *rotateRight(Node *root)
    {
        // Right rotation sets right child as new root
        Node *newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;

        // Update Heights
        updateHeight(root);
        updateHeight(newRoot);
        return newRoot;
    }

    Node *Rotate(Node *root)
    {
        Node *newRoot;

        // RR Case
        if (getBalance(root) < -1 && getBalance(root->right) <= 0)
        { // Perform Left rotation
            newRoot = rotateLeft(root);
        }
        else if (getBalance(root) > 1 && getBalance(root->left) >= 0) // LL case
        {
            // Perform Right rotation
            newRoot = rotateRight(root);
        }
        else if (getBalance(root) < -1 && getBalance(root->right) > 0) // RL case
        {
            // Perform right rotation on right child
            root->right = rotateRight(root->right);
            // Peform left rotation on root
            newRoot = rotateLeft(root);
        }
        else if (getBalance(root) > 1 && getBalance(root->left) < 0) // LR case
        {
            // Perform left rotation on left child
            root->left = rotateLeft(root->left);
            // Perform right rotaton on root
            newRoot = rotateRight(root);
        }
        else
        { // No rotation needed case
            newRoot = root;
            // Update height though.
            updateHeight(root);
        }

        return newRoot;
    }

    Node *insert(Node *root, int key)
    {
        // If it reaches a vacant spot, create a new node
        if (root == nullptr)
        {
            return new Node(key);
        }

        // If key is less than, traverse left. New left child may be updated on the way up.
        if (key > root->data)
        {
            root->right = insert(root->right, key);
        }
        else if (key < root->data) // If key is larger than, traverse right side. Right child may also need to be updated.
        {
            root->left = insert(root->left, key);
        }
        else
        {
            // key already exists
            //  Do nothing
        }

        return Rotate(root); // Check and perform rotations if needed; returns new root automatically. Heights also updated therein
    }

    Node *find(Node *root, int key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (key > root->data)
        {
            return find(root->right, key);
        }
        else if (key < root->data)
        {
            return find(root->left, key);
        }
        else
        {
            return root;
        }
    }

    Node *deleteNode(Node *root, int key)
    {
        if (root == nullptr)
        {
            // Does not exist in tree
            return root;
        }

        if (key > root->data)
        {
            root->right = deleteNode(root->right, key);
        }
        else if (key < root->data)
        {
            root->left = deleteNode(root->left, key);
        }
        else
        {
            // Key found

            // If no children
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }

            if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            else
            {
                Node *smallestBefore = root->left;
                while (smallestBefore->right != nullptr)
                {
                    smallestBefore = smallestBefore->right;
                }
                root->data = smallestBefore->data;
                root->left = deleteNode(root->left, root->data);
            }
        }
        // Update Height
        updateHeight(root);

        // Apply rotations if needed. Return the new root.
        return Rotate(root);
    }
};

int main(void)
{
    AVLTree myTree;

    string line;
    getline(cin, line); // Take in Full line

    stringstream ss(line); // Convert to string stream. This will let us tokenize based on whitespaces.
    string token;
    vector<string> tokens;

    while (ss >> token) // Read tokens divided by whitespaces, and place into tokens vector
    {
        tokens.push_back(token);
    }

    // Last token states the order of printing so go up to n-1.
    for (size_t i = 0; i < tokens.size() - 1; i++)
    {
        // Set current token
        token = tokens[i];
        char operation = token[0];         // Get operaton
        int value = stoi(token.substr(1)); // Get value asscoiated with opeartion

        if (operation == 'A') // Addition case
        {
            myTree.root = myTree.insert(myTree.root, value); // Update root as rotations may change the base root
        }
        else if (operation == 'D') // Deletion case
        {
            myTree.root = myTree.deleteNode(myTree.root, value); // Update roots for rotations
        }
    }

    vector<int> results; // Last token in the tokens vector represents order
    if (tokens.back() == "PRE")
    {
        results = myTree.preOrder(myTree.root); // pre order case
    }
    else if (tokens.back() == "POST")
    {
        results = myTree.postOrder(myTree.root); // Post order case
    }
    else if (tokens.back() == "IN")
    {
        results = myTree.inOrder(myTree.root); // In order case
    }

    if (results.empty()) // If Empty, print "EMPTY"
    {
        cout << "EMPTY";
        return 1;
    }

    // Otherwise print results seperated by spaces.
    cout << results[0];
    for (size_t i = 1; i < results.size(); i++)
    {
        cout << " " << results[i];
    }
}