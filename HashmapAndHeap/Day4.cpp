#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
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

int main(int argc, char** argv) {

}