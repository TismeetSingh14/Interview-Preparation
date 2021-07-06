#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;

// QUESTION 1
// PAINT FENCE LEETCODE
int noOfColors(int n, int k) {
    int sameColor = k;
    int diffColor = k*(k-1);

    for(int i = 3; i <= n; i++) {
        int totalColor = sameColor + diffColor;
        sameColor = diffColor;
        diffColor = totalColor*(k-1);
    }

    return diffColor + sameColor;
}

// QUESTION 2
// PAINT HOUSE LEETCODE
int costOfPaint(vector<vector<int>> &cost) {
    int maxCost = 1e9;
    for(int i = cost.size() - 2; i >= 0; i--) {
        for(int j = 0; j < cost[0].size(); j++) {
            if(j == 0) 
                cost[i][j] += min(cost[i + 1][j + 1], cost[i + 1][j + 2]);
            else if(j == 1)
                cost[i][j] += min(cost[i + 1][j - 1], cost[i + 1][j + 1]);
            else 
                cost[i][j] += min(cost[i + 1][j - 1], cost[i + 1][j - 2]);
            
            if(i == 0)
                maxCost = min(maxCost, cost[i][j]);
        }
    }

    return maxCost;
}

// QUESTION 3
// PAINT HOUSE II LEETCODE
int costOfPaintII(vector<vector<int>> &cost) {
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    for(int i = 0; i < cost[0].size(); i++) {
        if(cost[0][i] < min1) {
            min2 = min1;
            min1 = cost[0][i];
        }

        else if(cost[0][i] < min2) 
            min2 = cost[0][i];
    }

    for(int i = 1; i < cost.size(); i++) {
        int temp_min1 = INT_MAX;
        int temp_min2 = INT_MAX;
        for(int j = 0; j < cost[i].size(); j++) {
            
            if(min1 != cost[i][j]) {
                cost[i][j] += min1;
            }

            else if(min1 == cost[i][j])
                cost[i][j] += min2;

            if(cost[i][j] < temp_min1) {
                temp_min2 = temp_min1;
                temp_min1 = cost[i][j];
            }

            else if(cost[i][j] < temp_min2) 
                temp_min2 = cost[i][j];
        }

        min1 = temp_min1;
        min2 = temp_min2;
    }

    int minAns = 1e8;
    for(int i = 0; i < cost[cost.size() - 1].size(); i++) {
        minAns = min(minAns, cost[cost.size() - 1][i]);
    }

    return minAns;
}

// QUESTON 4
// COUNT NUMBER OF BINARY STRINGS WITHOUT CONSECUTIVE ONES GFG
// RECURRENCE FOR THIS QUESTION
// A[I] = A[I-1] + B[I-1] i.e., 0 CAN BE APPENDED BEHIND STRINGS ENDING WITH 0 AND 1
// B[I] = A[I-1] i.e., 0 CAN BE APPENDED BEHIND STRINGS ENDING WITH 0 BUT NOT 1
// NET ANSWER WE GET THE FIBONACCI SERIES PATTERN
int numStrings(int n) {
    int a = 0;
    int b = 1;
    int c = a + b;
    for(int i = 3; i <= n + 1; i++) {
        a = b;
        b = c;
        c = a + b;
    }

    return b + c;
}

// QUESTION 5
// COUNT POSSIBLE WAYS TO CONSTRUCT BUILDINGS
int waysToConstruct(int n) {
    int a = 0;
    int b = 1;
    int c = a + b;
    for(int i = 3; i <= n + 1; i++) {
        a = b;
        b = c;
        c = a + b;
    }

    return (b+c)*(b+c);
}

// QUESTION 6
// JUMP GAME II LEETCODE
int jump(vector<int>& arr) {
    int ans = 0;
    int cmax = 0;
    int nmax = 0;

    for(int i = 0; i < arr.size() - 1; i++) {
        nmax = max(nmax, i+arr[i]);

        if(i == cmax) {
            ans++;
            cmax = nmax;
        }
    }

    return ans;
}

// QUESTION 7
// TOTAL NUMBER OF BST and BT WITH N KEYS GFG
// APPROACH: RETURN CATALAN NUMBER
// N-TH CATALAN NUMBER: C(n) = 2nCn/(n + 1)
// C(2) = C0C1 + C1C0
// C(3) = C0C2 + C1C1 + C2C0
// C(4) = C0C3 + C1C2 + C2C1 + C3C0
void totalBSTandBT(int n) {
    int facn = 1;
    int facnp1 = 1;
    int fac = 1;

    for(int i = 1; i <= 2*n; i++) {
        fac *= i;
        if(i == n) {
            facn = fac;
            facnp1 = fac*(n+1); 
        }
    }

    facn = facn*facnp1;

    cout << "BST: " << fac/facn << "\n"; 
    cout << "BT: " << fac/facnp1;
}

// QUESTION 8
// COUNT OF VALID PARENTHESES GFG
// CONSIDER N = 2
// CASE 1 = (0) 2
// CASE 2 = (1) 1
// CASE 3 = (2) 0
// ANS = CASE 1 + CASE 2 + CASE 3
// N-TH CATALAN NUMBER
int countValid(int n) {
    int facn = 1;
    int facnp1 = 1;
    int fac = 1;

    for(int i = 1; i <= 2*n; i++) {
        fac *= i;
        if(i == n) {
            facn = fac;
            facnp1 = fac*(n+1); 
        }
    }

    facn = facn*facnp1;
    return fac/facn;
}

// SIMILAR QUESTION USING CATALAN IS MOUNTAINS AND VALLEYS /\

// QUESTION 9
// 2 KEYS KEYBOARD LEETCODE
int solver(int pr, int cp, int req, vector<vector<int>> &dp) {
    if(pr == req)
        return dp[pr][cp] = 0;
    
    if(pr > req)
        return dp[pr][cp] = 1e8;
    
    if(dp[pr][cp] != -1)
        return dp[pr][cp];
    
    int a = 1e8;
    int b = 1e8;
    if(cp != 0) 
        a = solver(pr + cp, cp, req, dp);
    if(pr != cp) 
        b = solver(pr, pr, req, dp);
    
    return dp[pr][cp] = min(a,b) + 1;
}

int minSteps(int n) {
    vector<vector<int>> dp(2000, vector<int>(2000, -1));
    return solver(1, 0, n, dp);
}

void solve() {
    // cout << noOfColors(2,2);
    // vector<vector<int>> cost = {{5}};
    // cout << costOfPaintII(cost);
    // cout << numStrings(1);
    // cout << waysToConstruct(2);
    // totalBSTandBT(5);
    // cout << countValid(3);
}

int main(int argc,char** argv) {
    solve();
}