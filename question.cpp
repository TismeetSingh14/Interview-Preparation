#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <map>
using namespace std;
#define ll long long int

bool solve(int num ,int n1, int n2, unordered_map<int,bool> &dp){
    if(num==1)
        return true;
    if(dp[num]!=0)
        return dp[num];
    if(num%n1==0 && n1 != 1)
        return dp[num] = dp[num] || solve(num/n1,n1,n2,dp);
    if(num-n2>=1)
        return dp[num] = solve(num-n2,n1,n2,dp);
    return false;
}

int main(int argc,char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
    while(t-- > 0) {
        ll a, b, n;
        cin >> n >> a >> b;
        unordered_map<int,bool> dp;
    
        if(solve(n ,a, b, dp))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}