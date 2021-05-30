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
vector<int> majorityElementII(vector<int> &arr) {
    int val1 = arr[0];
    int count1 = 1;
    int val2 = arr[0];
    int count2 = 0;

    for(int i = 1; i < arr.size(); i++) {
        if(val1 == arr[i] || val2 == arr[i]) {
            if(val1 == arr[i])
                count1++;
            else
                count2++;
            continue;
        }
        if(count1 == 0) {
            val1 = arr[i];
            count1++;
            continue;
        }

        if(count2 == 0) {
            val2 = arr[i];
            count2++;
            continue;
        }

        count1--;
        count2--;
    }

    int freq = arr.size()/3 + 1;
    int c1 = 0;
    int c2 = 0;
    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] == val1)
            c1++;
        if(arr[i] == val2)
            c2++;
    }

    vector<int> ans;
    if(c1 >= freq) 
        ans.push_back(val1);
    if(c2 >= freq && val1 != val2) 
        ans.push_back(val2);
    return ans;
}

// QUESTION 9
// MAJORITY ELEMENT GENERAL GFG
vector<int> majorityElementGeneral(vector<int> &arr, int k) {
    int freq = arr.size()/k + 1;
    unordered_map<int, int> map;
    vector<int> ans;

    for(int i = 0; i < arr.size(); i++)
        map[arr[i]]++;

    for(auto k:map)
        if(k.second >= freq)
            ans.push_back(k.first);

    return ans;
}

// QUESTION 10
// MAX CHUNKS TO MAKE ARRAY SORTED
int maxChunks(vector<int> &arr) {
    int num = 0;
    int maxEle = -1;
    for(int i = 0; i < arr.size(); i++) {
        maxEle = max(maxEle, arr[i]);
        if(maxEle == i)
            num++;
    }

    return num;
}

// QUESTION 11
// MAX CHUNKS TO MAKE ARRAY SORTED II LEETCODE
int maxChunksII(vector<int> &arr) {
    vector<int> prefixMax(arr.size(), 0);
    prefixMax[0] = arr[0];
    for(int i = 1; i <arr.size(); i++) {
        prefixMax[i] = max(prefixMax[i-1], arr[i]);
    }

    vector<int> suffixMin(arr.size(), 0);
    suffixMin[arr.size() - 1] = arr[arr.size() - 1];
    for(int i = arr.size() - 2; i >= 0; i--) {
        suffixMin[i] = min(suffixMin[i + 1], arr[i]);
    }

    int chunks = 0;
    for(int i = 0; i < arr.size() - 1; i++) {
        if(prefixMax[i] <= suffixMin[i+1]) 
            chunks++;
    }

    return chunks+1;
}

// QUESTION 12
// MAXIMUM PRODUCT OF THREE NUMBERS LEETCODE
int maxProduct(vector<int> &nums) {
    int max1 = -1e8;
    int max2 = -1e8;
    int max3 = -1e8;

    for(int n:nums) {
        if(n > max1) {
            max3 = max2;
            max2 = max1;
            max1 = n;
        }

        else if(n > max2) {
            max3 = max2;
            max2 = n;
        }

        else if(n > max3) {
            max3 = n;
        }
    }

    int min1 = 1e8;
    int min2 = 1e8;

    for(int n:nums) {
        if(n < min1) {
            min2 = min1;
            min1 = n;
        }

        else if(n < min2) {
            min2 = n;
        }
    }

    return max(min2*min1*max1, max1*max2*max3);
}

// QUESTION 13
// LARGEST NUMBER AT LEAST TWICE OF OTHERS LEETCODE
int dominantIndex(vector<int>& nums) {
    if(nums.size() < 2)
        return 0;
    int max2 = INT_MIN;
    int max1 = INT_MIN;
    int idx2 = -1;
    int idx1 = -1;
    for(int n: nums) {
        if(n > max1) {
            max2 = max1;
            max1 = n;
        }
        
        else if(n > max2) {
            max2 = n;
        }
    }
    if(max2*2 <= max1) {
        for(int i = 0; i < nums.size(); i++)
            if(max1 == nums[i])
                return i;
    }
    
    return -1;
}

// QUESTION 14
// PRODUCT OF ARRAY EXCEPT SELF LEETCODE 
vector<int> productExceptSelf(vector<int>& arr) {
    vector<int> ans(arr.size(), 1);

    ans[0] = arr[0];
    for(int i = 1; i < arr.size(); i++)
        ans[i] = ans[i-1]*arr[i];

    int suffProd = arr[arr.size() - 1];
    ans[ans.size() - 1] = ans[ans.size() - 2];
    for(int i = arr.size() - 2; i >= 1; i--) {
        ans[i] = ans[i-1]*suffProd;
        suffProd *= arr[i];
    }
    
    ans[0] = suffProd;
    return ans;
}

int main(int argc, char** argv) {
    
}