#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
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
// COLORING THE BORDER LEETCODE
void dfsColor(vector<vector<int>> &grid, vector<vector<bool>> &vis, int sr, int sc, int newCol, int oldCol) {
    if(sr < 0 || sc < 0 || sr == grid.size() || sc == grid[0].size() || grid[sr][sc] != oldCol || vis[sr][sc])
        return;
    vis[sr][sc] = true;
    bool isBorder = false;
    if(sr == 0 || sc == 0 || sr == grid.size() - 1 || sc == grid[0].size() - 1 || grid[sr - 1][sc] != oldCol || grid[sr][sc + 1] != oldCol || grid[sr + 1][sc] != oldCol || grid[sr][sc - 1] != oldCol)
        isBorder = true;
    
    dfsColor(grid, vis, sr - 1, sc, newCol, oldCol);
    dfsColor(grid, vis, sr, sc + 1, newCol, oldCol);
    dfsColor(grid, vis, sr + 1, sc, newCol, oldCol);
    dfsColor(grid, vis, sr, sc - 1, newCol, oldCol);

    if(isBorder == true) 
        grid[sr][sc] = newCol;
    
}

vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int newCol) {
    if(grid[r0][c0] == newCol)
        return grid;
    vector<vector<bool>> vis(grid.size(), vector<bool>(grid[0].size(), false));
    dfsColor(grid, vis, r0, c0, newCol, grid[r0][c0]);
    return grid;
}

// QUESTION 2
// ROTTING ORANGES LEETCODE
int orangesRotting(vector<vector<int>>& grid) {
    queue<pair<int,int>> que;
    int fresh = 0;
    
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] == 2)
                que.push({i,j});
            
            else if(grid[i][j] == 1)
                fresh++;
        }
    }
    if(fresh == 0) 
        return 0;
    int level = 0;
    while(que.size() != 0) {
        int size = que.size();
        while(size-->0) {
            vector<vector<int>> dir = {{0,-1},{-1,0},{0,1},{1,0}};
            pair<int, int> p = que.front();
            que.pop();
            
            for(int i = 0; i < 4; i++) {
                int x = p.first + dir[i][0];
                int y = p.second + dir[i][1];
                
                if(x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] == 2 || grid[x][y] == 0)
                    continue;
                grid[x][y] = 2;
                fresh--;
                que.push({x,y});
                
            }
        }
        level++;
    }
    
    return fresh == 0? level - 1 : -1;
}

// QUESTION 3
// TOPOLOGICAL SORTING
void topologicalSort(vector<vector<Edge*>> &graph, vector<int> &stack, int src, vector<bool> &vis) {
    vis[src] = true;

    for(Edge* e:graph[src]) {
        if(!vis[e->v]) 
            topologicalSort(graph, stack, e->v, vis);
    }

    stack.push_back(src);
}

