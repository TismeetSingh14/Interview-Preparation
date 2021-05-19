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

// QUESTION 2
// IS BST IN PREORDER
bool validate(Node* root, long long int maxVal, long long int minVal) {
    if(root == nullptr)
        return true;
    
    if(root->val > maxVal || root->val < minVal)
        return false;
    bool lc = validate(root->left, root->val-1, minVal);
    if(lc == false) 
        return false;
    bool rc = validate(root->right, maxVal, root->val + 1);
    if(rc == false)
        return false;

    return true;
}

bool isValidBST(Node* root) {
    return validate(root, LLONG_MAX, LLONG_MIN);
}

// QUESTION 3
// CONSTRUCT BST FROM GIVEN POSTORDER
int idx1 = 0;
Node* buildBstFromPost(vector<int> &postorder, int minVal, int maxVal) {

    if(idx1 == -1)
        return nullptr;
    
    if(postorder[idx1] < minVal || postorder[idx1] > maxVal)
        return nullptr;

    Node* root = new Node(postorder[idx1]);
    idx1--;
    root->right = buildBstFromPost(postorder, root->val + 1, maxVal);
    root->left = buildBstFromPost(postorder, minVal, root->val - 1);


    return root;
}

void bstFromPostorder() {
    vector<int> postorder = {1,7,5,35,50,40,10};
    idx1 = postorder.size() - 1;
    Node* k = buildBstFromPost(postorder, INT_MIN, INT_MAX);
    display(k);
}

// QUESTION 4
int idx2 = 0;
Node* buildBstFromPre(vector<int> &preorder, int minVal, int maxVal) {

    if(idx2 == preorder.size())
        return nullptr;
    
    if(preorder[idx2] < minVal || preorder[idx2] > maxVal)
        return nullptr;

    Node* root = new Node(preorder[idx2]);
    idx2++;
    root->left = buildBstFromPre(preorder, minVal, root->val - 1);
    root->right = buildBstFromPre(preorder, root->val + 1, maxVal);


    return root;
}

void bstFromPreorder() {
    vector<int> preorder = {10, 5, 1, 7, 40, 35, 50};
    idx2 = 0;
    Node* k = buildBstFromPre(preorder, INT_MIN, INT_MAX);
    display(k);
}

// QUESTION 5
// CONSTRUCT TREE FROM PREORDER AND POSTORDER
int index = 0;
Node* buildTreePrePost(vector<int> &pre, vector<int> &post, int si, int ei) {
    if(index == pre.size() || si > ei) 
        return nullptr;

    Node* root = new Node(pre[index]);
    index++;
    
    if(si == ei)
        return root;

    int i;
    for(i = si; i <= ei; i++) {
        if(pre[index] == post[i])
            break;
    }

    if(i <= ei) {
        root->left = buildTreePrePost(pre, post, si, i);
        root->right = buildTreePrePost(pre, post, i + 1, ei);
    }

    return root;
}

void buildTreeFromPreorderAndPostorder() {
    vector<int> pre = {1, 2, 4, 8, 9, 5, 3, 6, 7};
    vector<int> post = {8, 9, 4, 5, 2, 6, 7, 3, 1};

    Node* root = buildTreePrePost(pre, post, 0, pre.size() - 1);
    display(root);
}

// QUESTION 6
// TO SERIALIZE AND DESERIALIZE A BINARY TREE
void serialize_(Node* root, ostringstream& k) {
    if (root) {
        k << root->val << ' ';
        serialize_(root->left, k);
        serialize_(root->right, k);
    } else {
        k << "# ";
    }
}

string serialize(Node* root) {
    ostringstream k;
    serialize_(root, k);
    return k.str();
}

Node* deserialize_(istringstream& k) {
    string val;
    k >> val;
    if (val == "#")
        return nullptr;
    Node* root = new Node(stoi(val));
    root->left = deserialize_(k);
    root->right = deserialize_(k);
    return root;
}

Node* deserialize(string data) {
    istringstream k(data);
    return deserialize_(k);
}

// QUESTION 7
// FENWICK TREE
// PREPROCESSING O(N)
// TO SOLVE A QUERY O(logN)
// TO UPDATE DATA O(logN)
// TO SOLVE Q QUERIES O(Q*logN)
// FENWICK TREE IS 1-INDEXED AS IT IS DEPENDENT ON BITS
// REQUIRED INDICES ARE 1 TO N (N = NUMBER OF DATA ELEMENTS)
int calculateSum(vector<int> &fenwickArr, int i) {
    int sum = 0;
    while(i > 0) {
        sum += fenwickArr[i];
        i -= (i&(-i));
    }

    return sum;
}

int solveQuery(vector<int> &fenwickArr, int si, int ei) {
    int sum_1_ei = calculateSum(fenwickArr, ei);
    int sum_1_si = calculateSum(fenwickArr, si - 1);
    return sum_1_ei - sum_1_si;
}

void update(vector<int> &fenwickArr, int newVal, int i) {
    int delta = newVal - fenwickArr[i];
    while(i < fenwickArr.size() + 1) {
        fenwickArr[i] += delta;
        i += (i & (-i));
    }
}

void preprocessArray(vector<int> &arr) {
    vector<int> fenwickArr(arr.size() + 1, 0);
    vector<int> prefixSum(arr.size() + 1, 0);

    prefixSum[1] = arr[0];
    for(int i = 1; i < arr.size(); i++) {
        prefixSum[i + 1] = prefixSum[i] + arr[i];
    }

    for(int i = 1; i <= arr.size(); i++) {
        fenwickArr[i] = prefixSum[i] - prefixSum[i-(i&(-i))];
    }
    
    cout << solveQuery(fenwickArr,2, 15) << endl;
    update(fenwickArr, 6,3);
    cout << solveQuery(fenwickArr,2, 15) << endl;
}

// QUESTION 8
// LONGEST ZIGZAG PATH IN A BINARY TREE LEETCODE
int m = -1e8;
pair<int, int> zigzag(Node* root) {
    if(root == nullptr)
        return {-1,-1};
    
    pair<int, int> ret;
    pair<int, int> lc = zigzag(root->left);
    pair<int, int> rc = zigzag(root->right);
    
    if(lc.second + 1 > m) 
        m = lc.second + 1;
    
    if(rc.first + 1 > m) 
        m = rc.first + 1;

    ret.first = lc.second + 1;
    ret.second = rc.first + 1;
    
    return ret;
}

int longestZigZag(Node* root) {
    m = -1e8;
    zigzag(root);
    return m;
}

int main(int argc, char **argv) {
    vector<int> arr = {10,20,30,40,50,60,70,80,90,100,110,120};
    // Node *root = buildTree(arr);
    Node* root = buildBST(arr, 0, arr.size() - 1);
    display(root);
    // buildTreeFromPreorderAndPostorder();
    // vector<int> a = {3,2,4,0,5,-6,-1,-2,4,4,1,-3,4,2,-7,8};
    // preprocessArray(a);
}