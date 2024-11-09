/*
    Binary Search Tree implemenation in C++
    Muhammad Saif
*/

#include<iostream>
#include<queue>

using namespace std;

class TreeNode
{
    public:
        int val;
        TreeNode* left;
        TreeNode* right;
    
    TreeNode(int data) : val(data),left(nullptr),right(nullptr) {}
};


class BST
{
    private:
        TreeNode* root;

    public:
        BST() : root(nullptr) {}
    
    void insert(int data);
    bool search(int key);
    bool remove(int key);
    void display();

};

int main()
{

    BST tree;

    tree.insert(100);
    tree.insert(50);
    tree.insert(300);
    tree.insert(40);
    tree.insert(60);
    tree.insert(110);
    tree.insert(120);
    tree.insert(130);


    tree.remove(100);

    tree.display();

    cout << "\n";

    
    return 0;
}

void BST::insert(int data)
{
    // this is a function for insertion in a binary search tree

    // special case : tree is empty
    if (root == NULL)
    {
        // assign the new data to root pointer
        root = new TreeNode(data);
    }

    else
    {
        // curr = root
        TreeNode *curr = root;
        TreeNode *parent = nullptr;

        while (curr) // while curr is not NULL
        {
            // set parent to the last node before moving curr
            parent = curr;

            if (data < curr->val)
                curr = curr->left;
            else if (data > curr->val)
                curr = curr->right;
            else 
                return; // if duplicate is found
        }

        // insert value
        if (data < parent->val)
            parent->left = new TreeNode(data);
        else if (data > parent->val)
            parent->right = new TreeNode(data);


    }


}

bool BST::search(int key)
{

    TreeNode *curr = root;

    while (curr != NULL && curr->val != key)
    {
        if (key < curr->val)
            curr = curr->left;
        else if (key > curr->val)
            curr = curr->right;
    }

    // if the loop has ended then it can mean possibly two things
    // either we found the key or we reached a dead end

    if (curr == NULL)
        return false;
    else    
        return true;

    /* Notice here that the order in which i check the condition affects the program
    Consider for example that the loop exited because curr became NULL
    now if i had done curr->val == key, then i would be accessing a NULL pointer
    which would have led to segmentation fault error*/

}

bool BST::remove(int key)
{
    TreeNode *curr = root;  // curr points the node which holds the key
    TreeNode *parent = NULL;

    while (curr != NULL && curr->val != key)
    {
        // parent stays one step behind
        parent = curr;

        if (key < curr->val)
            curr = curr->left;
        else if (key > curr->val)
            curr = curr->right;
    }

    if (curr == NULL)
        return false;
    
    // node has no childs, then it is a simple case
    if (!curr->right && !curr->left)
    {   
        if (parent->left == curr)
            parent->left = NULL;
        else
            parent->right = NULL;

        delete curr;
    }

    // case where node has one child, either on the left or the right
    // in this case we first check whether the key node is the left
    // or right child of the parent, and then we link the remaining tree
    // accordingly

    else if (curr->right && !curr->left)
    {

        if (parent->left == curr)
            parent->left = curr->right;
        else
            parent->right = curr->right;
        
        delete curr;
    }

    else if (!curr->right && curr->left)
    {
        if (parent->left == curr)
            parent->left = curr->left;
        else
            parent->right = curr->left;
        
        delete curr;
    }

    // case where node has both childs
    else
    {
        /*
            we have to find the minimum value in the right subtree (inorder successor)
            because it is the smallest value that is greater than all the elements of the left subtree
            hence it is called a successor because replacing it with current value will
            not affect the BST property
        */

        TreeNode *successor = curr->right;  // sucessor is now the root of the right subtree
        TreeNode *successorParent = nullptr;

        // if we keep going left, we will eventually find the smallest value
        while (successor->left != NULL)
        {
            successorParent = successor;
            successor = successor->left;
        }

        // than it means that current's right subtree has no left subtree
        if (successorParent == NULL)
            curr->right = successor->right;
        else
            successorParent->left = successor->right;

        curr->val = successor->val;

        delete successor;


        // NOTE : a successor's left child will always be null because it is the least value,
        // for if it was not the least value than it would have had a left child.

    }

    return true;
}

void BST::display()
{
    // level order traversal

    // special case : if tree is empty
    if (root == NULL)
    {
        cout << "Tree is empty\n";
        return;
    }

    // create a queue to type TreeNode*
    queue<TreeNode*> q;

    q.push(root);
    while (!q.empty())
    {
        // store front in temp
        TreeNode* temp = q.front();

        if (temp->left != NULL)
            q.push(temp->left);
        if (temp->right != NULL)
            q.push(temp->right);

        cout << temp->val << " ";

        q.pop();    // dequeue
    }
}
