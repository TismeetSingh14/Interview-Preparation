#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// QUESTION 1
// SUBARRAY SUM EQUALS K LEETCODE
int subarraySumK(vector<int> &nums, int k) {
    unordered_map<int, int> prefixMap;
    int count = 0;
    prefixMap[0] = 1;
    int sum = 0;

    for(int j = 0; j < nums.size(); j++) {
        sum += nums[j];
        int tar = sum - k;

        if(prefixMap.find(tar) != prefixMap.end()) 
            count+= prefixMap[tar];
        prefixMap[sum]++;
    }

    return count;
}

// QUESTION 2
// SUBARRAY SUM DIVISIBLE BY K GFG
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> prefixMap;
    int sum = 0;
    int count = 0;
    prefixMap[0] = 1;

    for(int i = 0; i < nums.size(); i++) {
        sum += nums[i];
        int target = ((sum % k) + k) % k;

        if(prefixMap.find(target) != prefixMap.end())
            count += prefixMap[target];
        prefixMap[target]++;
    }
    
    return count;
}

// QUESTION 3
// SAME DIFFERENCE CODEFORCES
int pairsWithSameDiff(vector<int> &arr) {
    unordered_map<int,int> m;
    int ans = 0;

    for(int i = 0; i < arr.size(); i++) {
        int val = arr[i] - i;
        ans += m[val];
        m[val]++;
    }

    return ans;
}

// QUESTION 4
// SUBARRAY WITH EQUAL 0s AND 1s GFG
int countSubarrEqual01(vector<int> &arr) {
    unordered_map<int,int> pc0;
    unordered_map<int,int> pc1;
    unordered_map<int,int> m;
    int ans = 0;
    m[0] = 1;

    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] == 0) {
            pc0[i] = pc0[i - 1] + 1;
            pc1[i] = pc1[i - 1];
        }
        
        if(arr[i] == 1) {
            pc1[i] = pc1[i - 1] + 1;
            pc0[i] = pc0[i - 1];
        }

        int val = pc0[i] - pc1[i];
        ans += m[val];
        m[val]++;
    }

    return ans;
}

// QUESTION 5
// SUBSTRING WITH EQUAL 0s, 1s AND 2s GFG
int substringEqual012(string s) {
    unordered_map<int,int> pc0;
    unordered_map<int,int> pc1;
    unordered_map<int,int> pc2;
    unordered_map<string,int> m;
    int ans = 0;
    m["0#0"] = 1;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '0') {
            pc0[i] = pc0[i - 1] + 1;
            pc1[i] = pc1[i - 1];
            pc2[i] = pc2[i - 1];
        }
        
        if(s[i] == '1') {
            pc0[i] = pc0[i - 1];
            pc1[i] = pc1[i - 1] + 1;
            pc2[i] = pc2[i - 1];
        }

        if(s[i] == '2') {
            pc0[i] = pc0[i - 1];
            pc1[i] = pc1[i - 1];
            pc2[i] = pc2[i - 1] + 1;
        }

        int val01 = pc0[i] - pc1[i];
        int val02 = pc0[i] - pc2[i];
        string k = to_string(val01) + '#' + to_string(val02);
        ans += m[k];
        m[k]++;
        
    }
    return ans;
}

// QUESTION 6 
// K CLOSEST POINTS TO ORIGIN LEETCODE
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    priority_queue<pair<int,int>> pq;
    
    for(int i = 0; i < points.size(); i++) {
        int dis = (points[i][0]*points[i][0]) + (points[i][1]*points[i][1]);
        
        if(pq.size() >= k && pq.top().first > dis) {
            pq.pop();
            pq.push({dis, i});
        }
        
        else if(pq.size() < k) {
            pq.push({dis, i});
        }
    }
    
    vector<vector<int>> ans;
    while(pq.size() != 0) {
        ans.push_back(points[pq.top().second]);
        pq.pop();
    }
    
    return ans;
}

// QUESTION 7
// LONGEST CONSECUTIVE 1s
int longestArrOf1(vector<int> arr) {
    int count = 0;
    int maxCount = 0;

    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] == 1)
            count++;
    
        else 
            count = 0;
        
        maxCount = max(maxCount, count);
    }

    return maxCount;
}


int main(int argc, char** argv) {
    vector<int> arr = {0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1};
    // cout << pairsWithSameDiff(arr);
    // cout << countSubarrEqual01(arr);
    // string s = "102100211";
    // cout << substringEqual012(s);
    cout << longestArrOf1(arr);
}