void topologicalMain(vector<vector<Edge*>> &graph) {
    vector<bool> vis(graph.size(), false);
    vector<int> ans;
    for(int i = 0; i < graph.size(); i++) {
        if(vis[i] == false)
            topologicalSort(graph, ans, i, vis);
    }

    for(int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << " ";
}

// QUESTION 4 
// KAHNS ALGORITHM
void kahnsAlgorithm(vector<vector<Edge*>> &graph) {
    vector<int> indegrees(graph.size(), 0);

    for(int i = 0; i < graph.size(); i++) {
        for(Edge* e: graph[i]) {
            indegrees[e->v]++;
        }
    } 

    queue<int> que;
    vector<int> ans;
    for(int i = 0; i < indegrees.size();i++) {
        if(indegrees[i] == 0) 
            que.push(i);
    }

    while(que.size() != 0) {
        int size = que.size();
        while(size-->0) {
            int rp = que.front();
            que.pop();
            ans.push_back(rp);

            for(Edge* e:graph[rp]) {
                indegrees[e->v]--;
                if(indegrees[e->v] == 0)
                    que.push(e->v);
            }
        }
    }

    for(int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
}

// QUESTION 5
// COURSE SCHEDULE II LEETCODE
bool dfs(vector<vector<int>> &graph, vector<bool>&vis, vector<bool>&cycle , int src, vector<int> &ans) {
    vis[src] = true;
    cycle[src] = true;
    bool res = false;
    for(int e:graph[src]) {
        if(!vis[e])
            res = res || dfs(graph, vis, cycle, e, ans);
        else if(cycle[e] == true)
            return true;
            
    }
    
    cycle[src] = false;
    ans.push_back(src);
    return res;
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses, vector<int>());
    
    for(int i = 0; i < prerequisites.size(); i++) {
        graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }
    
    vector<bool> vis(graph.size(), false);
    vector<bool> cycle(graph.size(), false);
    vector<int> ans;
    bool res = false;
    
    for(int i = 0; i < graph.size(); i++) {
        if(vis[i] == false) {
            res = res || dfs(graph, vis, cycle, i, ans);
        }
    }
    
    for(int i = 0, j = ans.size() - 1; i <= j; i++, j--) {
        swap(ans[i],ans[j]);
    }
    
    return !res? ans : vector<int>();
}

// QUESTION 6
// ARTICULATION POINT
void dfsAP(vector<vector<Edge*>> &graph, vector<int> &disc, vector<int> &low, int src, vector<bool> &vis, vector<bool> &ans, int osrc, vector<int> &par, int &count) {

    static int discTime = 0;
    vis[src] = true;
    disc[src] = low[src] = discTime;
    discTime++;

    for(Edge* e:graph[src]) {
        if(par[src] == e->v)
            continue;

        if(vis[e->v] == true) {
            low[src] = min(low[src], disc[e->v]);
        }

        else {
            par[e->v] = src;
            if(src == osrc)
                count++;
            dfsAP(graph, disc, low, e->v, vis, ans, osrc, par, count);
            if(low[e->v] >= disc[src]) 
                ans[src] = true;
            low[src] = min(low[src], low[e->v]);
        }
    }
}

void articulationPoint(vector<vector<Edge*>> &graph) {
    vector<bool> vis(graph.size(), 0);
    vector<int> disc(graph.size(), 0);
    vector<int> low(graph.size(), 0);
    vector<int> par(graph.size(), -1);
    vector<bool> ans(graph.size(), false);
    int count = 0;
    for(int i = 0; i < graph.size(); i++) {
        if(vis[i] == false) {
            dfsAP(graph, disc, low, i, vis, ans, i, par, count);
            if(count < 2) 
                ans[i] = false;
        }
    }

    for(int i = 0; i < ans.size(); i++) 
        if(ans[i])
            cout << i << " ";
}

// QUESTION 7
// DOCTOR STRANGE GFG
void doctorAP(vector<vector<int>> &graph, vector<int> &disc, vector<int> &low, int src, vector<bool> &vis, int osrc, vector<int> &par, int &count, vector<bool> &ans) {
    static int discTime = 0;
    vis[src] = true;
    disc[src] = low[src] = discTime;
    discTime++;

    for(int v:graph[src]) {
        if(par[src] == v)
            continue;

        if(vis[v] == true) {
            low[src] = min(low[src], disc[v]);
        }

        else {
            par[v] = src;
            if(src == osrc)
                count++;
            doctorAP(graph, disc, low, v, vis, osrc, par, count, ans);
            if(low[v] >= disc[src])
                ans[src] = true;
            low[src] = min(low[src], low[v]);
        }
    }
}

int doctorStrange(vector<vector<int>> &edges, int n, int m) {
    if(n < 3)
        return 0;

    vector<vector<int>> graph(n, vector<int>());

    for(int i = 0; i < m; i++) {
        graph[edges[i][0] - 1].push_back(edges[i][1] - 1);
        graph[edges[i][1] - 1].push_back(edges[i][0] - 1);
    }

    vector<bool> vis(graph.size(), 0);
    vector<int> disc(graph.size(), 0);
    vector<int> low(graph.size(), 0);
    vector<int> par(graph.size(), -1);
    vector<bool> ans(graph.size(), false);
    int count = 0;
    int res = 0;

    doctorAP(graph, disc, low, edges[0][0] - 1, vis, edges[0][0] - 1, par, count, ans);
    if(count < 2)
        ans[edges[0][0] - 1] = false;

    for(int i = 0; i < ans.size(); i++) {
        if(ans[i])
            res++;
    }
    return res;
}

void solve() {
    int n = 8;
    vector<vector<Edge*>> graph(n,vector<Edge*>());
    addEdge(graph,0,1,0);
    addEdge(graph,1,2,0);
    addEdge(graph,2,3,0);
    addEdge(graph,0,3,0);
    addEdge(graph,3,4,0);
    addEdge(graph,4,5,0);
    addEdge(graph,5,6,0);
    addEdge(graph,7,6,0);
    addEdge(graph,7,5,0);

    // topologicalMain(graph);
    // articulationPoint(graph);
    vector<vector<int>> a = {{1,2},{2,3},{2,4},{2,5},{3,6},{3,7}};
    cout << doctorStrange(a, 7 ,6);
}

int main(int argc,char** argv) {
    solve();
}