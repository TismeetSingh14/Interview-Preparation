#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

// QUESTION 1
// EGG DROP LEETCODE
int minDroppings(int f, int e) {
    vector<vector<int>> dp(e + 1, vector<int> (f + 1, 0));

    for (int j = 1; j <= f; j++)
        dp[1][j] = j;

    for(int i = 2; i < dp.size(); i++) {
        for(int j = 2; j < dp[0].size(); j++) {
        
            dp[i][j] = INT_MAX; 
            for(int k = 1; k <= f; k++) {
                dp[i][j] = min(dp[i][j],max(dp[i - 1][k - 1], dp[i][j - k]) + 1);
            }
        }
    }

    for(vector<int> i:dp) {
        for(int j: i)
            cout << j << " ";
        cout << "\n";
    }

    return dp[e][f];
}

void solve() {
    cout << minDroppings(10,2);
}

int main(int argc,char** argv) {
    solve();
}