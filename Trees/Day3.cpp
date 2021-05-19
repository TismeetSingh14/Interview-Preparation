#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

class Node
{
public:
    int val;
    Node *left = NULL;
    Node *right = NULL;

    Node(int val)
    {
        this->val = val;
    }
};

int idx = 0;
Node *buildTree(vector<int> &arr)
{
    if (idx == arr.size() || arr[idx] == -1)
    {
        if (arr[idx] == -1)
            idx++;
        return NULL;
    }
    Node *root = new Node(arr[idx]);
    idx++;
    root->left = buildTree(arr);
    root->right = buildTree(arr);

    return root;
}

Node* buildBST(vector<int> &arr ,int si,int ei) {
    if(si>ei)
        return nullptr;

    int mid=si+(ei-si)/2;  
    Node* node = new Node(arr[mid]);

    node->left=buildBST(arr,si,mid-1);
    node->right=buildBST(arr,mid+1,ei);

    return node;
}

void display(Node *root)
{
    if (root == NULL)
        return;

    if (root->left != NULL)
        cout << root->left->val << " -> ";
    else
        cout << "."
             << " -> ";
    cout << root->val;
    if (root->right != NULL)
        cout << " <- " << root->right->val << "\n";
    else
        cout << " <- "
             << "."
             << "\n";

    display(root->left);
    display(root->right);
}

// QUESTION 1
// IMAGE MULTIPLICATION GFG
int sum = 0;
long long int m = 1e9 + 7;
void imageMultiply(Node* a, Node* b) {
    if(a == nullptr && b == nullptr) 
        return;
    
    if(a == nullptr || b == nullptr)
        return;

    sum = (sum % m + (a->val*b->val) % m) % m;
    imageMultiply(a->left, b->right);
    imageMultiply(a->right, b->left);
}

int imageMultiplication(Node* root) {
    if(root == nullptr)
        return 0;
    sum = 0;
    sum += root->val * root->val;
    imageMultiply(root->left, root->right);
    return sum;
}

// QUESTION 2
// TO FIND THE SUCCESSOR OF A NODE IN A BST
int findSuccessor(Node* root, int val) {
    Node* succ = nullptr;
    while(root != nullptr) {
        if(root->val == val) {
            
            if(root->right != nullptr) {
                succ = root->right;
                while(succ->left != nullptr) {
                    succ = succ->left;
                }
            }
            return succ == nullptr ? -1:succ->val;
        }

        else if(root->val < val) {
            root = root-> right;
        }

        else {
            succ = root;
            root = root->left;
        }
    }

    return -1;
}

// QUESTION 3
// MAXIMUM PRODUCT SPLITTED BINARY TREE LEETCODE
long long int sum;
long long int maxProd;
void dfs(Node* root) {
    if(root == nullptr) 
        return;
    sum += (long long int)root->val;
    dfs(root->left);
    dfs(root->right);
}

long long int checkMax(Node* root) {
    if(root == nullptr) 
        return 0;
    long long int l = checkMax(root->left);
    long long int r = checkMax(root->right);
    maxProd = max(maxProd, (l + r + root->val) * (sum - l - r - root->val));
    return l + r + root->val;
}
int maxProduct(Node* root) {
    sum = 0;
    maxProd = 0;
    dfs(root);
    long long int rootProd = checkMax(root);
    return (int)(maxProd % ((int)pow(10, 9) + 7));
}

// QUESTION 4
// LCA IN A BST LEETCODE
Node* lca = nullptr;
void lcaInBst(Node* root, int data1, int data2) {
    if(root == nullptr)
        return;
    
    if(root->val > data1 && root->val > data2)
        lcaInBst(root->left, data1, data2);
    
    else if(root->val < data1 && root->val < data2)
        lcaInBst(root->right, data1, data2);
    
    else {
        lca = root;
        return;
    }
}

// QUESTION 5
// LCA IN A BINARY TREE LEETCODE
Node* lcaInBinaryTree(Node* root, int data1, int data2) {
    if(root == nullptr)
        return nullptr;
    
    Node* lc = lcaInBinaryTree(root->left, data1, data2);
    Node* rc = lcaInBinaryTree(root->right, data1, data2);

    if(lc == nullptr && rc == nullptr) {
        if(root->val == data1 || root->val == data2) 
            return root;
        return nullptr;
    }

    else if(lc != nullptr && rc != nullptr) {
        return root;
    }

    else if(lc != nullptr || rc != nullptr) {
        if(root->val == data1 || root->val == data2) 
            return root;
        return lc == nullptr?rc:lc;
    }

    return nullptr;
}

int main(int argc, char **argv)
{
    vector<int> arr = {10,20,30,40,50,60,70,80,90,100,110,120};
    // Node *root = buildTree(arr);
    Node* root = buildBST(arr, 0, arr.size() - 1);
    display(root);
    cout << findSuccessor(root, 120);
    // imageMultiplication(root);
    // cout << sum << "\n";
}