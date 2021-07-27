#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// QUESTION 1
// BINARY SEARCH
int binSearch(vector<int> &arr, int data) {
    int lo = 0;
    int hi = arr.size() - 1;

    while(lo <= hi) {
        int mid = lo + (hi - lo)/2;

        if(arr[mid] == data)
            return mid;
        
        else if(arr[mid] < data)
            lo = mid + 1;
        
        else 
            hi = mid - 1;
    }

    return -1;
}

// QUESTION 2
// MEDIAN OF TWO SORTED ARRAYS LEETCODE
double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
    if(a.size() > b.size())
        swap(a,b);
    int lo = 0;
    int hi = a.size();
    int noe = (a.size() + b.size() + 1)/2;

    while(lo <= hi) {
        int mid = lo + (hi - lo)/2;
        int ele1 = mid;
        int ele2 = noe - mid;

        int maxA = ele1 <= 0 || ele1 > a.size() ? -1e9 : a[ele1 - 1];
        int maxB = ele2 <= 0 || ele2 > b.size() ? -1e9 : b[ele2 - 1];
        int minA = ele1 <=-1 || ele1 >= a.size()? 1e9 : a[ele1];
        int minB = ele2 <=-1 || ele2 >= b.size()? 1e9 : b[ele2];

        if(maxA > minB)
            hi = mid - 1;

        else if(maxB > minA)
            lo = mid + 1;

        else {
            if((a.size() + b.size() + 1) % 2 == 1)
                return (max(maxA, maxB) + min(minB, minA))/2.0;
            return max(maxA, maxB);
        }
    } 

    return -1;
}

// QUESTION 3
// CAPACITY TO SHIP PACKAGES WITHIN D DAYS LEETCODE
int capToShip(vector<int> &arr, int d) {
    int maxVal = 0;
    int sum = 0;
    for(int i: arr) {
        sum += i;
        maxVal = max(maxVal, i);
    }

    int lo = maxVal;
    int hi = sum;

    while(lo < hi) {
        int mid = lo + (hi-lo)/2;

        int days = 1;
        int currSum = 0;
        for(int i = 0; i < arr.size(); i++) {
            if(currSum + arr[i] > mid) {
                currSum = 0;
                days++;
            }

            currSum += arr[i];
        }

        if(days > d)
            lo = mid + 1;
        
        else 
            hi = mid;
    }

    return lo;
}

// QUESTION 4
// KOKO EATING BANANAS LEETCODE 
int minEatingSpeed(vector<int>& piles, int h) {
    int lo = 1;
    int hi = 0;
    int ans = 1e9;
    for(int i:piles)
        hi = max(hi,i);
    
    while(lo < hi) {
        int mid = lo + (hi - lo)/2;
        
        int res = 0;
        for(int i:piles) {
            res = res + (i + mid - 1)/mid;
        }
        
        if(res > h) 
            lo = mid + 1;
        
        else
            hi = mid;
    }
    
    return lo;
}

// QUESTION 5
// SMALLEST DIVISOR GIVEN A THRESHOLD LEETCODE
int smallestDivisor(vector<int>& nums, int h) {
    int lo = 1;
    int hi = 0;
    for(int i:nums)
        hi = max(hi,i);

    while(lo < hi) {
        int mid = lo + (hi - lo)/2;

        int res = 0;
        for(int i:nums) {
            res = res + (i + mid - 1)/mid;
        }

        if(res > h) 
            lo = mid + 1;

        else
            hi = mid;
    }

    return lo;
}

// QUESTION 6
// PAINTER'S PARTITION PROBLEM INTERVIEWBIT
int paint(int a, int b, vector<int> &arr) {
    int maxVal = 0;
    int sum = 0;
    for(int i: arr) {
        sum += i;
        maxVal = max(maxVal, i);
    }

    int lo = maxVal;
    int hi = sum;

    while(lo < hi) {
        int mid = lo + (hi-lo)/2;

        int days = 1;
        int currSum = 0;
        for(int i = 0; i < arr.size(); i++) {
            if(currSum + arr[i] > mid) {
                currSum = 0;
                days++;
            }

            currSum += arr[i];
        }

        if(days > a)
            lo = mid + 1;
        
        else 
            hi = mid;
    }

    return lo*b;
}

void solve() {
    vector<int> arr = {1,10};
    cout << paint(2, 5, arr);
}

int main(int arc,char** argv) {
    solve();
}