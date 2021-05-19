#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <stack>
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
// RIGHT SIDE VIEW OF A BINARY TREE LEETCODE
vector<int> rightSideView(Node* root) {
    if(root == NULL)
        return {};

    queue<Node*> que;
    vector<int> ans;
    que.push(root);

    while(que.size() > 0) {
        int lastVal = 0;
        int size = que.size();
        while(size-->0) {
            Node* rp = que.front();
            que.pop();

            lastVal = rp->val;

            if(rp->left != NULL)
                que.push(rp->left);

            if(rp->right != NULL)
                que.push(rp->right);
        }
        ans.push_back(lastVal);
    }

    return ans;
}

// QUESTION 2
// LEFT SIDE VIEW OF A BINARY TREE GFG
vector<int> leftSideView(Node* root) {
    if(root == NULL)
        return {};

    queue<Node*> que;
    vector<int> ans;
    que.push(root);

    while(que.size() > 0) {
        int lastVal = 0;
        int size = que.size();
        while(size-->0) {
            Node* rp = que.front();
            que.pop();

            lastVal = rp->val;

            if(rp->right != NULL)
                que.push(rp->right);

            if(rp->left != NULL)
                que.push(rp->left);
        }
        ans.push_back(lastVal);
    }

    return ans;
}

// QUESTION 3
// TOP VIEW OF A BINARY TREE GFG
// THE APPROACH IS TO USE LEVEL ORDER BUT FOR VERTICAL LEVELS
// WHENEVER WE GO LEFT WE ADD -1 TO THE LEVEL OF THE PARENT
// WHENEVER WE GO RIGHT WE ADD +1 TO THE LEVEL OF THE PARENT
// IN THIS WAY WE ARE ABLE TO CREATE LEVELS HORIZONTALLY
// THE ROOT IS ASSUMED TO BE LEVEL 0
vector<int> topView(Node* root) {
    if(root == nullptr) 
        return {};

    queue<pair<Node*, int>> que;
    que.push({root,0});
    vector<int> ans;
    map<int, int> m;

    while(que.size() > 0) {
        int size = que.size();
        while(size-->0) {
            
            pair<Node*, int> rp = que.front();
            que.pop();

            if(m.find(rp.second) == m.end()) {
                m[rp.second] = rp.first->val;
            }
            
            if(rp.first->left != nullptr) {
                que.push({rp.first->left, rp.second - 1});
            }

            if(rp.first->right != nullptr) {
                que.push({rp.first->right, rp.second + 1});
            }
        }
    }

    for(auto k:m) {
        ans.push_back(k.second);
    }

    return ans;
}

// QUESTION 4
// BOTTOM VIEW OF A BINARY TREE GFG
// THE APPROACH IS TO USE LEVEL ORDER BUT FOR VERTICAL LEVELS
// WHENEVER WE GO LEFT WE ADD -1 TO THE LEVEL OF THE PARENT
// WHENEVER WE GO RIGHT WE ADD +1 TO THE LEVEL OF THE PARENT
// IN THIS WAY WE ARE ABLE TO CREATE LEVELS HORIZONTALLY
// THE ROOT IS ASSUMED TO BE LEVEL 0
// IN CASE OF TIE PRINT LAST ELEMENT
vector<int> bottomView(Node* root) {
    if(root == nullptr) 
        return {};

    queue<pair<Node*, int>> que;
    que.push({root,0});
    vector<int> ans;
    map<int, int> m;

    while(que.size() > 0) {
        int size = que.size();
        while(size-->0) {
            
            pair<Node*, int> rp = que.front();
            que.pop();

            m[rp.second] = rp.first->val;
            
            if(rp.first->left != nullptr) {
                que.push({rp.first->left, rp.second - 1});
            }

            if(rp.first->right != nullptr) {
                que.push({rp.first->right, rp.second + 1});
            }
        }
    }

    for(auto k:m) {
        ans.push_back(k.second);
    }

    return ans;
}

