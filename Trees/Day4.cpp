#include <iostream>
#include <vector>
#include <queue>
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
// DISTRIBUTE COINS IN A BINARY TREE LEETCODE
int minCost = -1e8;
int minCostToDistribute(Node* root) {
    if(root == nullptr)
        return 0;

    int lc = minCostToDistribute(root->left);
    int rc = minCostToDistribute(root->right);
    minCost += abs(lc) + abs(rc);

    return lc + rc + root->val - 1;
}

// QUESTION 2
// BINARY TREE CAMERAS
// APPROACH IS TO DIVIDE THE NODES INTO 3 CATEGORIES
// LEAF -> 0
// NODE WITH CAMERA -> 1
// NODE WITHOUT CAMERA BUT BEING WATCHED -> 2
int cameras = 0;
int noOfCameras(Node* root) {
    if(root == nullptr)
        return 2;

    int lc = noOfCameras(root->left);
    int rc = noOfCameras(root->right);
    
    if(lc == 0 || rc == 0) {
        cameras++;
        return 1;
    }
    
    if (lc == 1 || rc == 1)
        return 2;

    return 0;
}

int minCameraCover(Node* root) {
    if(root == nullptr)
        return 0;

    int k = noOfCameras(root);
    if(k == 0)
        cameras++;
    return cameras;
}

// QUESTION 3
// BINARY TREE MAXIMUM PATH SUM
int maxAns = -1e8;
int maxPathSum(Node* root) {
    if(root = nullptr)
        return -1e8;
    
    int la = maxPathSum(root->left);
    int ra = maxPathSum(root->right);
    int v = max(la + ra + root->val, root->val);
    int maxBranch = max(la, ra);
    maxAns = max(max(v,maxBranch), max(maxBranch+root->val,maxAns));

    return min(maxBranch + root->val, root->val);
}

// QUESTION 4
// RECOVER BINARY SEARCH TREE LEETCODE
Node* first = NULL;
Node* second = NULL;
Node* prevNode = NULL;
void inorderTraversal(Node* root) {
    if(root == nullptr)
        return;
    
    inorderTraversal(root->left);
    if(prevNode != NULL && prevNode->val > root->val) {
        if(first == NULL) {
            first = prevNode;
            second = root;
        }
        else {
            second = root;
        }
        prevNode = root;
    }
    inorderTraversal(root->right);
}

void recoverTree(Node* root) {
    if(root == nullptr)
        return;
    inorderTraversal(root);
    int temp = first->val;
    first->val = second->val;
    second->val = temp;
} 

// QUESTION 5
// FLATTEN BINARY TREE TO LINKED LIST LEETCODE
Node* flattenList(Node* root) {
    if(root == nullptr)
        return nullptr;
    
    Node* lc = flattenList(root->left);
    Node* rc = flattenList(root->right);

    if(lc == nullptr && rc == nullptr)
        return root;

    if(lc == nullptr && rc != nullptr)
        return rc;

    if(lc != nullptr && rc == nullptr) {
        root->right = root->left;
        root->left = nullptr;
        return lc;
    }

    if(lc != nullptr && rc != nullptr) {
        Node* temp = root->right;
        root->right = root->left;
        lc->right = temp;
        root->left = nullptr;
        return rc;
    }
}

// QUESTION 6
// CONVERT BINARY TREE TO CIRCULAR DOUBLY LINKED LIST GFG
Node* merge(Node* t1, Node* t2) {
    Node* h1 = t1->right;
    Node* h2 = t2->right;
    t1->right = h2;
    h2->left = t1;
    t2->right = h1;
    h1->left = t2;

    return t2;
}

Node* binaryTreeToDLL(Node* root) {
    if(root == nullptr)
        return nullptr;
    
    Node* lc = binaryTreeToDLL(root->left);
    Node* rc = binaryTreeToDLL(root->right);
    root->left = root->right = root;

    if(lc == nullptr && rc == nullptr)
        return root;

    else if(lc == nullptr && rc != nullptr) {
        return merge(root, rc);
    }

    else if(lc != nullptr && rc == nullptr)
        return merge(lc, root);
    
    return merge(merge(lc, root), rc);
}

int main(int argc, char **argv)
{
    vector<int> arr = {10,20,30,40,50,60,70,80,90,100,110,120};
    Node *root = buildTree(arr);
    // Node* root = buildBST(arr, 0, arr.size() - 1);
    display(root);
}