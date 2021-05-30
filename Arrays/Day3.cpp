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

// QUESTION 3
// K CONCATENATION MAXIMUM SUM LEETCODE 
int kConcatenationMaxSum(vector<int>& arr, int k) {
    if(k == 1) {
        long long int cmax = 0;
        long long int omax = -1e9;
        for(int i = 0; i < arr.size(); i++) {
            if(cmax >= 0)
                cmax += arr[i%arr.size()];
            else
                cmax = arr[i%arr.size()];
            omax = max(omax, cmax);
        }
        return (int(omax%1000000007) < 0? 0:int(omax%1000000007));
    }

    long long int sum = 0;
    for(int i = 0; i < arr.size(); i++) 
        sum += arr[i];

    if(sum <= 0) {
        long long int cmax = 0;
        long long int omax = -1e9;
        for(int i = 0; i < 2*arr.size(); i++) {
            if(cmax >= 0)
                cmax += arr[i%arr.size()];
            else
                cmax = arr[i%arr.size()];
            omax = max(omax, cmax);
        }
        
        return (int(omax%1000000007) < 0? 0:int(omax%1000000007));
    }
    
    long long int cmax = 0;
    long long int omax = -1e9;
    for(int i = 0; i < 2*arr.size(); i++) {
        if(cmax >= 0)
            cmax += arr[i%arr.size()];
        else
            cmax = arr[i%arr.size()];
        omax = max(omax, cmax);
    }

    return int((omax + sum*(k-2))%1000000007) < 0 ? 0:int((omax + sum*(k-2))%1000000007);
}

// QUESTION 4
// SEGREGATE ONES AND ZEROES
void segregate01(vector<int> &arr) {
    int i = 0; 
    int j = arr.size()-1;

    while(i < j) {
        while(arr[i] == 0 && i < j)
            i++;
        while(arr[j] == 1 && i < j)
            j--;
        
        if(i < j) {
            arr[i] = 0;
            arr[j] = 1;
            i++;
            j--;
        }
    }
} 

// QUESTION 5
// BEST MEETING POINT LEETCODE/LINTCODE
int bestPoint(vector<vector<int>> &arr) {
    
}

int main(int argc, char** argv) {
    
}