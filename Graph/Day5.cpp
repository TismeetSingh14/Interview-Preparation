#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <unordered_set>
using namespace std;
#define pii pair<int, int>

class Edge {
    public:
    int v = -1;
    int w = -1;

    Edge() {

    }

    Edge(int v, int w) {
        this->v = v;
        this->w = w;
    }
};

void addEdge(vector<vector<Edge*>> &graph,int u, int v, int w) {

    graph[u].push_back(new Edge(v, w));
    // TO MAKE THE GRAPH DIRECTED COMMENT THE BELOW LINE
    graph[v].push_back(new Edge(u, w));
}

int findPar(vector<int>& par, int x) {
    if(par[x] == x)
        return x;
    par[x] = findPar(par, par[x]);
    return par[x];
}

void merge(vector<int> &par, vector<int> &rank, int x, int y) {
    int lox = findPar(par,x);
    int loy = findPar(par,y);

    if(lox != loy) {
        if(rank[lox] > rank[loy])
            par[loy] = lox;
        
        else if(rank[loy] > rank[lox])
            par[lox] = loy;
        
        else {
            par[lox] = loy;
            rank[loy]++;
        }
    }
}

// QUESTION 1
// NUMBER OF DISTINCT ISLANDS II LEETCODE/LINTCODE
int numOfIslands(vector<vector<int>> &arr, int n, int m) {
    vector<int> par(n*m, 0);
    vector<int> rank(n*m, 1);
    vector<vector<int>> grid(n, vector<int>(m, 0));
    vector<int> ans(arr.size(), 0);
    for(int i = 0; i < par.size(); i++) 
        par[i] = i;
    
    int count = 0;
    vector<vector<int>> dir = {{1,0},{0,1},{-1,0},{0,-1}};

    for(int i = 0; i < arr.size(); i++) {
        count++;
        grid[arr[i][0]][arr[i][1]] = 1;

        for(int d = 0; d < 4; d++) {
            int x = arr[i][0] + dir[d][0];
            int y = arr[i][1] + dir[d][1];

            if(x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 1) {
                int p1 = arr[i][0]*m + arr[i][1];
                int p2 = x*m + y;

                if(par[p1] != par[p2]) {
                    merge(par, rank, p1, p2); 
                    count--;
                }
            }  
        }
        ans[i] = count; 
    }

    for(int i = 0; i < ans.size(); i++) 
        cout << ans[i] << " ";
}

// QUESTION 2
// REGION CUT BY SLASHES LEETCODE
void dfs(vector<vector<int>> &graph, int i, int j) {
    if(i < 0 || j < 0 || i >= graph.size() || j >= graph.size() || graph[i][j] == 1)
        return ;
    
    graph[i][j] = 1;
    
    dfs(graph, i + 1 , j);
    dfs(graph, i , j + 1);
    dfs(graph, i , j - 1);
    dfs(graph, i - 1 , j);
}

int regionsBySlashes(vector<string>& grid) {
    vector<vector<int>> graph(grid.size()*3,vector<int>(grid.size()*3,0));
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid.size(); j++) {
            if(grid[i][j] == '/') {
                graph[i*3][j*3 + 2] = 1;
                graph[i*3 + 1][j*3 + 1] = 1;
                graph[i*3 + 2][j*3] = 1;
            }
            
            if(grid[i][j] == '\\') {
                graph[i*3][j*3] = 1;
                graph[i*3 + 1][j*3 + 1] = 1;
                graph[i*3 + 2][j*3 + 2] = 1;
            }
        }
    }
    
    int count = 0;
    for(int i = 0; i < graph.size(); i++) {
        for(int j = 0; j < graph.size(); j++) {
            if(graph[i][j] == 0) {
                dfs(graph, i, j);
                count++;
            }
        }
    }
    
    return count;
}

// QUESTION 3
// SENTENCE SIMILARITY II LEETCODE/LINTCODE
string findString(unordered_map<string, string> &par, string s) {
    if(par[s] == s) {
        return s;
    }

    par[s] = findString(par, par[s]);
    return par[s];
}

void mergeString(unordered_map<string, string> &par, unordered_map<string, int> &rank, string x, string y) {
    string lox = findString(par, x);
    string loy = findString(par, y);

    if(lox != loy) {
        if(rank[lox] > rank[loy])
            par[loy] = lox;
        else if(rank[loy] > rank[lox]) 
            par[lox] = loy;
        else {
            par[lox] = loy;
            rank[loy]++;
        }
    }
}

