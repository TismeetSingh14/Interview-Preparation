#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

// QUESTION 1
// MINIMUM DOMINO ROTATIONS FOR EQUAL ROW LEETCODE
int minDominoRotations(vector<int>& A, vector<int>& B) {
    int Acount_1 = 0;
    int Acount_2 = 0;
    int Bcount_1 = 0;
    int Bcount_2 = 0;

    int A0 = A[0];
    int B0 = B[0];

    for(int i = 0; i < A.size(); i++) {
        if(A[i] == A0 && B[i] == A0)
            continue;
        if(A[i] != A0 && B[i] == A0)
            Acount_1++;
        else if(B[i] != A0 && A[i] == A0)
            Bcount_1++;
        else {
            Acount_1 = INT_MAX;
            Bcount_1 = INT_MAX;
            break;
        }
    }

    for(int i = 0; i < A.size(); i++) {
        if(A[i] == B0 && B[i] == B0)
            continue;
        if(A[i] != B0 && B[i] == B0)
            Acount_2++;
        else if(B[i] != B0 && A[i] == B0)
            Bcount_2++;
        else {
            Acount_2 = INT_MAX;
            Bcount_2 = INT_MAX;
            break;
        }
    }

    int myAns = min(min(Acount_1, Acount_2), min(Bcount_1, Bcount_2));
    return myAns == INT_MAX ? -1:myAns;
}

// QUESTION 2
// MULTIPLY STRINGS LEETCODE
string multiplyStrings(string s1, string s2) {
    if(s1 == "0" || s2 == "0")
        return "0";
    int j = s1.length() - 1;
    vector<int> arr(s1.length() + s2.length(), 0);
    while(j >= 0) {
        int i = s2.length() - 1;
        while(i >= 0) {
            int quoIdx = i+j;
            int remIdx = i+j+1;
            int val = (s2[i] - '0')*(s1[j] - '0');
            int finalVal = val + arr[remIdx];
            int quo = finalVal/10;
            int rem = finalVal%10;
            arr[remIdx] = rem;
            arr[quoIdx] += quo;
            i--;
        }
        j--;
    }

    string s = "";
    int i = 0;
    while(arr[i] == 0)
        i++;
    for(; i < arr.size(); i++)
        s = s + char(arr[i] + '0');

    return s;
}

// QUESTION 3
// TWO SUM GFG/LEETCODE
void twoSum(vector<int> &arr, int target) {
    sort(arr.begin(), arr.end());
    int li = 0;
    int ri = arr.size() - 1;

    while(li < ri) {
        int sum = arr[li] + arr[ri];
        if(sum == target) {
            cout << li << " " << ri;
            li++;
            ri++;
        } 

        else if(sum < target) 
            li++;
        else 
            ri--;
    }
}

// QUESTION 4 
// TWO DIFFERENCE GFG
void twoDiff(vector<int> &arr, int target) {
    sort(arr.begin(), arr.end());
    int i = 0; 
    int j = 0;

    while(j < arr.size()) {
        int diff = arr[j] - arr[i];

        if(diff == target) {
            cout << i << " " << j;
            return;
        }

        else if(diff < target)
            j++;

        else 
            i++;
    }
} 

// QUESTION 5
// BOATS TO SAVE PEOPLE LEETCODE
int numRescueBoats(vector<int>& arr, int limit) {
    sort(arr.begin(), arr.end());
    
    int i = 0;
    int j = arr.size() - 1;
    
    int numBoats = 0;
    while(i < j) {
        int sum = arr[i] + arr[j];
        if(sum <= limit) {
            arr[i] = 0;
            arr[j] = 0;
            i++;
            j--;
            numBoats++;
        }
        
        else 
            j--;
    }
    
    for(int i = 0; i < arr.size(); i++)
        if(arr[i] != 0)
            numBoats++;
    return numBoats;
}

// QUESTION 6
// SMALLEST RANGE COVERING ELEMENTS FROM K LISTS


// QUESTION 7
// MAXIMUM PRODUCT SUBARRAY LEETCODE
int maxProduct(vector<int>& nums) {
    int cmax = 1;
    int omax = -1e9;
    bool flag  = false;
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i] == 0) {
            cmax = 1;
            flag = true;
            continue;
        }
        
        cmax = cmax*nums[i];
        omax = max(cmax, omax);
    }
    
    cmax = 1;
    for(int i = nums.size() - 1; i >= 0; i--) {
        if(nums[i] == 0) {
            cmax = 1;
            continue;
        }
        
        cmax = cmax*nums[i];
        omax = max(cmax, omax);
    }
    
    if(flag) {
        if(omax < 0)
            omax = 0;
    }
    
    return omax;
}

// QUESTION 9
// REVERSE VOWELS IN A STRING
 bool isVowel(char ch) {
    if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
        return true;
    if(ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
        return true;
    return false;
}

string reverseVowels(string s) {
    if(s.length() < 2)
        return s;
    int j = s.length() - 1;
    int i = 0;
    
    while(i < j) {
        if(!isVowel(s[i]) && !isVowel(s[j])) {
            i++;
            j--;
        }
        
        else if(isVowel(s[i]) && !isVowel(s[j])) {
            while(i < j && !isVowel(s[j]))
                j--;
        }
        
        else if(isVowel(s[j]) && !isVowel(s[i])) {
            while(i < j && !isVowel(s[i]))
                i++;
        }
        
        else {
            swap(s[i], s[j]);
            i++;
            j--;
        }
    }
    
    return s;
}

int main(int argc, char** argv) {
    
}