// QUESTION 5
// BOTTOM VIEW OF A BINARY TREE VARIATION GFG
// THE APPROACH IS TO USE LEVEL ORDER BUT FOR VERTICAL LEVELS
// WHENEVER WE GO LEFT WE ADD -1 TO THE LEVEL OF THE PARENT
// WHENEVER WE GO RIGHT WE ADD +1 TO THE LEVEL OF THE PARENT
// IN THIS WAY WE ARE ABLE TO CREATE LEVELS HORIZONTALLY
// THE ROOT IS ASSUMED TO BE LEVEL 0
// IN CASE OF TIE PRINT FIRST ELEMENT
vector<int> bottomViewVariation(Node* root) {
    if(root == nullptr) 
        return {};

    queue<pair<Node*, int>> que;
    que.push({root,0});
    vector<int> ans;
    map<int, int> m;

    while(que.size() > 0) {
        int size = que.size();
        while(size-->0) {
            
            pair<Node*, int> rp = que.front();
            que.pop();

            m[rp.second] = rp.first->val;

            if(rp.first->right != nullptr) {
                que.push({rp.first->right, rp.second + 1});
            }
            
            if(rp.first->left != nullptr) {
                que.push({rp.first->left, rp.second - 1});
            }
        }
    }

    for(auto k:m) {
        ans.push_back(k.second);
    }

    return ans;
}

// QUESTION 6
// DIAGONAL TRAVERSAL OF A BINARY TREE GFG
// THE APPROACH IS TO USE LEVEL ORDER BUT FOR VERTICAL LEVELS
// WHENEVER WE GO LEFT WE ADD -1 TO THE LEVEL OF THE PARENT
// WHENEVER WE GO RIGHT WE ADD TO THE LEVEL OF THE PARENT
// IN THIS WAY WE ARE ABLE TO CREATE LEVELS HORIZONTALLY
// THE ROOT IS ASSUMED TO BE LEVEL 0
vector<vector<int>> diagonalView(Node* root) {
    if(root == nullptr) 
        return {};

    queue<pair<Node*, int>> que;
    que.push({root,0});
    vector<vector<int>> ans;
    map<int, vector<int>> m;

    while(que.size() > 0) {
        int size = que.size();
        while(size-->0) {
            
            pair<Node*, int> rp = que.front();
            que.pop();

            if(m.find(rp.second) == m.end()) {
                vector<int> arr;
                m[rp.second] = arr;
            }

            m[rp.second].push_back(rp.first->val);
            
            if(rp.first->left != nullptr) {
                que.push({rp.first->left, rp.second - 1});
            }

            if(rp.first->right != nullptr) {
                que.push({rp.first->right, rp.second});
            }
        }
    }

    for(auto k:m) {
        ans.push_back(k.second);
    }

    return ans;
}

// QUESTION 7
// VERTICAL ORDER TRAVERSAL OF A BINARY TREE
// THE APPROACH IS TO USE LEVEL ORDER BUT FOR VERTICAL LEVELS
// WHENEVER WE GO LEFT WE ADD -1 TO THE LEVEL OF THE PARENT
// WHENEVER WE GO RIGHT WE ADD TO THE LEVEL OF THE PARENT
// IN THIS WAY WE ARE ABLE TO CREATE LEVELS HORIZONTALLY
// THE ROOT IS ASSUMED TO BE LEVEL 0
// IF MORE THAN ONE NODE IS THERE AT THE SAME HORIZONTAL AND 
// SAME VERTICAL LEVEL, THEN TIES MUST BE BROKEN BY ARRANGING
// THE NODES IN ASCENDING ORDER
vector<vector<int>> verticalOrderTraversal(Node* root) {
    if(root == nullptr) 
        return {};

    queue<pair<Node*, int>> que;
    que.push({root, 0});
    map<int, vector<pair<int, int>>>m;
    int level = 0;

    while(que.size() > 0) {
        int size = que.size();
        while(size-- > 0) {
            pair<Node*, int> rp = que.front();
            que.pop();

            if(m.find(rp.second) == m.end()) {
                vector<pair<int, int>> arr;
                m[rp.second] = arr;
            }

            m[rp.second].push_back({rp.first->val,level});

            if(rp.first->left != nullptr) 
                que.push({rp.first->left, rp.second - 1});

            if(rp.first->right != nullptr)
                que.push({rp.first->right, rp.second + 1});
        }
        level++;
    }

    vector<vector<int>> ans;

    for(auto k: m) {
        sort(k.second.begin(),k.second.end(), [] (pair<int, int> const& s1, pair<int, int> const& s2) -> bool {
            if(s1.second == s2.second) {
                return s1.first < s2.first;
            }

            return s1.second < s2.second;
        });
        vector<int> a;
        for(pair<int, int> i: k.second) {
            a.push_back(i.first);
        }

        ans.push_back(a);
    }

    return ans;
}

