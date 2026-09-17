#include <stdio.h>
#include <vector>

using namespace std;
// Node class
class Node
{
public:
    int data;
    int height;
    Node *left;
    Node *right;

public:
    Node(int data) : data(data), left(nullptr), right(nullptr), height(0) {};

    // void setLeft(Node *node) { this->left = node; }
    // void setRight(Node *node) { this->right = node; }
    // Node *getLeft() { return left; }
    // Node *getRight() { return right; }
};

class AVLTree
{
public:
    Node *root;

    AVLTree()
    {
        root = nullptr;
    }

    vector<int> inOrder(Node *root)
    {
        vector<int> inOrderResults;
        inOrderAdd(root, inOrderResults);
        return inOrderResults;
    }

    vector<int> preOrder(Node *root)
    {
        vector<int> preOrderResults;
        preOrderAdd(root, preOrderResults);
        return preOrderResults;
    }

    void inOrderAdd(Node *root, vector<int> &results)
    {

        if (root == nullptr)
        {
            return;
        }

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

        postOrderAdd(root->left, results);
        postOrderAdd(root->right, results);
        results.push_back(root->data);
    }

    int getHeight(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        return root->height;
    }

    void updateHeight(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    }

    int getBalance(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        return (getHeight(root->right) - getHeight(root->left));
    }

    Node *rotateLeft(Node *root)
    {
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
        Node *newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;

        updateHeight(root);
        updateHeight(newRoot);
        return newRoot;
    }

    Node *Rotate(Node *root)
    {
        Node *newRoot;

        // RR Case
        if (getBalance(root) > 1 && getBalance(root->right) >= 0)
        { // Perform Left rotation
            newRoot = rotateLeft(root);
        }
        else if (getBalance(root) < -1 && getBalance(root->left) <= 0) // LL case
        {
            // Perform Right rotation
            newRoot = rotateRight(root);
        }
        else if (getBalance(root) > 1 && getBalance(root->right) < 0) // RL case
        {
            // Perform right rotation on right child
            root->right = rotateRight(root->right);
            // Peform left rotation on root
            newRoot = rotateLeft(root);
        }
        else if (getBalance(root) < -1 && getBalance(root->left) > 0) // LR case
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
        if (root == nullptr)
        {
            return new Node(key);
        }

        if (key > root->data)
        {
            root->right = insert(root->right, key);
        }
        else if (key < root->data)
        {
            root->left = insert(root->left, key);
        }
        else
        {
            // key already exists
            //  Do nothing
        }

        return Rotate(root); // Check and perform rotations if needed; returns new root automatically. //Heights updated therein
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
            return;
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

        // Apply rotations if needed.
        return Rotate(root);
    }
};