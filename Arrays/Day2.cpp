#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;

// QUESTION 1
// SQUARES OF SORTED ARRAY LEETCODE
vector<int> sortedSquares(vector<int>& nums) {
    int p1 = 0;
    int p2 = nums.size() - 1;
    vector<int> ans(nums.size(), 0);
    int j = nums.size() - 1;
    
    while(p1 <= p2) {
        if(abs(nums[p1]) > abs(nums[p2])){
            ans[j] = pow(abs(nums[p1]),2);
            p1++;
            j--;
        }
        
        else {
            ans[j] = pow(abs(nums[p2]),2);
            p2--;
            j--;
        }
    }
    
    return ans;
}

// QUESTION 2
// ROTATE ARRAY LEETCODE
void reverse(vector<int> &arr, int si, int ei) {
    while(si <= ei) {
        swap(arr[si],arr[ei]);
        si++;
        ei--;
    }
}

void rotate(vector<int>& arr, int k) {
    if(arr.size() < 2)
        return;
    k = k % arr.size();
    k = arr.size() - k;
    
    reverse(arr, 0, k-1);
    reverse(arr, k, arr.size() - 1);
    reverse(arr, 0, arr.size() - 1);
}

int main(int argc, char** argv) {
    
}