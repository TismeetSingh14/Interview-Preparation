#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <cmath>
using namespace std;

// QUESTION 1
// MEXIMIZATION CODEFORCES
void meximization(vector<int> &arr) {
    vector<int> freq(101, 0);

    for(int i = 0; i < arr.size(); i++)
        freq[arr[i]]++; 

    int j = 0;
    for(int i = 0; i < freq.size(); i++) {
        if(j < arr.size() && freq[i] > 0) {
            arr[j] = i;
            freq[i]--;
            j++;
        }
    }

    for(int i : arr)
        cout << i << " ";
}

// QUESTION 2
// K-LCM EASY VERSION CODEFORCES
void kLCM(int n) {
    if(n%8 == 0) {
        cout << n/2 << " " << n/4 << " " << n/4;
        return;
    }

    if(n % 2 != 0) {
        cout << 1 << " " << n/2 << " " << n/2;
        return;
    }

    if((n - 2) % 2 == 0) {
        cout << (n - 2)/2 << " " << (n - 2)/2 << " " << 2;
        return;
    }

    if((n - 2) % 2 != 0) {
        cout << (n - 4)/2 << " " << (n - 4)/2 << " " << 2;
    }
}

// QUESTION 3
// K-LCM HARD VERSION CODEFORCES
void kLCM2(int n, int k) {
    while(k != 3) {
        cout << 1 << " ";
        n--;
        k--;
    }

    if(n%8 == 0) {
        cout << n/2 << " " << n/4 << " " << n/4;
        return;
    }

    if(n % 2 != 0) {
        cout << 1 << " " << n/2 << " " << n/2;
        return;
    }

    if((n - 2) % 2 == 0) {
        cout << (n - 2)/2 << " " << (n - 2)/2 << " " << 2;
        return;
    }

    if((n - 2) % 2 != 0) {
        cout << (n - 4)/2 << " " << (n - 4)/2 << " " << 2;
    }
}

// QUESTION 4
// CONSECUTIVE NUMBERS SUM LEETCODE
int numbersSum(int n) {
    int k = sqrt(2*n) + 1;

    int ans = 0;
    for(int i = 0; i < k; i++) {
        if((n - ((i-1)*1/2))%i == 0)
            ans++;
    }

    return ans;
}

// QUESTION 5
// FAST EXPONENTIATION POW(X,N) O(logN)
int powerFE(int x, int n) {
    int temp = 1;
    while(n > 1) {
        if(n % 2 != 0) {
            temp*= x;
            n--;
        }

        x = x*x;
        n = n/2;
    }

    return temp*x;
}

// QUESTION 6
// SIEVE OF ERATOSTHENES GFG
// USED TO FIND PRIME NUMBERS FROM 1 TO N
// TIME COMPLEXITY O(NloglogN)
void sieveOfEratosthenes(int n) {
    int k = sqrt(n);
    vector<bool> vis(n + 1, false); 
    vis[0] = vis[1] = true;

    for(int i = 2; i <= k; i++) {
        if(vis[i] == false) {
            for(int j = i*i; j <= n; j +=i)
                vis[j] = true; 
        }
    }

    for(int i = 1; i < vis.size(); i++) {
        if(vis[i] == false)
            cout << i << " ";
    }
}

// QUESTION 7
// SEGMENTED SIEVE
// HANDLE FOR THE CASE WHEN THE SQRT PRIMES LIE IN THE GIVEN RANGE
vector<int> sieve(int n) {
    int k = sqrt(n);
    vector<int> ans;
    vector<bool> vis(n + 1, false); 
    vis[0] = vis[1] = true;

    for(int i = 2; i <= k; i++) {
        if(vis[i] == false) {
            for(int j = i*i; j <= n; j +=i)
                vis[j] = true; 
        }
    }

    for(int i = 1; i < vis.size(); i++) {
        if(vis[i] == false)
            ans.push_back(i);
    }

    return ans;
}

void segmentedSieve(int ll, int ul) {
    vector<int> primes = sieve(sqrt(ul));
    vector<int> vis(ul-ll+1, false);
    if(ll == 1 || ll == 0)
        vis[0] = true;

    for(int i = 0; i < primes.size(); i++) {
        for(int j = ceil(ll/primes[i])* primes[i]; j <= ul; j+= primes[i]) {
            if(j == primes[i])
                continue;
            vis[j - ll] = true;
        }
    }

    for(int i = 0; i < vis.size(); i++) {
        if(vis[i] == false) 
            cout << i + ll << " ";
    }
}

// QUESTION 8
// WIGGLE SORT LEETCODE/LINTCODE
vector<int> wiggleSort(vector<int> &arr) {
    for(int i = 0; i < arr.size(); i++) {
        if(i % 2 == 0) {
            if(i + 1 < arr.size() && arr[i] > arr[i + 1])
                swap(arr[i], arr[i + 1]);
        }

        if(i % 2 != 0) {
            if(i + 1 < arr.size() && arr[i] < arr[i + 1]) 
                swap(arr[i], arr[i + 1]);
        }
    }

    for(int i : arr)
        cout << i << " ";

    return arr;
}


// QUESTION 9
// FIND THE NUMBER OF JUMPS TO REACH X IN THE NUMBER LINE FROM ZERO GFG
int minSteps(int x) {
    int i = 0;
    int sum = 0;
    while(x > sum) { 
        i++;
        sum = sum + i;
    }

    int diff = abs(sum - x);
    if(diff % 2 != 0) {
        i++;
        diff = abs(sum + i - x);
        if(diff % 2 != 0) {
            i++;
            diff = abs(sum + i - x);
        }
    }
    return i;
}

// QUESTION 10
// MAXIMUM SWAP LEETCODE
int maxSwap(int num) {
    string n = to_string(num);
    
    unordered_map<int, int> last;
    for (int i=0; i<n.size(); i++)
        last[n[i] - '0'] = i;
    
    for (int i=0; i < n.size(); i++) {
        for (int j = 9; j > n[i]-'0'; j--) {
            if (last[j] > i) {
                swap(n[last[j]], n[i]);
                return stoi(n);
            }
        }
    }
    return stoi(n);
}

int main(int argc, char** argv) {
    vector<int> arr = {3,5,2,1,6,4};
    // meximization(arr);
    // cout << powerFE(2,5);
    // sieveOfEratosthenes(30);
    // segmentedSieve(22,100);
    // wiggleSort(arr);
    // cout << minSteps(14);
}