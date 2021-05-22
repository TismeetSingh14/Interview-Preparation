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
void dfs(vector<vector<int>> &grid, vector<vector<bool>> &vis, int sr, int sc) {
    if(sr < 0 || sc < 0 || sr == grid.size() || sc == grid[0].size())
        return;
    
    vis[sr][sc] = true;
    dfs(grid, vis, sr - 1, sc);
    dfs(grid, vis, sr, sc + 1);
    dfs(grid, vis, sr + 1, sc);
    dfs(grid, vis, sr, sc - 1);
}
void coloringTheBorder(vector<vector<int>> &grid, int r0, int c0, int newCol) {
    vector<vector<bool>> vis(grid.size(), vector<bool>(grid[0].size(), false));

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
// RECONSTRUCT ITINERARY

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

    topologicalMain(graph);
}

int main(int argc,char** argv) {

}