// QUESTION 8
// REVERSE LEVEL ORDER OF A BINARY TREE GFG
vector<int> reverseLevelOrder(Node* root) {
    if(root == nullptr) 
        return {};

    stack<int> st;
    queue<Node*> que;

    while(que.size() > 0) {
        int size = que.size();
        while(size-- > 0) {
            Node* rp = que.front();
            que.pop();

            st.push(rp->val);

            if(rp->right != nullptr)
                que.push(rp->right);

            if(rp->left != nullptr) 
                que.push(rp->left);

        }
    }

    vector<int> ans;

    while(st.size() > 0) {
        ans.push_back(st.top());
        st.pop();
    }

    return ans;
}

// QUESTION 9
// BOUNDARY TRAVERSAL OF A BINARY TREE LEETCODE 
// SPLIT THE PROBLEM INTO THREE PARTS
// PART ONE IS FOR LEFT BOUNDARY
// PART TWO IS FOR LEAF NODES
// PART THREE IS FOR RIGHT BOUNDARY
void leftBoundaryTraversal(Node* root, vector<int> &ans) {
    if(root == nullptr)
        return;

    if(root->left != nullptr) {
        ans.push_back(root->val);
        leftBoundaryTraversal(root->left, ans);
    }
    else if(root->right != nullptr) {
        ans.push_back(root->val);
        leftBoundaryTraversal(root->right, ans);
    }
}

void rightBoundaryTraversal(Node* root, vector<int> &ans) {
    if(root == nullptr)
        return;

    if(root->right != nullptr) {
        rightBoundaryTraversal(root->right, ans);
        ans.push_back(root->val);
    }
    else if(root->left != nullptr) {
        rightBoundaryTraversal(root->left, ans);
        ans.push_back(root->val);
    }
    
}

void leafTraversal(Node* root, vector<int> &ans) {
    if(root == nullptr)
        return;
    
    leafTraversal(root->left, ans);
    if(root->left == nullptr && root->right == nullptr)
        ans.push_back(root->val);
    leafTraversal(root->right, ans);
}

vector<int> boundaryTraversal(Node* root) {
    vector<int> ans;
    leftBoundaryTraversal(root, ans);
    leafTraversal(root, ans);
    rightBoundaryTraversal(root->right, ans);

    return ans;
}

// QUESTION 10
// BINARY TREE COLORING GAME LEETCODE
int size(Node* root) {
    if(root == nullptr)
        return 0;
    
    int ls = size(root->left);
    int rs = size(root->right);
    
    return ls + rs + 1;
}
Node* find(Node* root, int x) {
    if(root == NULL)
        return nullptr;
    if(root->val == x)
        return root;
    Node* lr = find(root->left, x);
    Node* rr = find(root->right, x);
    
    return lr == NULL?rr:lr;
}
bool btreeGameWinningMove(Node* root, int n, int x) {
    Node* k = find(root, x);
    int size1 = size(k->left);
    int size2 = size(k->right);
    
    int rt = n - size1 - size2 - 1;
    
    if(rt >= n/2 + 1 || size1 >= n/2 + 1 || size2 >= n/2 + 1)
        return true;
    return false;
}

int main(int argc, char** argv){
    vector<int> arr = {4, 1, 0, -1, -1, 5, -1, 3, -1, -1, 6, 2, -1, -1, 7, -1, 8, -1, -1};
    Node *root = buildTree(arr);
    display(root);

    vector<int> a = boundaryTraversal(root);
    for(int i: a)
        cout << i << " ";

    // vector<vector<int>> b = verticalOrderTraversal(root);
    // for(vector<int> i: b) {
    //     for(int k : i)
    //         cout << k << " ";
    //     cout << endl;    
    // }
}