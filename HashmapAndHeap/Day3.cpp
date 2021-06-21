#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

// QUESTION 1
// ARRAY OF DOUBLED PAIRS LEETCODE
bool canReorderDoubled(vector<int>& arr) {
    sort(arr.begin(),arr.end(),[](const int &a, const int &b)->bool {
        return abs(a) < abs(b);
    });
    unordered_map<int,int> m;
    for(int i=0;i<arr.size();i++) {
        m[arr[i]]++;
    }
    
    for(int i=0;i<arr.size();i++){
        if(m[arr[i]]==0) 
            continue;
        
        if(m[2*arr[i]]==0) 
            return false;
        
        m[2*arr[i]]--;
        m[arr[i]]--; 
    }
    return true;
}

// QUESTION 2
// RABBITS IN FOREST LEETCODE
int numRabbits(vector<int>& answers) {
    if(answers.size() == 0)
        return 0;
    unordered_map<int,int> freq;
    for(int i = 0; i < answers.size(); i++) {
        freq[answers[i]]++;
    }
    int ans = 0;
    
    for(auto k:freq) {
        if(k.first == 0)
            ans += k.second;
        else if(k.second <= k.first + 1)
            ans += k.first + 1;
        else {
            if(k.second % (k.first + 1) == 0) {
                ans += k.second;
            }
            
            else {
                int temp = (k.second / (k.first + 1)) + 1;
                ans += temp*(k.first + 1);
            }
        }
    }
    
    return ans;
}

// QUESTION 3
// LONGEST CONSECUTIVE SUBSEQUENCE LEETCODE


// QUESTION 4
// THE SKYLINE PROBLEM LEETCODE
vector<vector<int>> getSkyline(vector<vector<int>> &points) {
    vector<vector<int>> heights;
    for(int i = 0; i < points.size(); i++) {
        heights.push_back({points[i][0], points[i][2]});
        heights.push_back({points[i][1], -points[i][2]});
    }

    sort(heights.begin(), heights.end(), [](const vector<int>&a, const vector<int> &b) ->bool{
        if(a[0] == b[0])
            return a[1] > b[1];
        return a[0] < b[0];
    });
    
    multiset<int, greater<int>> pq;
    pq.insert(0);
    int prev = 0;
    vector<vector<int>> ans;

    for(int i = 0; i < heights.size(); i++) {
        if(heights[i][1] >= 0)
            pq.insert(heights[i][1]);

        else if(heights[i][1] < 0) 
            pq.erase(pq.find(-heights[i][1]));
        if(prev != *pq.begin()) {
            ans.push_back({heights[i][0], *pq.begin()});
            prev = *pq.begin();
        }
    }

    return ans;
}

// QUESTION 5
// TRICKY SORTING COST GFG
int costOfSorting(vector<int> &arr) {
    unordered_map<int,int> m;
    int maxAns = 0;
    for(int n:arr) {
        if(m.find(n - 1) != m.end()) {
            m[n] = m[n - 1] + 1;
        }

        else 
            m[n] = 1;
        
        maxAns = max(maxAns, m[n]);
    }

    return arr.size() - maxAns;
}

// QUESTION 6
// BRICK WALL LEETCODE
int leastBricks(vector<vector<int>>& w) {
    unordered_map<int,int> m;
    
    int maxAns = 0;
    for(int i = 0; i < w.size(); i++) {
        int sum = 0;
        for(int j = 0; j < w[i].size() - 1; j++) {
            sum += w[i][j];
            m[sum]++;
            maxAns = max(maxAns, m[sum]);
        }
    }
    
    return w.size() - maxAns;
}

// QUESTION 7
// GRID ILLUMINATION LEETCODE
vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
    unordered_map<int,int> col;
    unordered_map<int,int> row;
    unordered_map<int,int> diag1;
    unordered_map<int,int> diag2;
    unordered_map<string,int> cell;
    vector<vector<int>> dir = {{-1,-1},{-1,1},{1,-1},{1,1},{-1,0},{0,-1},{0,1},{1,0}};
    
    for(int i = 0; i < lamps.size(); i++) {
        
        int r = lamps[i][0];
        int c = lamps[i][1];
        string k = to_string(r) + '#' + to_string(c);
        if(cell.find(k) != cell.end())
            continue;
        col[c]++;
        row[r]++;
        diag1[r + c]++;
        diag2[r - c]++;
        cell[k]++;
    }
    vector<int> ans(queries.size(), 0);
    
    for(int i = 0; i < queries.size(); i++) {
        int r = queries[i][0];
        int c = queries[i][1];
        string k = to_string(r) + '#' + to_string(c);
        
        if(col[c] > 0 || row[r] > 0 || diag1[r + c] > 0 || diag2[r-c] > 0 || cell[k] > 0)
            ans[i] = 1;
        
        if(cell[k] > 0) {
            col[c]--;
            row[r]--;
            diag1[r+c]--;
            diag2[r-c]--;
            cell[k]--;
        }
        
        for(int d = 0; d < 8; d++) {
            int x = r + dir[d][0];
            int y = c + dir[d][1];
            string k_ = to_string(x) + '#' + to_string(y);
            
            if(x < 0 || y < 0 || x >= n || y >= n)
                continue;
            
            if(cell[k_] > 0) {
                col[y]--;
                row[x]--;
                diag1[x+y]--;
                diag2[x-y]--;
                cell[k_]--;
            }
        }
    }
    
    return ans;
}

// QUESTION 8
// ISLAND PERIMETER LEETCODE
int islandPerimeter(vector<vector<int>>& grid) {
    int ans = 0;
    vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};

    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[0].size(); j++) {
            if(grid[i][j] == 1) {
                ans += 4;
                for(int d = 0; d < 4; d++) {
                    int x = i + dir[d][0];
                    int y = j + dir[d][1];
                    if(x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 1)
                        ans--;
                }
            }
        }
    }

    return ans;
}

// QUESTION 9
// BULB SWITCHER LEETCODE
int bulbSwitch(int n) {
    return pow(n,0.5);
}

// QUESTION 10
// ISOMORPHIC STRINGS LEETCODE
bool isIsomorphic(string s, string t) {
    if(t.length() != s.length())
        return false;
    unordered_map<char,char> st;
    unordered_map<char, char> ts;
    
    for(int i = 0; i < s.length(); i++) {
        if(st.find(s[i]) == st.end()) {
            st[s[i]] = t[i];
        }
        
        if(ts.find(t[i]) == ts.end()) {
            ts[t[i]] = s[i];
        }
        
        if(st[s[i]] != t[i] || ts[t[i]] != s[i])
            return false;
    }
    
    return true;
}

// QUESTION 11 
// PAIRS OF NON COINCIDING POINTS GFG


int main(int argc,char** argv) {

}