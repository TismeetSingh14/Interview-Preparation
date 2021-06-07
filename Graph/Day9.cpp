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