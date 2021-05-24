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

// QUESTION 1
// NUMBER OF DISTINCT ISLANDS II LEETCODE/LINTCODE
int find(vector<int>& par, int x) {
    if(par[x] == x)
        return x;
    par[x] = find(par, par[x]);
    return par[x];
}

void merge(vector<int> &par, vector<int> &rank, int x, int y) {
    int lox = find(par,x);
    int loy = find(par,y);

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
            int x = arr[i][0] + dir[i][0];
            int y = arr[i][1] + dir[i][1]; 

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
        cout << count << " ";
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

    vector<vector<int>> arr = {{1,1},{0,1},{3,3},{3,4}};
    numOfIslands(arr, 4, 5);
}

int main(int argc, char** argv) {
    solve();
}