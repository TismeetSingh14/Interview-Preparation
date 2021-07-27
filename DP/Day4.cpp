#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;

// QUESTION 1
// BURST BALLOONS MEMOIZATION LEETCODE
int maxCoinsBalloons(vector<int> &nums, int si, int ei, vector<vector<int>> &dp) {
    if(si + 1 == ei)
        return dp[si][ei] = 0;

    if(dp[si][ei] != 0)
        return dp[si][ei];
    
    int maxCost = -1e8;
    for(int cut = si + 1 ; cut < ei; cut++) {
        int leftCost = maxCoinsBalloons(nums, si, cut, dp);
        int rightCost = maxCoinsBalloons(nums, cut, ei, dp);

        int myCost = leftCost + nums[si]*nums[cut]*nums[ei] + rightCost;
        maxCost = max(maxCost, myCost);
    }

    return dp[si][ei] = maxCost;
}

int maxCoins(vector<int>& arr) {
    vector<int> nums(arr.size() + 2, 0);
    int n = 1;
    for(int i : arr)
        nums[n++] = i;
    nums[0] = nums[n++] = 1;
    vector<vector<int>> dp(nums.size(), vector<int> (nums.size(), 0));
    return maxCoinsBalloons(nums, 0, nums.size() - 1, dp);
}

// QUESTION 2
// BURST BALLOONS TABULATION LEETCODE
int maxCoinsDP(vector<int> &arr) {
    vector<int> nums(arr.size() + 2, 0);
    int n = 1;
    for(int i : arr)
        nums[n++] = i;
    nums[0] = nums[n++] = 1;
    vector<vector<int>> dp(nums.size(), vector<int> (nums.size(), 0));
    int maxCost = -1e8;

    for(int gap = 2; gap < dp.size(); gap++) {
        for(int i = 0, j = gap; j < dp.size(); i++, j++) {
            
            for(int k = i + 1; k < j; k++) 
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + nums[i]*nums[k]*nums[j]);
        }
    } 

    return dp[0][nums.size() - 1];
}

// QUESTION 3
// BOOLEAN PARENTHISIZATION LINTCODE
int numberOfWaysToParenthisize(vector<char> &symb, vector<char> &opr) {

    vector<vector<int>> dpF(symb.size(), vector<int> (symb.size(), 0));
    vector<vector<int>> dpT(symb.size(), vector<int> (symb.size(), 0));

    for(int gap = 0; gap < symb.size(); gap++) {
        for(int left = 0, right = gap; right < symb.size(); left++, right++) {
            if(gap == 0) {
                dpF[left][right] = symb[left] == 'F' ? 1:0;
                dpT[left][right] = symb[left] == 'T' ? 1:0;
                continue;
            }

            for(int i = left; i < right; i++) {
                if(opr[i] == '|') {
                    dpF[left][right] = dpF[left][i] * dpF[i+1][right];
                    dpT[left][right] = dpF[left][i] * dpT[i+1][right] + dpT[left][i] * dpT[i+1][right] + dpT[left][i] * dpF[i+1][right];
                }

                else if(opr[i] = '&') {
                    dpT[left][right] = dpT[left][i] * dpT[i+1][right];
                    dpF[left][right] = dpF[left][i] * dpT[i+1][right] + dpF[left][i] * dpF[i+1][right] + dpT[left][i] * dpF[i+1][right];
                }

                else if(opr[i] == '^') {
                    dpT[left][right] = dpT[left][i] * dpF[i+1][right] + dpF[left][i] * dpT[i+1][right];
                    dpF[left][right] = dpF[left][i] * dpF[i+1][right] + dpT[left][i] * dpT[i+1][right];
                }
            }
        }
    }

    for(vector<int> i:dpF) {
        for(int j:i)
            cout << j << " ";
        cout << "\n";
    }
    cout << "\n";
    for(vector<int> i:dpT) {
        for(int j:i)
            cout << j << " ";
        cout << "\n";
    }

    return dpT[0][dpT[0].size() - 1];
}

// QUESTION 4
// MINIMUM AND MAXIMUM VALUES OF AN EXPRESSION WITH * AND +
void minMaxValueOfExpression(vector<int> &symb, vector<char> &opr) {

    vector<vector<int>> dpmin(symb.size(), vector<int> (symb.size(), INT_MAX));
    vector<vector<int>> dpmax(symb.size(), vector<int> (symb.size(), 0));

    for(int gap = 0; gap < symb.size(); gap++) {
        for(int left = 0, right = gap; right < symb.size(); left++, right++) {
            if(gap == 0) {
                dpmin[left][right] = symb[left];
                dpmax[left][right] = symb[left];
                continue;
            }

            
            for(int i = left; i < right; i++) {
                int minTemp = 0;
                int maxTemp = 0;

                if(opr[i] == '+') {
                    minTemp = dpmin[left][i] + dpmin[i+1][right];
                    maxTemp = dpmax[left][i] + dpmax[i+1][right];
                }

                if(opr[i] == '*') {
                    minTemp = dpmin[left][i] * dpmin[i+1][right];
                    maxTemp = dpmax[left][i] * dpmax[i+1][right];
                }

                if(dpmin[left][right] > minTemp)
                dpmin[left][right] = minTemp;

                if(dpmax[left][right] < maxTemp)
                    dpmax[left][right] = maxTemp;
            }

            
        }
    }

    for(vector<int> i:dpmin) {
        for(int j:i)
            cout << j << " ";
        cout << "\n";
    }
    cout << "\n";
    for(vector<int> i:dpmax) {
        for(int j:i)
            cout << j << " ";
        cout << "\n";
    }

    cout << dpmin[0][dpmin[0].size() - 1] << " ";
    cout << dpmax[0][dpmax[0].size() - 1] << " ";
}

// QUESTION 5
// HIGHWAY BILLBOARD PROBLEM GFG
int maxRevenue(vector<int> &x, vector<int> &rev) {
    int maxVal = 0;
    for(int i:x)
        maxVal = max(maxVal, i);
}


void solve() {
    // vector<int> nums = {3,1,5,8};
    // maxCoins(nums);

    // vector<char> symb = {'T', 'F', 'T'};
    // vector<char> opr = {'^', '&'};
    // cout << numberOfWaysToParenthisize(symb, opr);

    // vector<int> symb = {1, 2, 3, 4, 5};
    // vector<char> opr = {'+','*','+','*'};
    // minMaxValueOfExpression(symb, opr);
}

int main(int argc,char** argv) {
    solve();
}