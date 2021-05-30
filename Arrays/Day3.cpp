#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

// QUESTION 1
// NUMBER OF SUBARRAYS WITH BOUNDED MAXIMUM LEETCODE
int maxSubarrays(vector<int> &arr, int l, int r) {
    int ans = 0;
    int i = 0;
    int j = 0;
    int prevValCount = 0;

    while(i < arr.size() && j < arr.size()) {
        if(arr[j] >= l && arr[j] <= r) {
            ans += (j - i + 1);
            prevValCount = (j - i + 1);
            j++;
        }

        else if(arr[j] < l) {
            ans += prevValCount;
            j++;
        }

        else if(arr[j] > r) {
            prevValCount = 0;
            i = j + 1;
            j++;
        }
    }

    return ans;
}

// QUESTION 2
// MAXIMUM SUM SUBARRAY LEETCODE
// KADANES ALGORITHM
int maxSubarraySum(vector<int> &arr) {
    int cmax = 0;
    int omax = -1e9;

    for(int i = 0; i < arr.size(); i++) {
        if(cmax >= 0)
            cmax += arr[i];
        else
            cmax = arr[i];
        omax = max(omax, cmax);
    }

    return omax;
}

int main(int argc, char** argv) {
    
}