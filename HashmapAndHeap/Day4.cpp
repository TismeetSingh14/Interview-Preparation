#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;
#define ppi pair<int,pair<int,int>>

// QUESTION 1
// TRAPPING RAIN WATER LEETCODE
// SPACE O(1)
int trap(vector<int> &height) {
    int lmax = 0;
    int rmax = 0;
    int ans = 0;
    int i = 0;
    int j = height.size() - 1;
    while(i < j) {
        lmax = max(lmax, height[i]);
        rmax = max(rmax, height[j]);

        if(lmax < rmax) {
            ans += lmax - height[i];
            i++;
        }
        else {
            ans += rmax - height[j];
            j--;
        }
    } 
    return ans;
}

// QUESTION 2
// TRAPPING RAIN WATER II LEETCODE
int trapRainWater(vector<vector<int>>& heightMap) {
    priority_queue<ppi, vector<ppi> ,greater<ppi>> pq;
    int n = heightMap.size();
    int m = heightMap[0].size();
    vector<vector<bool>> vis(n, vector<bool> (m,false));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                vis[i][j] = true;
                pq.push({heightMap[i][j],{i,j}});
            }
        }
    }

    vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};
    int res = 0;

    while(pq.size() != 0) {
        ppi rp = pq.top();
        pq.pop();


        for(int i = 0; i < 4; i++) {
            int x = rp.second.first + dir[i][0];
            int y = rp.second.second + dir[i][1];

            if(x < 0 || y < 0 || x >= n || y >= m || vis[x][y] == true)
                continue;
            res += max(0, rp.first - heightMap[x][y]);
            pq.push({max(rp.first, heightMap[x][y]),{x,y}});
            vis[x][y] = true;
        }
    }

    return res;   
}

// QUESTION 3
// COUNT PAIRS WHOSE SUM IS DIVISIBLE BY K GFG
int divisiblePairs(vector<int> &arr, int k) {
    unordered_map<int,int> m;
    int ans = 0;

    for(int i = 0; i < arr.size(); i++) {
        int val = arr[i]%k;

        if(val == 0)
            ans += m[val];

        else 
            ans += m[k - val];

        m[val]++;
    }

    return ans;
}

// QUESTION 4
// LENGTH OF LARGEST SUBARRAY WITH CONTIGUOUS ELEMENTS I GFG
int largestContiguousSubarr(vector<int> &arr) {
    int len = 1;
    int maxVal = -1e8;
    int minVal = 1e8;

    for(int i = 0; i < arr.size(); i++) {
        maxVal = arr[i];
        minVal = arr[i];
        for(int j = i + 1; j < arr.size(); j++) {
            maxVal = max(maxVal, arr[j]);
            minVal = min(minVal, arr[j]);

            int gap = maxVal - minVal + 1;
            if(j - i + 1 == gap) {
                len = max(len,j - i + 1);
            }
        }
    }

    return len;
}

// QUESTION 5 
// LENGTH OF LARGEST SUBARRAY WITH CONTIGUOUS ELEMENTS II (WITH DUPLICATE ELEMENTS) GFG
int largestContiguousSubarrII(vector<int> &arr) {
    int len = 1;
    int maxVal = -1e8;
    int minVal = 1e8;

    for(int i = 0; i < arr.size(); i++) {
        maxVal = arr[i];
        minVal = arr[i];
        set<int> vis;
        vis.insert(arr[i]);
        for(int j = i + 1; j < arr.size(); j++) {
            if(vis.find(arr[j]) != vis.end())
                break;
            vis.insert(arr[j]);
            maxVal = max(maxVal, arr[j]);
            minVal = min(minVal, arr[j]);

            int gap = maxVal - minVal + 1;
            if(j - i + 1 == gap) {
                len = max(len,j - i + 1);
            }
        }
    }

    return len;
}

// QUESTION 6
// FIND THE SMALLEST NUMBER N WHOSE DIGITS MULTILY TO A GIVEN NUMBER N GFG

// QUESTION 7
// CHECK IF FREQUENCY OF ALL CHARACTERS CAN BECOME SAME BY ONE REMOVAL GFG

// QUESTION 8 
// INSERT DELETE GETRANDOM O(1) LEETCODE
class RandomizedSet {
public:
    unordered_map<int,int> m;
    vector<int> k;
    RandomizedSet() {
    }
    
    bool insert(int val) {
        if(m.find(val) != m.end())
            return false;
        k.push_back(val);
        m[val] = k.size() - 1;
        
        return true;
    }
    
    bool remove(int val) {
        if(m.find(val) == m.end())
            return false;
        int remIdx = m[val];
        int lastEle = k[k.size() - 1];
        m[lastEle] = remIdx;
        k[remIdx] = lastEle;
        k.pop_back();
        m.erase(val);
        return true;
        
    }
    
    int getRandom() {
        return k[rand() % k.size()]; 
    }
};

int main(int argc, char** argv) {
    // vector<int> arr = {10,12,12,10,11,10};
    // cout << divisiblePairs(arr, 3);
    // cout << largestContiguousSubarr(arr);
    // cout << largestContiguousSubarrII(arr);
}