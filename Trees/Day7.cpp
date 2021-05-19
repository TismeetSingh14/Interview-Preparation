#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <climits>
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
// TO COUNT COMPLETE NODES IN A BINARY TREE LEETCODE
int leftCount(Node* node) { 
    int count = 0;
    while(node != nullptr) {
        count++;
        node = node->left;
    }
    return count;
}

int rightCount(Node* node) { 
    int count = 0;
    while(node != nullptr) {
        count++;
        node = node->right;
    }
    return count;
}

int traversal(Node* root) {
    if(root == nullptr)
        return 0;

    int lh = leftCount(root);
    int rh = rightCount(root);

    if(lh == rh)
        return (1<<lh)-1;
    
    return traversal(root->left) + traversal(root->right) + 1;
}

// QUESTION 2
// CLOSEST BINARY SEARCH TREE VALUE LINTCODE
int ans = 1e8;
void bstSearch(Node* root, int target) {
    if(root == nullptr)
        return;

    if(abs(target - root->val) < abs(ans - root->val))
        ans = root->val;
    
    if(root->val > target)
        bstSearch(root->left, target);
    
    else if(root->val < target)
        bstSearch(root->right, target);
    
    else {
        ans = root->val;
        return;
    }
}

// QUESTION 3 
// CLOSEST BINARY SEARCH TREE 2 LINTCODE
void inorderTraversal(Node* root,vector<int> &small, vector<int> &large, int target) {
    if(root == nullptr)
        return;
    
    inorderTraversal(root->left, small, large, target);
    if(root->val <= target)
        small.push_back(root->val);
    else 
        large.push_back(root->val);
    inorderTraversal(root->right, small, large, target);
}

vector<int> kNearest(Node* root, int target, int k) {
    vector<int> ans;
    vector<int> small;
    vector<int> large;
    inorderTraversal(root, small, large, target);
    int i = small.size() - 1;
    int j = 0;

    while(k > 0) {
        if(j >= large.size()) {
            ans.push_back(small[i]);
            i--;
        }

        else if(i < 0) {
            ans.push_back(large[j]);
            j++;
        }

        else if(abs(target - small[i]) < abs(target - large[j])) {
            ans.push_back(small[i]);
            i--;
        }

        else {
            ans.push_back(large[j]);
            j++;
        }
        k--;
    }

    return ans;
}

// QUESTION 4
// SUM OF ROOT TO LEAF NUMBERS LEETCODE 
int sum = 0;
void sumNumbers_(Node* root, int val) {
    if(root == nullptr) {
        return;
    }
    
    val = val*10 + root->val;
    sumNumbers_(root->left, val);      
    sumNumbers_(root->right,val);
    
    if(root->left == nullptr && root->right == nullptr) {
        sum += val;
    }
    val = val/10;
}

int sumNumbers(Node* root) {
    sum = 0;
    sumNumbers_(root, 0);
    return sum;
}

// COMPLEXITY ANALYSIS FOR QUERY TYPE APPROACHES
// METHODS            PREPROCESSING    QUERY        UPDATE
// Prefix Sum            O(N)           O(1)         O(N)
// Fenwick Tree          O(N)           O(logN)      O(logN)
// Segment Tree          O(N)           O(4logN)     O(4logN)
// Sqrt Decomposition    O(N)           O(sqrt(N))   O(1)



int main(int argc, char **argv) {
    vector<int> arr = {10,20,30,40,50,60,70,80,90,100,110,120};
    // Node *root = buildTree(arr);
    Node* root = buildBST(arr, 0, arr.size() - 1);
    display(root);
    ans = root->val;
    bstSearch(root, 53.33);
    cout << ans;
}