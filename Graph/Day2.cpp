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
// CHEF AND REVERSING CODECHEF
// DJIKATRA'S ALGORITHM USING QUEUE
// ALSO KNOWN AS 0-1 BFS
int minCostToReverseEdges(vector<vector<Edge*>> &graph, int src, int des) {
    queue<int> que;
}

void reverseEdges(vector<vector<int>> &edges) {
    int start = 1;
    int end = edges.size();
    vector<vector<Edge*>> graph(edges.size(), vector<Edge*>());

    for(int i = 0; i < edges.size(); i++) {
        graph[edges[i][0]].push_back(new Edge(graph[edges[i][1]],0));
        graph[edges[i][1]].push_back(new Edge(graph[edges[i][0]],1));
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
    solve();
}