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
// REDUNDANT CONNECTION II LEETCODE
bool isCycleDSU(vector<vector<int>> &edges, int blackList) {
    vector<int> par(edges.size() + 1, 0);
    vector<int> rank(edges.size() + 1, 1);

    for(int i = 0; i < edges.size() + 1; i++)
        par[i] = i;

    for(int i = 0; i < edges.size(); i++) {
        if(i == blackList)
            continue;
        int p1 = findPar(par, edges[i][0]);
        int p2 = findPar(par, edges[i][1]);

        if(p1 == p2)
            return true;

        else 
            merge(par, rank, p1, p2);
    }

    return false;
}

vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
    vector<int> indegrees(edges.size() + 1, -1);

    int blackList = -1;

    for(int i = 0; i < edges.size(); i++) {
        if(indegrees[edges[i][1]] != -1) {
            blackList = i;
            break;
        }
        indegrees[edges[i][1]] = i;
    }

    vector<int> par(edges.size() + 1, 0);
    vector<int> rank(edges.size() + 1, 1);

    for(int i = 0; i < edges.size() + 1; i++)
        par[i] = i;

    if(blackList != -1) {
        if(isCycleDSU(edges, blackList) == true) {
            return edges[indegrees[edges[blackList][1]]];
        }
        return edges[blackList];
    }

    for(int i = 0; i < edges.size() + 1; i++) {
        int p1 = findPar(par, edges[i][0]);
        int p2 = findPar(par, edges[i][1]);

        if(p1 == p2)
            return edges[i];

        else 
            merge(par, rank, p1, p2);
    }

    vector<int> arr = {};
    return {};
}

// QUESTION 2
// MINIMIZE MALWARE SPEED LEETCODE
vector<int> parents;
int find(int x) {
    if (x != parents[x])
        parents[x] = find(parents[x]);
    return parents[x];
}

void uni(int x, int y) {
    parents[find(x)] = find(y);
}

int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
    int n = graph.size();
    for (int i = 0; i < n; ++i) parents.push_back(i);
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (graph[i][j]) uni(i, j);
    vector<int> area(n, 0), malware(n, 0);
    for (int i = 0; i < n; ++i) area[find(i)]++;
    for (int i : initial) malware[find(i)]++;
    vector<int> res = {1, 0};
    for (int i : initial)
        res = min(res, {(malware[find(i)] == 1 ) * (-area[find(i)]), i});
    return res[1];
}

// QUESTION 3
// KRUSKALS ALGORITHM
void displayKruskalGraph(vector<vector<pii>> &g) {
    for (int i = 0; i < g.size(); i++) {
        cout << i << "-> ";
        for (pii e : g[i])
            cout << "(" << e.first << "," << e.second << "), ";
        cout << endl;
    }
}

void kruskalMST(vector<piii> &arr, int n, vector<int> &par, vector<int> &rank) {
    vector<vector<pii>> MST(n, vector<pii>());

    for (int i = 0; i < arr.size(); i++) {
        piii rp = arr[i];

        int p1 = findPar(par, rp.second.first);
        int p2 = findPar(par, rp.second.second);

        if (p1 != p2) {
            merge(par, rank, p1, p2);
            //ADDING EDGES TO THE NEW GRAPH
            MST[rp.second.first].push_back({rp.second.second, rp.first});
            MST[rp.second.second].push_back({rp.second.first, rp.first});
        }
    }

    displayKruskalGraph(MST);
}

void kruskalsAlgorithmMST()
{
    vector<piii> arr;
    int n = 7;

    arr.push_back({10, {0, 1}});
    arr.push_back({10, {0, 3}});
    arr.push_back({10, {1, 2}});
    arr.push_back({40, {2, 3}});
    arr.push_back({2, {3, 4}});
    arr.push_back({2, {4, 5}});
    arr.push_back({3, {4, 6}});
    arr.push_back({8, {5, 6}});

    sort(arr.begin(), arr.end(), [](piii a, piii b) {
        return a.first < b.first;
    });

    vector<int> par(n, 0);
    vector<int> rank(n, 1);
    for (int i = 0; i < n; i++)
        par[i] = i;

    kruskalMST(arr, n, par, rank);
}

// QUESTION 4
// CASTLE RUN GFG
// TO DETECT THE WHETHER THE GRAPH HAS A EULER CIRCUIT OR NOT
bool isCastleRunPossible(vector<vector<int>> &graph) {
    vector<int> indegrees(graph.size(), 0);

    for(int i = 0; i < graph.size(); i++) {
        for(int j = i+1; j < graph.size(); j++) {
            if(graph[i][j] ==1) {
                indegrees[i]++;
                indegrees[j]++;
            }
        }
    }

    int oddCount = 0;
    for(int i = 0; i < indegrees.size(); i++) {
        if(oddCount > 2)  
            return false;
        if(indegrees[i] % 2 != 0)
            oddCount++;
    }

    return true;
}

// QUESTION 5
// RECONSTRUCT ITINERARY
unordered_map<string,priority_queue<string,vector<string>,greater<string>>> map;
vector<string> ans;
void dfs(string s)
{
    auto &x=map[s];
    while(!x.empty())
    {
        string to=x.top();
        x.pop();
        dfs(to);
    }
    cout<<s<<endl;
    ans.push_back(s);
}

vector<string> findItinerary(vector<vector<string>>& tickets) {
    for(auto &x:tickets)
        map[x[0]].push(x[1]);
    dfs("JFK");
    reverse(ans.begin(),ans.end());
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

    kruskalsAlgorithmMST();
}

int main(int argc, char** argv) {
    solve();
}