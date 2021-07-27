#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;

// QUESTION 1
// COUNT OF DISTINCT PALINDROMIC SUBSEQUENCES LEETCODE 
int countPalindromicSubsequences(string s) {
    vector<vector<int>> dp(s.length(), vector<int> (s.length(), 0));
    long long int m = 1e9+7;
    for(int gap = 0; gap < s.length(); gap++) {
        for(int i = 0, j = gap; j < s.length(); i++, j++) {
            if(gap == 0) {
                dp[i][j] = 1;
                continue;
            }

            if(s[i] != s[j]) {
                dp[i][j] += dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
            }

            if(s[i] == s[j]) {
                dp[i][j] += 2*dp[i + 1][j - 1];

                int lo = i + 1;
                int hi = j - 1;

                while(lo <= hi && s[lo] != s[i]) lo++;
                while(lo <= hi && s[hi] != s[i]) hi--;

                if(lo > hi)
                    dp[i][j] += 2;

                else if(lo == hi)
                    dp[i][j] += 1;

                else
                    dp[i][j] -= dp[lo+1][hi-1];
            }
            
            dp[i][j] = (dp[i][j] + m) % m;
        }
    }

    return dp[0][dp[0].size() - 1]%(m);
}

// QUESTION 2
// PERFECT SQUARES LEETCODE
int numSquares(int n) {
    vector<int> dp(n + 1, 1e9);
    dp[1] = 1;
    dp[0] = 0;
    
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j*j <= i; j++) {
            dp[i] = min(dp[i-(j*j)] + 1,dp[i]);
        }
    }

    return dp[n];
}

// QUESTION 3
// COUNT OF DISTINCT SUBSEQUENCES
int countSubsequences(string s) {
    vector<int> dp(s.length() + 1, 0);

    dp[0] = 1;
    unordered_map<char,int> idx;
    for(int i = 1; i < dp.size(); i++) {
        dp[i] = dp[i-1]*2;
        if(idx.find(s[i-1]) != idx.end())
            dp[i] -= dp[idx[s[i-1]]];
        
        idx[s[i-1]] = i;
    }

    return dp[s.length()];
}

// QUESTION 4
// DISTINCT SUBSEQUENCES LEETCODE
int numDistinct(string s1, string s2) {
    vector<vector<int>> dp(s1.length() + 1, vector<int> (s2.length() + 1, 0));
    long m = 1e9 + 7;
    for (int i = s1.length(); i >= 0; i--) {
        for (int j = s2.length(); j >= 0; j--) {
            if (j == s2.length() || (i == s1.length() && j == s2.length())) {
                dp[i][j] = 1;
                continue;
            }

            if (i == s1.length() || (s1.length() - i < s2.length() - j)) {
                dp[i][j] = 0;
                continue;
            }

            if (s1[i] == s2[j])
                dp[i][j] = dp[i + 1][j + 1] + dp[i + 1][j];

            else
                dp[i][j] = dp[i + 1][j];
            
            dp[i][j] = (dp[i][j] + m)%m;
        }
    }

    return dp[0][0];
}

// QUESTION 5
// MAXIMAL SQUARE LEETCODE
int maxSq = 0;
int maximalSquare_(vector<vector<char>>& grid, int x, int y, vector<vector<int>> &dp) {
    if(x == grid.size() || y == grid[0].size())
        return 0;

    if(dp[x][y] != -1)
        return dp[x][y];

    int right = maximalSquare_(grid, x + 1, y,dp);
    int down = maximalSquare_(grid, x, y + 1,dp);
    int diag = maximalSquare_(grid, x + 1, y + 1,dp);

    int minans = 0;
    if(grid[x][y] == '1') 
        minans = min(diag, min(down, right)) + 1;

    maxSq = max(maxSq, minans);

    return dp[x][y] = minans;
}

int maximalSquare(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n,vector<int>(m,-1));
    maximalSquare_(grid, 0, 0, dp);
    return maxSq*maxSq;
}

// QUESTION 6
// COUNT PALINDROMIC SUBSTRINGS LEETCODE
int countSubstrings(string s) {
    vector<vector<int>> dp(s.length(), vector<int>(s.length(), 0));
    int count = 0;

    for (int gap = 0; gap < s.length(); gap++)
    {
        for (int si = 0, ei = gap; ei < s.length(); si++, ei++)
        {
            if (gap == 0)
                dp[si][ei] = 1;

            else if (gap == 1 && s[si] == s[ei])
                dp[si][ei] = 2;

            else if (s[si] == s[ei] && dp[si + 1][ei - 1] != 0)
                dp[si][ei] = dp[si + 1][ei - 1] + 2;

            count = dp[si][ei] ? count + 1 : count;
        }
    }

    return count;
}

// QUESTION 7
// EDIT DISTANCE LEETCODE
int minDistance(string s1, string s2) {
    vector<vector<int>> dp(s1.length() + 1, vector<int>(s2.length() + 1, 0));
    
    for (int i = 0; i <= s1.length(); i++) {
        for (int j = 0; j <= s2.length(); j++) {
            if (i == 0) {
                dp[i][j] = j;
                continue;
            }

            else if (j == 0) {
                dp[i][j] = i;
                continue;
            }

            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];

            else {
                int insertion = dp[i][j - 1];
                int deletion = dp[i - 1][j];
                int replace = dp[i - 1][j - 1];
                dp[i][j] = min(insertion, min(deletion, replace)) + 1;
            }
        }
    }


    return dp[s1.length()][s2.length()];
}

// QUESTION 8
// ARITHMETIC SLICES LEETCODE
int numberOfArithmeticSlices(vector<int>& nums) {
    int n = nums.size();
    if(n < 3)
        return 0;

    vector<int> dp(n, 0);
    dp[0] = 0;
    dp[1] = 0;
    int sum = 0;
    for(int i = 2; i < n; i++) {
        if((nums[i] - nums[i - 1]) == (nums[i - 1] - nums[i - 2]))
            dp[i] = dp[i - 1] + 1;
        else
            dp[i]=0;
        
        sum += dp[i];
    }

    return sum;
}

int main(int argc,char** argv) {

}