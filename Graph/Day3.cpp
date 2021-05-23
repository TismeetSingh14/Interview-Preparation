#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
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
// WORD LADDER LEETCODE
int ladderLength(string beginWord, string target, vector<string>& s) {
    unordered_map<string, bool> m;
    for(int i = 0; i < s.size(); i++)
        m[s[i]] = false;
    queue<string> que;
    que.push(beginWord);
    int level = 1;

    while(que.size() != 0) {
        int size = que.size();
        while(size-->0) {
            string str = que.front();
            que.pop();
            
            for(int i = 0; i < str.length(); i++) {
                for(int j = 0; j < 26; j++) {
                    string temp = str.substr(0,i) + char(j + 'a') + str.substr(i + +1);
                    if(m.find(temp) != m.end() && temp != str && m[temp] != true) {
                        m[temp] = true;
                        if(temp == target) 
                            return level + 1;
                        que.push(temp);
                    } 
                }
            }
        }
        level++;
    }

    return 0;
}

// QUESTION 2
// SHORTEST BRIDGE LEETCODE
void dfs(vector<vector<int>> &grid, queue<pii> &que, int x, int y) {
    if(x >= grid.size() || y >= grid[0].size() || x < 0 || y < 0 || grid[x][y] == 0 || grid[x][y] == 2)
        return;

    grid[x][y] = 2;
    que.push({x,y});
    dfs(grid, que, x + 1, y);
    dfs(grid, que, x - 1, y);
    dfs(grid, que, x, y + 1);
    dfs(grid, que, x, y - 1);
}

int shortestBridge(vector<vector<int>> &grid) {
    int x = 0, y = 0;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] == 1) {
                x = i;
                y = j;
                break;
            }
        }
    }

    queue<pii> que;
    dfs(grid, que, x, y);
    int level = 0;
    vector<vector<int>> dir = {{0,1}, {1,0}, {-1,0}, {0,-1}};

    while(que.size() != 0) {
        int size = que.size();
        while(size-->0) {
            pii rp = que.front();
            que.pop();

            for(int i = 0; i < 4; i++) {
                int k1 = rp.first + dir[i][0];
                int k2 = rp.second + dir[i][1];

                if(k1 < grid.size() && k2 < grid[0].size() && k1 > -1 && k2 > -1 && grid[k1][k2] < 2) {
                    if(grid[k1][k2] == 1)
                        return level;
                    que.push({k1,k2});
                    grid[k1][k2] = 2;
                }
            }
        }
        level++;
    }

    return 1;
}

// QUESTION 3
// AS FAR FROM LAND AS POSSIBLE LEETCODE
int maxDistance(vector<vector<int>>& matrix) {
    queue<pair<int,int>> que;
    int water = 0;
    int land = 0;
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
            if(matrix[i][j] == 1) {
                que.push({i,j});
                land++;
            }
            
            if(matrix[i][j] == 0)
                water++;
        }
    }
    
    if(land == 0 || water == 0)
        return -1;
    
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
                if(x < 0 || y < 0 || x >= matrix.size() || y >= matrix[0].size() || matrix[x][y] == 1)
                    continue;
                matrix[x][y] = 1;
                que.push({x,y});
            }
        }
    }
    
    return level - 1;
}

// QUESTION 4
// SLIDING PUZZLE LEETCODE
int slidingPuzzle(vector<vector<int>>& board) {
    vector<vector<int>> swapPos = {{1,3},{0,2,4},{1,5},{0,4},{1,3,5},{2,4}};
    unordered_map<string, bool> m;

    string target = "123450";
    string s = "";
    int idx = -1;
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            s = s + to_string(board[i][j]);
            if(board[i][j] == 0) 
                idx = i*3 + j;
        }
    }

    if(s == target)
        return 0;
    queue<pair<string, int>> que;
    que.push({s, idx});
    m[s] = true;
    int level = 0;

    while(que.size() != 0) {
        int size = que.size();
        while(size-->0) {

            pair<string, int> rp = que.front();
            que.pop();

            for(int i = 0; i < swapPos[rp.second].size(); i++) {
                string temp = rp.first;
                swap(temp[swapPos[rp.second][i]],temp[rp.second]);
                if(temp == target)
                    return level + 1;
                if(m.find(temp) == m.end()) {
                    m[temp] = true;
                    que.push({temp, swapPos[rp.second][i]});
                }
            }
        }
        level++;
    }

    return -1;  
}

// QUESTION 5
// BELLMAN FORD ALGORITHM
void bellmanFordAlgorithm(vector<vector<Edge*>> &graph ,int src) {
    vector<int> dis(graph.size(), 1e9);
    dis[src] = 0;

    for (int i = 0; i < graph.size() - 1; i++) {
        for (int j = 0; j < graph.size(); j++) {
            for (Edge *e : graph[j]) {
                int x = j;
                int y = e->v;
                int wgt = e->w;
                if (dis[x] != 1e9 && dis[x] + wgt < dis[y])
                    dis[y] = dis[x] + wgt;
            }
        }
    }

    for (int i = 0; i < graph.size(); i++) {
        for (Edge *e : graph[i]) {
            int x = i;
            int y = e->v;
            int wgt = e->w;
            if (dis[x] != 1e9 && dis[x] + wgt < dis[y]) {
                cout << "NEGATIVE CYCLE DETECTED" << endl;
                break;
            }
        }
    }

    cout << "DISTANCES FROM SOURCE:";
    for (int i = 0; i < graph.size(); i++)
        cout << dis[i] << " ";
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

    bellmanFordAlgorithm(graph, 0);

}
int main(int argc, char** argv) {

}