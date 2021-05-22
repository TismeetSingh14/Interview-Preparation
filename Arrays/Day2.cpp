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

// QUESTION 3
// RELATIVELY PRIME NUMBERS CODEFORCES
void relativePrime(int l, int r) {
    cout << "YES";
    for(int i = l; i <= r; i+=2) {
        cout << i << " " << i + 1;
    }
}

// QUESTION 4
// NAPOLEAN CAKE CODEFORCES
vector<int> napoleonCake(vector<int> &arr) {
    int n = arr.size() + 1;
    vector<int> ans(n, 0);
    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] > 0) {
            ans[i + 1] += 1;
            if(i + 1 - arr[i] >= 0) {
                ans[i + 1 - arr[i]] -= 1;
            }
        }
    }

    for(int i = ans.size() - 2; i>= 0; i--) {
        ans[i] = ans[i] + ans[i + 1];
    }

    for(int i = 1; i < ans.size(); i++) {
        if(ans[i] > 0) {
            ans[i] = 1;
        }
    }

    return ans;
}

// QUESTION 5
// NEXT PERMUTATION LEETCODE
void nextPermutation(vector<int>& nums) {
    int n = nums.size(), k, l;
    for (k = n - 2; k >= 0; k--) {
        if (nums[k] < nums[k + 1]) {
            break;
        }
    }
    if (k < 0) {
        reverse(nums.begin(), nums.end());
    } else {
        for (l = n - 1; l > k; l--) {
            if (nums[l] > nums[k]) {
                break;
            }
        } 
        swap(nums[k], nums[l]);
        reverse(nums.begin() + k + 1, nums.end());
    }
}

// QUESTION 6
// NEXT GREATER ELEMENT III LEETCODE
// THE IDEA IS SAME AS NEXT PERMUTATION
int nextGreaterElement(int n) {
    auto digits = to_string(n);
    next_permutation(begin(digits), end(digits));
    auto res = stoll(digits);
    return (res > INT_MAX || res <= n) ? -1 : res;
}

// QUESTION 7
// MAJORITY ELEMENT I LEETCODE
// O(N) TIME, O(1) SPACE
int majorityElement(vector<int>& arr) {
    int val = arr[0];
    int count = 1;
    
    for(int i = 1; i < arr.size(); i++) {
        if(val == arr[i]) 
            count++;
        else {
            if(count == 0) {
                val = arr[i];
                count = 1;
            }
            else 
                count--;
        }
    }
    
    return val;
}

// QUESTION 8
// MAJORITY ELEMENT II LEETCODE


int main(int argc, char** argv) {
    
}