#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
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
// INORDER OF A BINARY TREE USING O(N) TIME AND O(1) SPACE (INCLUDING INTERNAL SPACE)
// ANY EDGE IN A TREE IS TRAVERSED 3 TIMES WHEN MORRIS TRAVERSAL IS USED
// NO. OF EDGES = NO. OF NODES - 1, AND THE NET TIME REQUIRED IS 3*N
// HENCE O(3N) CAN BE APPROXIMATED TO O(N).
Node *rightMostOfLeft(Node *leftnode, Node *curr)
{
    while (leftnode->right != NULL && leftnode->right != curr)
        leftnode = leftnode->right;

    return leftnode;
}

void morrisTraversalInorder(Node *root)
{

    Node *curr = root;
    while (curr != NULL)
    {

        Node *leftnext = curr->left;
        if (leftnext == NULL)
        {
            cout << curr->val << " ";
            curr = curr->right;
        }

        else
        {
            Node *rightmost = rightMostOfLeft(leftnext, curr);

            if (rightmost->right == NULL)
            {
                rightmost->right = curr;
                curr = curr->left;
            }

            else
            {
                cout << curr->val << " ";
                rightmost->right = NULL;
                curr = curr->right;
            }
        }
    }
}

// QUESTION 2
// PREORDER OF A BINARY TREE USING O(N) TIME AND O(1) SPACE (INCLUDING INTERNAL SPACE)
// ANY EDGE IN A TREE IS TRAVERSED 3 TIMES WHEN MORRIS TRAVERSAL IS USED
// NO. OF EDGES = NO. OF NODES - 1, AND THE NET TIME REQUIRED IS 3*N
// HENCE O(3N) CAN BE APPROXIMATED TO O(N).
void morrisTraversalPreorder(Node *root)
{

    Node *curr = root;
    while (curr != NULL)
    {

        Node *leftnext = curr->left;
        if (leftnext == NULL)
        {
            cout << curr->val << " ";
            curr = curr->right;
        }

        else
        {
            Node *rightmost = rightMostOfLeft(leftnext, curr);

            if (rightmost->right == NULL)
            {
                cout << curr->val << " ";
                rightmost->right = curr;
                curr = curr->left;
            }

            else
            {
                rightmost->right = NULL;
                curr = curr->right;
            }
        }
    }
}

// MORRIS TRAVERSAL IS ONLY FOR PREORDER AND INORDER, BUT NOT POSTORDER
// HOWEVER, WE CAN PRINT THE POSTORDER USING MORRIS' TECHNIQUE, THIS TECHNQIUE USES
// THE METHOD OF REVERSE PREORDER. IF WE PRINT REVERSE PREORDER FOR A TREE(NODE, RIGHT, LEFT)
// AND THEN REVERSE THE ORDER WE GET THE ORDER MATCHES POSTORDER OF A TREE.
// THIS TECHNIQUE ONLY PRINTS THE ORDER SIMILAR TO POSTORDER, BUT IT DOES NOT TRAVERSE THE TREE IN POSTORDER.
// IN OTHER WORDS, IT IS NOT ACTUALLY POSTORDER TRAVERSAL.

// QUESTION 3
// POSTORDER PRINTING OF A BINARY TREE USING O(N) TIME AND O(1) SPACE (INCLUDING INTERNAL SPACE)
// ANY EDGE IN A TREE IS TRAVERSED 3 TIMES WHEN MORRIS TRAVERSAL IS USED
// NO. OF EDGES = NO. OF NODES - 1, AND THE NET TIME REQUIRED IS 3*N
// HENCE O(3N) CAN BE APPROXIMATED TO O(N).
void morrisTraversalPostorderPrinting(Node *root)
{

    Node *curr = root;
    while (curr != NULL)
    {

        Node *leftnext = curr->left;
        if (leftnext == NULL)
        {
            cout << curr->val << " ";
            curr = curr->right;
        }

        else
        {
            Node *rightmost = rightMostOfLeft(leftnext, curr);

            if (rightmost->right == NULL)
            {
                cout << curr->val << " ";
                rightmost->right = curr;
                curr = curr->left;
            }

            else
            {
                rightmost->right = NULL;
                curr = curr->right;
            }
        }
    }
}


