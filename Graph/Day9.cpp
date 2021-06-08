#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <unordered_set>
#include <cmath>
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
// GRAPH CONNECTIVITY WITH THRESHOLD LEETCODE
class UnionFind {
    vector<int> parent, size;
public:
    UnionFind(int n) {
        parent.resize(n); size.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i; size[i] = 1;
        }
    }
    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }
    bool Union(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return false;
        if (size[pu] > size[pv]) {
            size[pu] += size[pv];
            parent[pv] = pu;
        } else {
            size[pv] += size[pu];
            parent[pu] = pv;
        }
        return true;
    }
};

vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
    UnionFind uf(n+1);
    for (int i = 1; i <= n; i++)
        for (int j = i * 2; j <= n; j += i)
            if (i > threshold)
                uf.Union(i, j);
    vector<bool> ans;
    for (auto& q : queries) {
        int pa = uf.find(q[0]);
        int pb = uf.find(q[1]);
        ans.push_back(pa == pb);
    }
    return ans;
}

// QUESTION 2
// SMALLEST STRING WITH SWAPS LEETCODE
vector<int> idx;                                                 
vector<bool> vis;
vector<vector<int>> graph;
string compStr;                                                 
void dfs(string &s,int src) {
    vis[src]=true;
    idx.push_back(src);
    compStr+=s[src];
    for(int &i:graph[src])
        if(!vis[i])
            dfs(s,i);
}

string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    graph.resize(s.length());
    vis.resize(s.length(),false);
    for(vector<int> &v:pairs) {                             
        graph[v[0]].push_back(v[1]);
        graph[v[1]].push_back(v[0]); 
    }
    
    for(int i=0;i<s.length();i++) {
        if(!vis[i]) {
            compStr="";                              
            idx.clear();                            
            dfs(s,i);
            sort(compStr.begin(),compStr.end());                   
            sort(idx.begin(),idx.end());                                 
            for(int i=0;i<idx.size();i++)          
                s[idx[i]]=compStr[i];
        }
    }

    return s;
}

// QUESTION 3
// CRACKING THE SAFE LEETCODE
string myAns = "";
unordered_set<string> visSet;
bool traverse(int k, int maxEle, string &ans, string &src) {
    if(visSet.size() == maxEle) {
        myAns = ans;
        return true;
    }
    
    bool res = false;
    
    for(int i = 0; i < k; i++) {
        string k1 = src.substr(1) + to_string(i);
        if(visSet.find(k1) == visSet.end()) {
            visSet.insert(k1);
            ans = ans + to_string(i);
            res = res || traverse(k, maxEle, ans, k1);
            visSet.erase(k1);
            ans.pop_back();
        }
    }
    
    return res;
}

string crackSafe(int n, int k) {
    string ans = string(n, '0');
    int maxEle = pow(k, n);
    visSet.insert(ans);
    traverse(k ,maxEle, ans, ans);
    return myAns;
}

// QUESTION 4
// FIND EVENTUAL SAFE STATES LEETCODE 
bool dfs(vector<vector<int>> &graph, vector<int> &vis, int src) {
    if(vis[src] != -1) {
        if(vis[src] == 0)
            return true;
        else 
            return false;
    }
    
    vis[src] = 1;
    for(int i: graph[src]) {
        bool temp = dfs(graph, vis, i);
        if(temp == false)
            return false;
    }
    vis[src] = 0;
    return true;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    vector<int> vis(graph.size(), -1);
    vector<int> a;
    for(int i = 0; i < graph.size(); i++) {
        if(vis[i] == 0) {
            a.push_back(i);
            continue;
        }
        if(vis[i] == -1) {
            bool ans = dfs(graph, vis, i);
            if(ans == true)
                a.push_back(i); 
        }
    }
    
    return a;
}

// QUESTION 5
// CHEAPEST FLIGHT WITHIN K STOPS LEETCODE
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<vector<pair<int,int>>> graph(n, vector<pair<int,int>>());
    for(int i = 0; i < flights.size(); i++) {
        graph[flights[i][0]].push_back({flights[i][1], flights[i][2]});
    }
    
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq; 

    pq.push({0,{src, 0}});
    while(pq.size() != 0) {
        pair<int,pair<int,int>> rp = pq.top();
        pq.pop();
        if(rp.second.first == dst) {
            return rp.first;
        }
        
        if(rp.second.second > k)
            continue;

        for(pair<int,int> p:graph[rp.second.first]) {
                pq.push({rp.first + p.second, {p.first, rp.second.second + 1}});
        }
    }
    
    return -1;
}

// QUESTION 6
// FLOYD WARSHALL ALGORITHM
void floydWarshallAlgorithm(vector<piii> &arr) {
    vector<vector<int>> dist(arr.size(),vector<int>(arr.size(),1e9));

    for(int i = 0; i < dist.size(); i++)
        dist[i][i] = 0;

    for(piii e:arr) {
        dist[e.second.first][e.second.second] = e.first;
        dist[e.second.second][e.second.first] = e.first;
    } 

    for(int k = 0; k < dist.size(); k++) {
        for(int i = 0; i < dist.size(); i++) {
            for(int j = 0; j < dist.size(); j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    } 

    for(int i = 0; i < dist.size(); i++) {
        for(int j = 0; j < dist.size(); j++)
            cout << dist[i][j] << " ";
        cout << endl;
    }  
}

void floydWarshallAlgorithm() {
    vector<piii> arr;
    arr.push_back({10, {0, 1}});
    arr.push_back({10, {0, 3}});
    arr.push_back({10, {1, 2}});
    arr.push_back({40, {2, 3}});
    floydWarshallAlgorithm(arr);
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

    floydWarshallAlgorithm();
}

int main(int argc, char** argv) {

}