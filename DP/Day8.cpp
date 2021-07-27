#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// QUESTION 1
// OPTIMAL BINARY SEARCH TREE GFG

// QUESTION 2
// REGULAR EXPRESSION MATCHING LEETCODE
bool isMatch(string s1, string s2) {
    vector<vector<bool>> dp(s1.length() + 1, vector<bool> (s2.length() + 1, 0));
    dp[0][0] = true;
    for(int i = 1; i < s1.length(); i++) {
        for(int j = 1; j < s2.length(); j++) {
            if(s1[i-1] == s2[j-1] || s2[j-1] == '.')
                dp[i][j] = dp[i][j] || dp[i-1][j-1];

            else if(s1[i-1] != s2[j-1])
                dp[i][j] = false;

            else if(s2[j-1] == '*') {
                if(s1[i-2] == s2[j-1])
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }

        }
    }

    return dp[s1.length()][s2.length()];
}

int main(int arg,char** argv) {

}