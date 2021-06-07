#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// QUESTION 1
// SUBARRAY SUM EQUALS K LEETCODE
int subarraySumK(vector<int> &nums, int k) {
    unordered_map<int, int> prefixMap;
    int count = 0;
    prefixMap[0] = 1;
    int sum = 0;

    for(int j = 0; j < nums.size(); j++) {
        sum += nums[j];
        int tar = sum - k;

        if(prefixMap.find(tar) != prefixMap.end()) 
            count+= prefixMap[tar];
        prefixMap[sum]++;
    }

    return count;
}

// QUESTION 2
// SUBARRAY SUM DIVISIBLE BY K GFG
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> prefixMap;
    int sum = 0;
    int count = 0;
    prefixMap[0] = 1;

    for(int i = 0; i < nums.size(); i++) {
        sum += nums[i];
        int target = ((sum % k) + k) % k;

        if(prefixMap.find(target) != prefixMap.end())
            count += prefixMap[target];
        prefixMap[target]++;
    }
    
    return count;
}

// QUESTION 3
// SUBARRAY WITH EQUAL 0s AND 1s GFG


// QUESTION 4
// SUBSTRING WITH EQUAL 0s, 1s AND 2s GFG


// QUESTION 5 
// K CLOSEST POINTS TO ORIGIN LEETCODE


// QUESTION 6
// RABBITS IN FOREST LEETCODE


// QUESTION 7
// LONGEST CONSECUTIVE 1s


// QUESTION 8
// MINIMUM NUMBER OF REFUELLING SPOTS


int main(int argc, char** argv) {
    
}