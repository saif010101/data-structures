#include<iostream>
#include<stack>

using namespace std;

class TreeNode
{
    public:
        char val;
        TreeNode* left;
        TreeNode* right;
    
    TreeNode(char data) : val(data),left(nullptr),right(nullptr) {}
};

TreeNode *postfixToTree(string postfix);
void postorder(TreeNode* root);
bool isOperand(char c);

int main()
{
    TreeNode *root = postfixToTree("34+5*6-");
    postorder(root);

    return 0;
}

TreeNode *postfixToTree(string postfix)
{
    // create a stack of type TreeNode*
    stack<TreeNode*> st;
    // traverse the string
    for (int i = 0; i < postfix.size(); i ++)
    {
        if (isOperand(postfix[i]))
        {  
            // create a node of the operand
            TreeNode *temp = new TreeNode(postfix[i]);
            st.push(temp);
        }

        else
        {
            TreeNode *left,*right,*root;
            right = st.top();
            st.pop();
            left = st.top();
            st.pop();

            // create root 
            root = new TreeNode(postfix[i]);

            // attach left and right
            root->left = left;
            root->right = right;

            st.push(root);
        }
    }

    // return stack top
    return st.top();
}

bool isOperand(char c)
{
    return (c >= 'a' && c <= 'z' || c >= '0' && c <= '9');
}

void postorder(TreeNode* root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->val;
    }
}
