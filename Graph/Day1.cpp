#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
using namespace std;

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
// BFS IN A GRAPH
void bfsGraph(vector<vector<Edge*>> &graph, int src, vector<bool> &vis) {
    queue<int> que;
    que.push(src);

    while(que.size() > 0) {
        int size = que.size();
        while(size-->0) {
            int rp = que.front();
            que.pop();

            if(vis[rp])
                continue;

            cout << rp << " ";
            vis[rp] = true;
            for(Edge* e:graph[rp]) {
                if(!vis[e->v])
                    que.push(e->v);
            }
        }
    }
}

void bfs(vector<vector<Edge*>>&graph) {
    vector<bool> vis(graph.size(), false);
    for(int i = 0; i < vis.size(); i++) {
        if(vis[i] == false)
            bfsGraph(graph, i, vis);
    }
}

// QUESTION 2
// TO CHECK WHETHER A GRAPH IS BIPARTITE OR NOT LEETCODE
bool isGraphBipartite(vector<vector<Edge*>> &graph, int src, vector<int> &vis) {
    queue<int> que;
    que.push(src);
    int currCol = 0;

    while(que.size() > 0) {
        int size = que.size();
        while(size-->0) {
            int rp = que.front();
            que.pop();

            if(vis[rp] != -1) {
                if(vis[rp] != currCol) 
                    return false;
                continue;
            }
            
            vis[rp] = currCol;

            for(Edge* e: graph[rp]) {
                if(vis[e->v] == -1) 
                    que.push(e->v);
            }
        }
        currCol = (currCol + 1)%2;
    }

    return true;
}

void bipartite(vector<vector<Edge*>> &graph) {
    bool res = true;
    vector<int> vis(graph.size(), -1);
    for(int i = 0; i < vis.size(); i++) {
        if(vis[i] == -1)
            res = res && isGraphBipartite(graph, i, vis);
    }
    cout << "Is Graph Bipartite? " << boolalpha << res;
}

// QUESTION 3
// BUS ROUTES LEETCODE
int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
    unordered_map<int, vector<int>> m;

    for(int i = 0; i < routes.size(); i++) {
        for(int j = 0; j < routes[i].size(); j++) {
            if(m.find(routes[i][j]) == m.end()) {
                vector<int> t;
                m[routes[i][j]] = t;
            }
            m[routes[i][j]].push_back(i);
        }
    }

    unordered_map<int, bool> visBSN;
    vector<bool> visBN(routes.size(), false);

    queue<int> que;
    int level = 0;
    que.push(source);
    while(que.size() > 0) {
        int size = que.size();
        while(size-->0) {
            int rp = que.front();
            que.pop();

            if(rp == target)
                return level;

            for(int k:m[rp]) {
                if(!visBN[k]) {
                    visBN[k] = true;
                    for(int i = 0; i < routes[k].size(); i++) {
                        if(visBSN.find(routes[k][i]) == visBSN.end()) {
                            visBSN[routes[k][i]] = true;
                            que.push(routes[k][i]);
                        }
                    }
                }
            }
        }
        level++;
    }

    return -1;
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

    bfs(graph);
    bipartite(graph);
}

int main(int argc, char** argv) {
    solve();
}