// QUESTION 4
// CONVERT BST TO GREATER TREE
int ssf = 0;
void convertBSTToGreaterTree(Node* root) {
    if(root == NULL) {
        return;
    }

    convertBSTToGreaterTree(root->right);
    root->val += ssf;
    ssf = root->val;
    convertBSTToGreaterTree(root->left);
}

// QUESTION 5
// POPULATING NEXT POINTERS
class Node_ {
    public:
    int val;
    Node_* left = NULL;
    Node_* right = NULL;
    Node_* next = NULL;

    Node_(int val) {
        this->val = val;
    }
};

void populate(Node_* root) {
    queue<Node_*> que;
    que.push(NULL);
    que.push(root);

    while(que.size() != 1) {
        if(que.front() == NULL) {
            que.pop();
            que.push(NULL);
        }

        Node_* rp = que.front();
        que.pop();
        rp->next = que.front();

        if(rp->left != NULL)
            que.push(rp->left); 
        
        if(rp->right != NULL)
            que.push(rp->right);
    }
}

// QUESTION 6
// SUM OF DISTANCES IN A TREE
int subtreeCount(unordered_map<int, vector<int>> &map, vector<int> &sub, int src, vector<bool> &vis) {
    
    if(map[src].size() == 0)
        return 1;
    vis[src] = true;
    
    int count = 0;
    for(int i = 0; i < map[src].size(); i++) {
        if(!vis[map[src][i]])
            count += subtreeCount(map, sub, map[src][i], vis);
    }
    
    sub[src] = count + 1;
    return count + 1; 
}

int calculateForZero(int src, unordered_map<int, vector<int>> &map) {
    queue<int> que;
    que.push(src);
    
    int level = 0;
    int sum = 0;
    vector<bool> vis(map.size(), false);
    while(que.size() != 0) {
        int size = que.size();
        while(size-->0) {
            int rp = que.front();
            que.pop();
            vis[rp] = true;
            sum += level;
            
            for(int i = 0; i < map[rp].size(); i++) {
                if(!vis[map[rp][i]])
                    que.push(map[rp][i]);
            }
        }
        level++;
    }
    
    return sum;
}


void calculateAns(vector<int> &ans, vector<int> &sub, unordered_map<int, vector<int>> &map, int src) {
    queue<int> que;
    que.push(src);
    vector<bool> vis(map.size(), false);
    
    while(que.size() != 0) {
        int size = que.size();
        while(size-->0) {
            int rp = que.front();
            que.pop();
            vis[rp] = true;
            
            
            for(int i = 0; i < map[rp].size(); i++) {
                if(!vis[map[rp][i]]) {
                    que.push(map[rp][i]);
                    ans[map[rp][i]] = ans[rp] - sub[map[rp][i]] + (map.size() -sub[map[rp][i]]);
                }
                                                                                
            }
            
        }
    }
}

vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
    if(edges.size() == 0) {
        vector<int> base(N,0);
        return base;
    }
    unordered_map<int, vector<int>> map;
    for(int i = 0; i < edges.size(); i++) {
        if(map.find(edges[i][0]) == map.end()) {
            vector<int> arr;
            map[edges[i][0]] = arr;
        }
        
        if(map.find(edges[i][1]) == map.end()) {
            vector<int> arr;
            map[edges[i][1]] = arr;
        }
        map[edges[i][0]].push_back(edges[i][1]);
        map[edges[i][1]].push_back(edges[i][0]);
    }
    
    int src = 0;
    
    vector<int> ans(N, 0);
    ans[src] = calculateForZero(src, map);

    vector<int> sub(N, 1);
    vector<bool> vis(N,false);
    subtreeCount(map, sub, src, vis);
    
    calculateAns(ans, sub, map, src);
    return ans;
}

int main(int argc, char **argv)
{
    vector<int> arr = {4, 1, 0, -1, -1, 2, -1, 3, -1, -1, 6, 5, -1, -1, 7, -1, 8, -1, -1};
    Node *root = buildTree(arr);
    display(root);
    morrisTraversalInorder(root);
    cout << "\n";
    morrisTraversalPreorder(root);
    cout << "\n";
    convertBSTToGreaterTree(root);
    morrisTraversalInorder(root);
}