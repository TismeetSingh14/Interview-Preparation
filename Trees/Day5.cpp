#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <sstream>
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
// CONVERT SORTED DOUBLY LINKED LIST TO BALANCED BINARY TREE LEETCODE
// TIME COMPLEXITY IS O(N)
Node* temp = nullptr;
Node* build(int n) {
    if(n <= 0)
        return nullptr;
    
    Node* lc = build(n/2);
    Node* root = temp;
    root->left = lc;
    temp = temp->right;
    Node* rc = build(n - n/2 - 1);
    root->right = rc;

    return root;
}

Node* DLLToBST(Node* head) {
    int ptr = 0;
    Node* curr = head;
    while(curr != nullptr) {
        curr = curr->right;
        ptr++;
    }

    temp = head;
    Node* root = build(ptr);
    return root;
}

// QUESTION 2
// MERGE TWO BST LEETCODE
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

Node* mergeTwoSortedDLL(Node* head1, Node* head2) {

    Node* h = new Node(-1);
    Node* head = h;
    Node* temp1 = head1;
    Node* temp2 = head2;

    while(temp1->right && temp2->right) {
        if(temp1->val < temp2->val) {
            head->right = temp1;
            temp1->left = head;
            head = head->right;
            temp1 = temp1->right;
        }

        else {
            head->right = temp2;
            temp2->left = head;
            head = head->right;
            temp2 = temp2->right;
        }
    }

    while(temp1 != nullptr) {
        head->right = temp1;
        temp1->left = head;
        head = head->right;
        temp1 = temp1->right;
    }

    while(temp2 != nullptr) {
        head->right = temp2;
        temp2->left = head;
        head = head->right;
        temp2 = temp2->right;
    }

    Node* newHead = h->right;
    newHead->left = nullptr;
    h->right = nullptr;
    return newHead;
}

void displayll(Node* head) {
    Node* curr = head;
    while(curr != nullptr) {
        cout << curr -> val << " "; 
        curr = curr->right;
    }
    cout << endl;
}

Node* mergeTwoBST(Node* root1, Node* root2) {
    Node* head1 = binaryTreeToDLL(root1)->right;
    Node* head2 = binaryTreeToDLL(root2)->right;
    Node* h1 = head1->left;
    Node* h2 = head2->left;
    head1->left = nullptr;
    head2->left = nullptr;
    h1->right = nullptr;
    h2->right = nullptr;
    
    displayll(head1);
    displayll(head2);

    Node* head = mergeTwoSortedDLL(head1, head2);
    displayll(head);
    return DLLToBST(head);
}

// QUESTION 3
// CLONE A BINARY TREE WITH RANDOM POINTER LEETCODE
class Node_
{
public:
    int val;
    Node_* left = NULL;
    Node_* right = NULL;
    Node_* random = NULL;

    Node_(int val)
    {
        this->val = val;
    }
};
void traversal(Node_* root) {
    if(root == nullptr) {
        return;
    }

    Node_* newNode = new Node_(root->val);
    newNode->left = root->left;
    root->left = newNode;
    traversal(root->left->left);
    traversal(root->right);
}

void settingRandomPointers(Node_* root) {
    if(root == nullptr) {
        return;
    }

    if(root->random == nullptr)
        root->left->random = nullptr;
    else
        root->left->random = root->random->left;
    settingRandomPointers(root->left->left);
    settingRandomPointers(root->right);
}

Node_* extraction(Node_* root) {
    if(root == nullptr)
        return nullptr;

    Node_* lc = extraction(root->left->left);
    Node_* rc = extraction(root->right);
    Node_* rootp1 = root->left;
    rootp1->left = lc;
    rootp1->right = rc;
    root->left = root->left->left;

    return rootp1;
}

Node_* cloneTreeWithRandomPointer(Node_* root) {
    traversal(root);
    settingRandomPointers(root);
    Node_* r = extraction(root);
    return r;
}

// QUESTION 4
// DELETE NODE IN BST LEETCODE
int leftMostOfRight(Node* node) {
    while(node->left != nullptr)
        node = node->left;
    return node->val;
}

Node* deleteNode(Node* root, int data) {
    if(root == nullptr)
        return nullptr;
    
    if(root->val == data) {
        if(!root->left || !root->right) {
            return root->left == nullptr? root->right:root->left;
        }

        int l = leftMostOfRight(root->right);
        root->val = l;
        root->right = deleteNode(root->right, l);
    }

    else if(root->val > data) {
        root->left = deleteNode(root->left, data);
    }

    else {
        root->right = deleteNode(root->right,data);
    }
}

// QUESTION 5
// DELETE LEAVES WITH PARTICULAR VALUE LEETCODE
Node* removeLeafNodes(Node* root, int target) {
    if(root == nullptr)
        return nullptr;
    
    root->left = removeLeafNodes(root->left, target);
    root->right = removeLeafNodes(root->right, target);
    
    if(root->val == target && root->left == nullptr && root->right == nullptr) {
        return nullptr;
    }
    
    return root;
}

// QUESTION  6
// CONSTRUCT TREE FROM PREORDER AND INORDER LEETCODE
int idx2 = 0;
Node* treeFromPreAndIn(vector<int>& preorder, unordered_map<int,int>& in, int beg, int end) {
    if(beg > end || idx >= preorder.size())
        return nullptr;
    int rootVal = preorder[idx2];
    idx2++;
    Node* root = new Node(rootVal);

    if(beg == end) {
        return root;
    }

    int k = in[rootVal];
    root->left = treeFromPreAndIn(preorder, in, beg, k - 1);
    root->right = treeFromPreAndIn(preorder, in, k + 1, end);

    return root;
}

Node* buildTreeFromPreAndIn(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int,int> in;
    for(int i = 0; i < inorder.size(); i++)
        in[inorder[i]] = i;
    idx2 = 0;
    Node* r = treeFromPreAndIn(preorder, in, 0, preorder.size() - 1);
    return r;
}

// QUESTION 7
// CONSTRUCT TREE FROM INORDER AND POSTORDER LEETCODE
int idx3 = 0;
Node* treeFromPostAndIn(vector<int>& postorder, unordered_map<int,int>& in, int beg, int end) {
    if(beg > end || idx3 < 0)
        return nullptr;
    int rootVal = postorder[idx3];
    idx3--;
    Node* root = new Node(rootVal);

    if(beg == end) {
        return root;
    }

    int k = in[rootVal];
    root->right = treeFromPostAndIn(postorder, in, k + 1, end);
    root->left = treeFromPostAndIn(postorder, in, beg, k - 1);
    return root;
}

Node* buildTreeFromPostAndIn(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int,int> in;
    for(int i = 0; i < inorder.size(); i++)
        in[inorder[i]] = i;
    idx3 = postorder.size() - 1;
    Node* r = treeFromPostAndIn(postorder, in, 0, postorder.size() - 1);
    return r;
}

int main(int argc, char **argv) {
    vector<int> arr = {1,5,9,10,11};
    vector<int> arr_ = {2,3,4,7,12,13};
    // Node *root = buildTree(arr);
    Node* root = buildBST(arr, 0, arr.size() - 1);
    Node* root_ = buildBST(arr_, 0, arr_.size() - 1);
    Node* ret = mergeTwoBST(root, root_);
    display(ret);
}