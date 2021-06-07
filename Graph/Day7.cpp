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
#define piii pair<int, pair<int, int>>

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
// MOST STONES REMOVED WITH SAME ROW OR COLUMN LEETCODE
int findParMap(unordered_map<int,int>& par, int x) {
    if(par[x] == x)
        return x;
    par[x] = findParMap(par, par[x]);
    return par[x];
}

void mergeMap(unordered_map<int,int> &par, unordered_map<int,int> &rank, int x, int y) {
    int lox = findParMap(par,x);
    int loy = findParMap(par,y);

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

int removeStones(vector<vector<int>>& stones) {
    unordered_map<int, int> parent;
    unordered_map<int,int> rank;

    int count = 0;
    for(int i = 0; i < stones.size(); i++) {

        if(parent.find(stones[i][0]) == parent.end()) {
            parent[stones[i][0]] = stones[i][0];
            rank[stones[i][0]] = 0;
            count++;
        }
        if(parent.find(~stones[i][1]) == parent.end()) {
            parent[~stones[i][1]] = ~stones[i][1];
            rank[~stones[i][1]] = 0;
            count++;
        }
        
        if(findParMap(parent,stones[i][0]) != findParMap(parent,~stones[i][1])) {
        mergeMap(parent, rank, stones[i][0], ~stones[i][1]);
        count--;
        }
    }

    return stones.size() - count;
}

// QUESTION 2
// FORD FULKERSON AND EDMONDS KARP ALGORITHM FOR MAXIMUM NETWORK FLOW
// FORD FULKERSON ALGORITHM
// 1. DFS -> TO FIND A PATH (NON-ZERO WEIGHT)
// 2. MIN WEIGHT EDGE(X) INA BOVE PATH --> ANS += X
// 3. SUBTRACT X FROM EVERY EDGE IN THE ABOVE PATH
// 4. ADD X WEIGHT BACK EDGE TO EVERY EDGE IN THE ABOVE PATH
// BACK EDGE HELPS IN REORDERING OF EDGES
// COMPLEXITY =>
vector<int> bfsMF(vector<vector<int>> &graph, int src, int sink) {
    queue<int> que;
    que.push(src);
    vector<int> parent(graph.size(), -1);
    vector<bool> vis(graph.size(), false);
    vis[src] = true;
    while(que.size() != 0) {
        int u = que.front();
        que.pop();

        for(int i = 0; i < graph[u].size(); i++) {
            if(vis[i] == false && graph[u][i] > 0) {
                if(i == sink) {
                    parent[i] = u;
                    return parent;
                }
                que.push(i);
                parent[i] = u;
                vis[i] = true;
            }
        }
    }

    return parent;
}

int maximumFlow(vector<vector<int>> &graph, int src, int sink) {

    int ans = 0;
    while(true) {
        vector<int> par = bfsMF(graph, src, sink);
        if(par[sink] == -1)
            break;
        int minEdge = 1e9;
        for(int i = sink; i != src; i = par[i]) {
            int u = par[i];
            minEdge = min(minEdge, graph[u][i]);
        }

        for(int i = sink; i != src; i = par[i]) {
            int u = par[i];
            graph[u][i] -= minEdge;
            graph[i][u] += minEdge;
        }

        ans += minEdge;
    }

    return ans;
}

void maxFlowSolve() {
    vector<vector<int>> graph = {{0,16,13,0,0,0},
                                {0,0,10,12,0,0},
                                {0,4,0,0,14,0},
                                {0,0,9,0,0,20},
                                {0,0,0,7,0,4},
                                {0,0,0,0,0,0}};
    cout << maximumFlow(graph, 0, 5);
}

// QUESTION 3
// MAXIMUM BIPARTITE MATCHING GFG
// FOR ONE PERSON TO ONE JOB CONNECT PERSON AND JOBS WITH WEIGHT 1, SOURCE TO PERSON WITH WEIGHT 1, AND JOB TO SINK WITH WEIGHT 1
// FOR ONE PERSON TO N JOBS CONNECT PERSON AND JOBS WITH WEIGHT 1, SOURCE TO PERSON WITH WEIGHT N, AND JOB TO SINK WITH WEIGHT 1
// FOR N PERSON TO ONE JOB CONNECT PERSON AND JOBS WITH WEIGHT 1, SOURCE TO PERSON WITH WEIGHT 1, AND JOB TO SINK WITH WEIGHT N

// QUESTION 4
// MINIMUM NUMBER OF SWAPS REQUIRED TO SORT AN ARRAY
int minSwaps(vector<int> &arr) {
    vector<pair<int,int>> k(arr.size());
    for(int i = 0; i < k.size(); i++) {
        k[i] = {arr[i], i};
    }
    sort(k.begin(), k.end());
    vector<bool> vis(k.size(), false);
    int ans = 0;
    int i = 0;
    while(i < arr.size()) {
        if(k[i].second != i && vis[i] == false) {
            int j = i;
            int cycle = 0;
            while(vis[j] != true) {
                vis[j] = true;
                cycle += 1;
                j = k[j].second;
            }
            
            ans += cycle - 1;
        } 
        i++;
    }

    return ans;
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

    // maxFlowSolve();
    vector<int> arr = {4,5,2,1,3};
    cout << minSwaps(arr);

}

int main(int argc, char** argv) {
    solve();
}