bool sentenceSimilarityII(vector<string> &words1, vector<string> &words2, vector<vector<string>> &pairs) {
    unordered_map<string, string> par;
    unordered_map<string, int> rank;

    for(int i = 0; i < pairs.size(); i++) {
        if(par.find(pairs[i][0]) == par.end()) {
            par[pairs[i][0]] = pairs[i][0];
            rank[pairs[i][0]] = 1;
        }

        if(par.find(pairs[i][1]) == par.end()) {
            par[pairs[i][1]] = pairs[i][1];
            rank[pairs[i][1]] = 1;
        }

        mergeString(par, rank, pairs[i][0], pairs[i][1]);
    }

    for(int i = 0; i < words1.size(); i++) {
        if(words1[i] == words2[i])
            continue;
        if(par.find(words1[i]) == par.end() || par.find(words2[i]) == par.end())
            return false;
        if(par[words1[i]] != par[words2[i]])
            return false;
    }

    return true;
}

// QUESTION 4
// SATISFIABILITY OF EQUALITY EQUATIONS LEETCODE
char findChar(unordered_map<char, char> &par, char s) {
    if(par[s] == s) {
        return s;
    }

    par[s] = findChar(par, par[s]);
    return par[s];
}

void mergeChar(unordered_map<char, char> &par, unordered_map<char, int> &rank, char x, char y) {
    char lox = findChar(par, x);
    char loy = findChar(par, y);

    if(lox != loy) {
        if(rank[lox] > rank[loy])
            par[loy] = lox;
        else if(rank[loy] > rank[lox]) 
            par[lox] = loy;
        else {
            par[lox] = loy;
            rank[loy]++;
        }
    }
}
bool equationsPossible(vector<string>& equations) {
    unordered_map<char, char> par;
    unordered_map<char, int> rank;

    for(int i = 0; i < equations.size(); i++) {
        if(par.find(equations[i][0]) == par.end()) {
            par[equations[i][0]] = equations[i][0];
            rank[equations[i][0]] = 1;
        }

        if(par.find(equations[i][3]) == par.end()) {
            par[equations[i][3]] = equations[i][3];
            rank[equations[i][3]] = 1;
        }

        if(equations[i][1] == '=' && equations[i][2] == '=') {
            mergeChar(par, rank, equations[i][0], equations[i][3]);
        }
    }
    
    for(int i = 0; i < equations.size(); i++) {
        if(equations[i][1] == equations[i][2]) {
            if(findChar(par, equations[i][0]) != findChar(par, equations[i][3]) )
                return false;
        }

        else {
            if(findChar(par, equations[i][0]) == findChar(par, equations[i][3]))
                return false;
        }
    }

    return true;
}

// QUESTION 5
// REDUNDANT CONNECTION I LEETCODE
// UNION BY SIZE APPROACH (CAN BE DONE THROUGH RANK AS WELL)
void mergeLeaders(int p1, int p2, vector<int> &size, vector<int> &par)
{
    if (size[p1] > size[p2]) {
        par[p2] = p1;
        size[p1] += size[p2];
    }

    else {
        par[p1] = p2;
        size[p2] += size[p1];
    }
}

int findParent(int vtx, vector<int> &par) {
    if (par[vtx] == vtx)
        return vtx;

    par[vtx] = findParent(par[vtx], par);
    return par[vtx];
}

vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    vector<int> parent;
    vector<int> size;

    for (int i = 0; i < edges.size(); i++) {
        edges[i][0]--;
        edges[i][1]--;
        parent.push_back(i);
        size.push_back(1);
    }

    for (vector<int> ar : edges) {
        int p1 = findParent(ar[0], parent);
        int p2 = findParent(ar[1], parent);

        if (p1 != p2)
            mergeLeaders(p1, p2, size, parent);

        else
        {
            ar[0]++;
            ar[1]++;
            return ar;
        }
    }

    return {};
}

void solve() {
    int n = 7;
    vector<vector<Edge*>> graph(n,vector<Edge*>());
    addEdge(graph,0,1,0);
    addEdge(graph,1,2,0);
    addEdge(graph,2,3,0);
    addEdge(graph,0,3,0);
    addEdge(graph,3,4,0);
    addEdge(graph,4,5,0);
    addEdge(graph,5,6,0);
    addEdge(graph,4,6,0);

    // vector<vector<int>> arr = {{1,1},{0,1},{3,3},{3,4}};
    // numOfIslands(arr, 4, 5);

    // vector<string> words1 = {"great"};
    // vector<string> words2 = {"great"};
    // vector<vector<string>> pairs = {};
    // cout << sentenceSimilarityII(words1, words2, pairs);
}

int main(int argc, char** argv) {
    solve();
}