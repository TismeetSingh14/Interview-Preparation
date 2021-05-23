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
// DIJKSTRA'S ALGORITHM USING QUEUE
// ALSO KNOWN AS 0-1 BFS


// QUESTION 2
// OPTIMIZE WATER DISTRIBUTION IN VILLAGE LEETCODE/LINTCODE

// QUESTION 3
// DFS
void dfs(vector<vector<Edge*>> &graph, int src, vector<bool> &vis) {
    vis[src] = true;

    for(Edge* e: graph[src]) {
        if(vis[e->v] == false)
            dfs(graph, e->v, vis);
    }
}

// QUESTION 4
// EVALUATE DIVISION LEETCODE

// QUESTION 5
// STRONGLY CONNECTED COMPONENTS (KOSARAJU'S ALGORTIHM) GFG
void graphTranspose(vector<vector<Edge*>> &graph, vector<vector<Edge*>> &graph_transpose) {
    for (int i = 0; i < graph.size(); i++) {
        for (Edge *e : graph[i])
            graph_transpose[e->v].push_back(new Edge(i, e->w));
    }
}

void topologicalSortDfsFunction(int src, vector<bool> &vis, vector<int> &AnsStack, vector<vector<Edge*>> &graph) {
    vis[src] = true;

    for (Edge *e : graph[src]) {
        if (!vis[e->v])
            topologicalSortDfsFunction(e->v, vis, AnsStack, graph);
    }

    AnsStack.push_back(src);
}

vector<int> topologicalSortFunction(vector<vector<Edge*>> &graph) {
    vector<bool> vis(graph.size(), false);
    vector<int> AnsStack;
    for (int i = 0; i < graph.size(); i++) {
        if (!vis[i])
            topologicalSortDfsFunction(i, vis, AnsStack, graph);
    }

    return AnsStack;
}

void DfsFunction(int src, vector<bool> &vis, vector<vector<Edge*>> &graph_transpose) {
    vis[src] = true;
    cout << src << " ";

    for (Edge *e : graph_transpose[src]) {
        if (!vis[e->v])
            DfsFunction(e->v, vis, graph_transpose);
    }
}

int kosarajusAlgorithm(vector<vector<Edge*>> &graph) {
    vector<int> stack = topologicalSortFunction(graph);
    vector<bool> vis(graph.size(), 0);
    vector<vector<Edge*>> graph_transpose(graph.size(), vector<Edge*>());

    graphTranspose(graph, graph_transpose);
    int count = 0;

    while (stack.size() != 0) {
        int src = stack.back();
        stack.pop_back();

        if (vis[src] == false) {
            DfsFunction(src, vis, graph_transpose);
            count++;
            cout << endl;
        }
    }

    return count;
}

// QUESTION 6
// MOTHER VERTEX GFG
void topologicalSort(vector<vector<Edge*>> &graph, int src, vector<int> &ans, vector<bool> &vis) {
    vis[src] = true;

    for(Edge* e: graph[src]) {
        if(vis[e->v] == false)
            topologicalSort(graph, e->v, ans, vis);
    }

    ans.push_back(src);
}

void dfsCheckIfVisAll(vector<vector<Edge*>> &graph, int src, vector<bool> &vis) {
    vis[src] = true;

    for(Edge* e: graph[src]) {
        if(!vis[e->v])
            dfsCheckIfVisAll(graph, e->v, vis);
    }
}

int motherVertex(vector<vector<Edge*>> &graph) {
    vector<bool> vis(graph.size(), false);
    vector<int> ans;
    for(int i = 0; i < graph.size(); i++) {
        if(vis[i] == false) 
            topologicalSort(graph, i, ans, vis);
    }

    vector<bool> visDFS(graph.size(), false);
    dfsCheckIfVisAll(graph, ans[ans.size() - 1], visDFS);

    for(int i = 0; i < visDFS.size(); i++) {
        if(visDFS[i] == false)
            return -1;
    }

    return ans[ans.size() - 1];
}

// QUESTION 7
// NUBER OF ENCLAVES LEETCODE
void dfsNOE(vector<vector<int>> &board, int sr, int sc) {
    if(sr < 0 || sc < 0 || sr >= board.size() || sc >= board[0].size() || board[sr][sc] == 0)
        return;
    
    board[sr][sc] = 0;
    dfsNOE(board, sr + 1, sc);
    dfsNOE(board, sr, sc + 1);
    dfsNOE(board, sr - 1, sc);
    dfsNOE(board, sr, sc - 1);
}

int numEnclaves(vector<vector<int>>& board) {
    int area = 0;
    
    for(int i = 0; i < board[0].size(); i++) {
        if(board[0][i] == 1) 
            dfsNOE(board, 0, i);
        if(board[board.size() - 1][i] == 1)
            dfsNOE(board, board.size() - 1, i);
    }
    
    for(int i = 0; i < board.size(); i++) {
        if(board[i][0] == 1) 
            dfsNOE(board, i, 0);
        if(board[i][board[0].size() - 1] == 1)
            dfsNOE(board, i, board[0].size() - 1);
    }

    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            if(board[i][j] == 1)
                area+=1;
        }
    }
    
    return area;
}

// QUESTION 8
// 01 MATRIX LEETCODE
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
    queue<pair<int,int>> que;
    vector<vector<int>> ans(matrix.size(), vector<int>(matrix[0].size(), 0));
    
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
            if(matrix[i][j] == 0) {
                que.push({i,j});
            }
        }
    }
    
    int level = 0;
    vector<vector<int>> dir = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    while(que.size() != 0) {
        int size = que.size();
        level++;
        while(size-->0) {
            pair<int, int> p = que.front();
            que.pop();
            
            
            for(int i = 0; i < 4; i++) {
                int x = p.first + dir[i][0];
                int y = p.second + dir[i][1];
                if(x < 0 || y < 0 || x >= matrix.size() || y >= matrix[0].size() || matrix[x][y] == 0)
                    continue;
                matrix[x][y] = 0;
                ans[x][y] = level;
                que.push({x,y});
            }
        }
    }
    return ans;
}

// QUESTION 9
// NUMBER OF ISLANDS LEETCODE
int dfsNOI(vector<vector<char>> &grid, int i, int j) {
    if(i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] == '0') {
        return 0;
    }
    
    
    grid[i][j] = '0';
    dfsNOI(grid, i + 1, j) ;dfsNOI(grid, i , j + 1) ; dfsNOI(grid, i - 1, j) ;dfsNOI(grid, i, j -1) + 1;
    return 1;
}

int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] == '1') {
                ans += dfsNOI(grid, i, j);
            }
        }
    }
    return ans;
}

// QUESTION 10
// NUMBER OF DISTINCT ISLANDS LEETCODE


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