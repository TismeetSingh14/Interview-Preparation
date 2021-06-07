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

// QUESTION 5
// SWIM IN RISING WATER LEETCODE
int swimInWater(vector<vector<int>>& h) {
    priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> que;
    int m = h.size();
    int n = h[0].size();
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    vector<vector<int>> dir = {{-1,0},{0,-1},{1,0},{0,1}};
    que.push({h[0][0],{0,0}});
    while(que.size() != 0) {
        
        pair<int,pair<int,int>> p = que.top();
        que.pop();
        int cx = p.second.first;
        int cy = p.second.second;
        if(vis[cx][cy] == true)
            continue;
        if(cx == m -1 && cy == n - 1)
            return p.first;
        
        vis[cx][cy] = true;
        
        for(int i = 0; i < 4; i++) {
            int x = cx + dir[i][0];
            int y = cy + dir[i][1];
            
            if(x >= 0 && y >= 0 && x < m && y < n) {
                int maxDiff = max(h[x][y], p.first);
                que.push({maxDiff, {x,y}});
            }
        }
    }
    
    return -1;
}

// QUESTION 7
// REMOVE MAX NUMBER OF EDGES TO KEEP GRAPH FULLY TRAVERSABLE LEETCODE
int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
    sort(edges.begin(), edges.end());
    vector<int> parentA(n, 0);
    vector<int> rankA(n, 0);
    vector<int> parentB(n, 0);
    vector<int> rankB(n, 0);
    
    int count = 0;
    for(int i = 0; i < n; i++) {
        parentA[i] = i;
        parentB[i] = i;
    }
    
    int n1 = n;
    int n2 = n;
    
    for(int i = edges.size() - 1; i >= 0; i--) {
        edges[i][1]--;
        edges[i][2]--;
        
        if(edges[i][0] == 3) {
            int k1 = findPar(parentA, edges[i][1]);
            int k2 = findPar(parentA, edges[i][2]);
            int l1 = findPar(parentB, edges[i][1]);
            int l2 = findPar(parentB, edges[i][2]);
            if(k1 == k2 && l1 == l2)
                count++;
            
            if(k1 != k2) {
                merge(parentA, rankA, edges[i][1], edges[i][2]);
                n1--;
            }
            
            if(l1 != l2) {
                merge(parentB, rankB, edges[i][1], edges[i][2]);
                n2--;
            }
        }
        
        else if(edges[i][0] == 1) {
            if(findPar(parentA, edges[i][1]) == findPar(parentA, edges[i][2]))
                count++;
            else { 
                merge(parentA, rankA, edges[i][1], edges[i][2]);
                n1--;
            }
        }
        
        else {
            if(findPar(parentB, edges[i][1]) == findPar(parentB, edges[i][2]))
                count++;
            else { 
                merge(parentB, rankB, edges[i][1], edges[i][2]);
                n2--;
            }
        }
    }
    
    if(n1 != 1 || n2 != 1)
        return -1;
    
    return count;
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
}

int main(int argc, char** argv) {

}