#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// QUESTION 1
// MEDIAN OF DATASTREAM LEETCODE
class MedianFinder {
public:
    
    priority_queue<int, vector<int>, greater<int>> pqm; 
    priority_queue<int> pqM;
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(pqm.size() == pqM.size()) {
            pqm.push(num);
            int k = pqm.top();
            pqm.pop();
            pqM.push(k);
        }

        else {
            pqM.push(num);
            int k = pqM.top();
            pqM.pop();
            pqm.push(k);
        }
    }
    
    double findMedian() {
        if(pqm.size() == pqM.size())
            return (pqm.top() + pqM.top())/2.0;
        
        else 
            return pqM.top();
    }
};

// QUESTION 2
// KTH SMALLEST PRIME FRACTION LEETCODE
vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
    double lo = 0.0;
    double hi = 1.0;
    int n = arr.size();

    while(true) {
        double mid = lo + (hi-lo)/2;

        int count = 0;
        int i = 0;
        int j = arr.size() - 1;
        int num = 0;
        int den = 1;

        while(i < arr.size()) {
            while(j > 0 && arr[i]/double(arr[n-j]) > mid) {
                j--;
            }
            if(j > 0 && num*arr[n-j] < arr[i]*den) {
                num = arr[i];
                den = arr[n-j];
            }
            count += j;
            i++;
        }

        if(count < k) 
        lo = mid;

        else if(count == k)
            return {num, den};

        else 
            hi = mid;
    }

    return {};
}

// QUESTION 3
// SEARCH IN A ROTATED SORTED ARRAY LEETCODE
int findPivot(vector<int> &arr) {
    int n = arr.size();
    int lo = 0;
    int hi = n-1;

    while(lo < hi) {
        int mid = lo + (hi - lo)/2;

        if(arr[mid] > arr[hi])
            lo = mid + 1;
        
        else 
            hi = mid;
    }

    return lo;
}

int binarySearch(vector<int> &nums, int target, int li, int ri) {
    while(li <= ri) {
        int mid = li + (ri-li)/2;
        
        if(nums[mid] == target)
            return mid;
        
        else if(nums[mid] < target) 
            li = mid + 1;
        
        else
            ri = mid - 1;
    }
    
    return -1;
}

int search(vector<int>& nums, int target) {        
    int pivot = findPivot(nums) - 1;
    
    int a = binarySearch(nums, target, 0, pivot);
    int b = binarySearch(nums,target, pivot + 1, nums.size() - 1);
    
    return a == -1? b:a;
}

// QUESTION 4
// FIND MINIMUM IN A ROTATED SORTED ARRAY LEETCODE
int findPivot(vector<int> &arr) {
    int n = arr.size();
    int lo = 0;
    int hi = n-1;

    while(lo < hi) {
        int mid = lo + (hi - lo)/2;

        if(arr[mid] > arr[hi])
            lo = mid + 1;
        
        else 
            hi = mid;
    }

    return arr[lo];
}

int main(int argc,char** argv) {

}