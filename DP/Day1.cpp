#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// QUESTION 1
// LONGEST INCREASING SUBSEQUENCE LEETCODE 
// O(N^2) ALSO PRINT THE LIS SEQUENCE
int LIS(vector<int> &arr) {
    vector<int> dp(arr.size(), 1);
    vector<vector<int>> temp(arr.size(), vector<int> ());
    for(int i = 0; i < temp.size(); i++) {
        string k = to_string(arr[i]) + " ";
        temp[i].push_back(arr[i]);
    }

    int maxLen = 0;
    vector<int> ans;
    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < i; j++) {
            if(arr[i] > arr[j]) {
                if(dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    temp[i] = temp[j];
                    temp[i].push_back(arr[i]);
                }
            }

            if(maxLen < dp[i]) {
                maxLen = dp[i];
                ans = temp[i];
            }
        }
    }

    for(int i: ans)
        cout << i << " ";
    cout << "\n";
    return maxLen;
}

// QUESTION 2
// LONGEST INCREASING SUBSEQUENCE LEETCODE 
// O(NlogN) 
int LISOptimized(vector<int> &arr) {
    vector<int> lis(arr.size(), 0);
    int ans = 0;
    for(int i = 0; i < arr.size(); i++) {
        int li = 0;
        int hi = ans;

        while(li < hi) {
            int mid = li + (hi-li)/2;
            if(lis[mid] < arr[i]) 
                li = mid + 1;
            else 
                hi = mid;
        }

        lis[li] = arr[i];
        if(li == ans)
            ans++;
    }

    return ans;
}

// QUESTION 3
// BUILDING BRIDGES GFG
int maxBridges(vector<int> &north, vector<int> &south) {
    int n = north.size();
    vector<pair<int,int>> NSarr(n);
    for(int i = 0; i < north.size(); i++) {
        pair<int,int> p;
        p.first = north[i];
        p.second = south[i];
        NSarr[i] = p;
    }

    sort(NSarr.begin(), NSarr.end(),[](const pair<int,int> &a,const pair<int,int> &b)->bool{
        if(a.second == b.second) 
            return a.first < b.first;
        return a.second < b.second;
    });

    vector<int> dp(n, 1);
    int maxLen = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(NSarr[i].first >= NSarr[j].first) {
                if(dp[i] < dp[j] + 1)
                    dp[i] = dp[j] + 1;
            }

            if(maxLen < dp[i])
                maxLen = dp[i];    
        }
    }

    return maxLen;
}

// QUESTION 4
// RUSSIAN DOLL ENVOLOPES LEETCODE
int maxEnvelopes(vector<vector<int>>& arr) {
    sort(arr.begin(), arr.end(), [](vector<int> &a, vector<int> &b) {
    if (a[0] == b[0])
        return a[1] > b[1];
    else
        return a[0] < b[0]; 
    });

    vector<int> dp(arr.size(), 1);
    int maxEnv = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i][1] > arr[j][1])
                dp[i] = max(dp[i], dp[j] + 1);
        }

        maxEnv = max(maxEnv, dp[i]);
    }

    return maxEnv;
}

// QUESTION 5
// BOX STACKING GFG
int maxStackBox(vector<int> &height, vector<int> &width, vector<int> &length) {
    vector<vector<int>> arr;
    for(int i = 0; i < height.size(); i++) {

        
    }
}

// QUESTION 6
// MINIMUM NUMBER OF INCREASING SUBSEQUENCES GFG
// TO FIND LDS = ANSWER
int minCountLIS(vector<int> &arr) {
    vector<int> lis(arr.size(), 0);
    int ans = 0;
    for(int i = arr.size() - 1; i >= 0; i--) {
        int li = 0;
        int hi = ans;

        while(li < hi) {
            int mid = li + (hi-li)/2;
            if(lis[mid] < arr[i]) 
                li = mid + 1;
            else 
                hi = mid;
        }

        lis[li] = arr[i];
        if(li == ans)
            ans++;
    }

    return ans;
}

// QUESTION 7
// WEIGHTED JOB SCHEDULING GFG
int maxProfit(vector<vector<int>> &arr) {
    
}

void solve() {
    // vector<int> north = {0,0,0,0};
    // vector<int> south = {1,1,1,1};
    // cout << maxBridges(north, south);

    // vector<int> arr = {1, 6, 2, 4, 3};
    // cout << minCountLIS(arr);
}

int main(int argc,char**argv) {
    solve();
}