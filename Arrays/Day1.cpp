#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

// QUESTION 1
// LONG PRESSED NAME LEETCODE
bool isLongPressedName(string name, string typed) {
    int i = 0;
    int j = 0;
    
    if(typed.length() < name.length())
        return false;
    
    while(j < typed.length()) {
        if(name[i] == typed[j]) {
            i++;
            j++;
        }
        
        else if(name[i] != typed[j]) {
            if(j > 0 && typed[j] == typed[j - 1])
                j++;
            else 
                return false;
        }
    }
    
    if(i == name.length() && j < typed.length())
        return false;
    
    if(j == typed.length() && i < name.length())
        return false;
    
    
    return true;
}

// QUESTION 2
// RANGE ADDITION LEETCODE/LINTCODE
vector<int> rangeAddition(vector<vector<int>> &queries, int n) {
    vector<int> ans(n + 1, 0);
    for(int i = 0; i < queries.size(); i++) {
        ans[queries[i][0]] += queries[i][2];
        ans[queries[i][1] + 1] += -queries[i][2];
    }

    for(int i = 1; i < ans.size(); i++) {
        ans[i] = ans[i] + ans[i - 1];
    }

    return ans;
}

// QUESTION 3
// MAX RANGE QUERY CODECHEF
int maxHeightOfCakes(vector<vector<int>> &range, int k) {

    int maxEnd = -1;
    vector<int> ans(100002, 0);
    for(int i = 0; i < range.size(); i++) {
        ans[range[i][0]] += 1;
        ans[range[i][1] + 1] -= 1;
        maxEnd = max(maxEnd, range[i][1]); 
    }

    int maxCakes = 0;
    if(ans[1] == k)
        maxCakes++;
    for(int i = 1; i <= maxEnd + 1; i++) {
        ans[i] = ans[i] + ans[i - 1];
        if(ans[i] == k)
            maxCakes++;
    }

    vector<int> prefixCountK(maxEnd + 2,0);
    if(ans[1] == k)
        prefixCountK[1] += 1;

    for(int i = 1; i <= maxEnd + 2; i++) {
        if(ans[i] == k)
            prefixCountK[i] += 1;
        prefixCountK[i] += prefixCountK[i - 1];
    }

    vector<int> prefixCountKP1(maxEnd + 2,0);
    if(ans[1] == k + 1)
        prefixCountKP1[1] += 1;

    for(int i = 1; i <= maxEnd + 2; i++) {
        if(ans[i] == k + 1)
            prefixCountKP1[i] += 1;
        prefixCountK[i] += prefixCountKP1[i - 1];
    }

    int myans = -1;
    for(int i = 0; i < range.size(); i++) {
        int lostCakes = prefixCountK[range[i][1]] - prefixCountK[range[i][0] - 1];
        int gainCakes = prefixCountKP1[range[i][1]] - prefixCountKP1[range[i][0] - 1];
        myans = max(myans, maxCakes - lostCakes + gainCakes);
    }

    return myans;
}


// QUESTION 4
// ORDERLY QUEUE LEETCODE
string orderlyQueue(string s, int k) {
    if(k >= 2) {
        sort(s.begin(), s.end());
        return s;
    }
    
    string ans = s;
    for(int i = 0; i < s.length(); i++) {
        s = s.substr(1) + s[0];
        if(s < ans) {
            ans = s;
        }
    }
    
    return ans;
}

// QUESTION 5
// CONTAINER WITH MOST WATER LEETCODE
int maxArea(vector<int>& arr) {
    int i = 0;
    int j = arr.size() - 1;
    int maxAns = 0;
    
    while(i < j) {
        if(arr[i] < arr[j]) {
            maxAns = max(maxAns, (j-i)* arr[i]);
            i++;
        }
        
        else {
            maxAns = max(maxAns, (j-i)* arr[j]);
            j--;
        }
    }
    
    return maxAns;
}

int main(int argc, char** argv) {
    vector<vector<int>> range = {{2,6},{4,9},{1,4}};
    cout << maxHeightOfCakes(range,2);
}