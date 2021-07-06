#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

// APPROACH 3D DP WITH 3 PARAMETERS T[I][J][X]
// I = DAY NUMBER
// K = NUMBER OF TRANSACTIONS (RANGE FROM 0 TO NO. OF TRANSACTIONS ALLOWED)
// X = NUMBER OF STOCKS PRESENT WITH ME
// ONLY BUY AND SELL IS ALLOWED
// BUY AND BUY IS NOT ALLOWED
// RECURRENCE RELATION
// T[I][K][0] = MAX(T[I-1][K][0], T[I-1][K][1] + PRICE[I])
// T[I][K][0] = MAX(T[I-1][K][1], T[I-1][K-1][0] - PRICE[I])

// QUESTION 1
// BEST TIME TO BUY AND SELL STOCK LEETCODE
// ONE TRANSACTION
int maxProfit(vector<int> &arr) {
    int T_i10 = 0;
    int T_i11 = INT_MIN;

    for(int i = 0; i < arr.size(); i++) {
        T_i10 = max(T_i10, T_i11 + arr[i]);
        T_i11 = max(T_i11, -arr[i]);
    }

    return T_i10;
}

// QUESTION 2
// BEST TIME TO BUY AND SELL STOCK II LEETCODE
// INFINITE TRANSACTIONS
int maxProfitII(vector<int> &arr) {
    int T_ik0 = 0;
    int T_ik1 = INT_MIN;

    for(int i = 0; i < arr.size(); i++) {
        int temp = T_ik0;
        T_ik0 = max(T_ik0, T_ik1 + arr[i]);
        T_ik1 = max(T_ik1, temp - arr[i]);
    }

    return T_ik0;
}

// QUESTION 3
// BEST TIME TO BUY AND SELL STOCK III LEETCODE
int maxProfitIII(vector<int> &arr) {
    int T_i20 = 0;
    int T_i10 = 0;
    int T_i21 = INT_MIN;
    int T_i11 = INT_MIN;

    for(int i = 0; i < arr.size(); i++) {
        T_i20 = max(T_i20, T_i21 + arr[i]);
        T_i21 = max(T_i21, T_i10 - arr[i]);
        T_i10 = max(T_i10, T_i11 + arr[i]);
        T_i11 = max(T_i11, -arr[i]);
    }

    return T_i20;
}

// QUESTION 4
// BEST TIME TO BUY AND SELL STOCK WITH COOLDOWN LEETCODE
int maxProfitWithCooldown(vector<int> &arr, int fee) {
    int T_ik0 = 0;
    int T_ik1 = INT_MIN;
    int T_ik0_Prev = 0;

    for(int i = 0; i < arr.size(); i++) {
        int temp = T_ik0;
        T_ik0 = max(T_ik0, T_ik1 + arr[i]);
        T_ik1 = max(T_ik1, T_ik0_Prev - arr[i]);
        T_ik0_Prev = temp;
    }

    return T_ik0;
}

// QUESTION 5
// BEST TIME TO BUY AND SELL STOCK WITH TRANSACTION FEE LEETCODE
int maxProfitWithFee(vector<int> &arr, int fee) {
    int T_ik0 = 0;
    int T_ik1 = INT_MIN;

    for(int i = 0; i < arr.size(); i++) {
        int temp = T_ik0;
        T_ik0 = max(T_ik0, T_ik1 + arr[i] - fee);
        T_ik1 = max(T_ik1, temp - arr[i]);
    }

    return T_ik0;
}

void solve() {

}

int main(int argc,char** argv) {
    solve();
}