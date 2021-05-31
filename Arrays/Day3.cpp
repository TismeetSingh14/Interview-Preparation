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
// MEDIAN POINT IS THE SHORTEST DISTANCE POINT FROM ALL OTHER POINTS IN A LINE
vector<int> bestPoint(vector<vector<int>> &arr) {
    vector<int> row;
    vector<int> col;

    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < arr[0].size(); j++) {
            if(arr[i][j] == 1) {
                row.push_back(i);
                col.push_back(j);
            }
        }
    }

    if(row.size() % 2 != 0) {
        return {row[row.size()/2], col[row.size()/2]};
    }

    return {(row[row.size()/2] + row[(row.size() - 1)/2])/2, (col[row.size()/2] + col[(row.size() - 1)/2])/2};
}

// QUESTION 6
// SORT COLORS LEETCODE
void sortColors(vector<int>& nums) {
    int i = 0;
    int j = 0;
    int k = nums.size() - 1;
    int idx = 0;

    while(j <= k) {
        if(nums[j] == 1)
            j++;

        else if(nums[j] == 0) {
            swap(nums[i], nums[j]);
            i++;j++;
        }

        else {
            swap(nums[j], nums[k]);
            k--;
        }   
    }
}

// QUESTION 7
// SORT ARRAY BY PARITY LEETCODE
vector<int> sortArrayByParity(vector<int>& arr) {
    int i = 0; 
    int j = arr.size() - 1;
    
    while(i < j) {
        if(arr[i] % 2 != 0 && arr[j] % 2 == 0) {
            swap(arr[i],arr[j]);
            i++; j--;
        }
        
        else if(arr[i] % 2 != 0 && arr[j] % 2 != 0)
            j--;
        
        else if(arr[i] % 2 == 0 && arr[j] % 2 == 0)
            i++;
        
        else {
            i++;
            j--;
        }
    }
    
    return arr;
}

// QUESTION 8
// PARTITION LABELS LEETCODE
vector<int> partitionLabels(string s) {
    vector<int> m(26, 0);
    vector<int> cut;
    for(int i = 0; i < s.length(); i++)
        m[s[i] - 'a'] = i;
    
    int end = 0;
    int start = 0;
    for(int i = 0; i < s.length(); i++) {
        end = max(end, m[s[i] - 'a']);
        if(i == end) {
            cut.push_back(end - start + 1);
            start = end + 1;
        }
    }
    return cut;
}

int main(int argc, char** argv) {
    
}