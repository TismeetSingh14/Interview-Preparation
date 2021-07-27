#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

// int main(int argc, char** argv) {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);
//     int t = 1;
//     cin >> t;
//     while(t-- > 0) {
//         string s;
//         cin >> s;
//         string ans = "";
//         int i = 0;
//         while(i < s.length()) {
//             if(s[i] == 'p' && i + 3 < s.length() && s.substr(i, 4) == "plus") {
//                 ans += '+';
//                 i = i + 3;
//             }
 
//             else if(s[i] == 'm' && i + 4 < s.length() && s.substr(i, 5) == "minus") {
//                 ans += '-';
//                 i = i + 4;
//             }

//             else 
//                 ans += s[i];
//             i++;
//         }

//         cout << ans << "\n";
//     }
    
// } 

// int main(int argc,char** argv) {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);
//     int t = 1;
//     cin >> t;
//     while(t-- > 0) {
//         int n;
//         cin >> n;
//         vector<int> arr(n, 0);
//         for(int i = 0; i < n; i++)
//             cin >> arr[i];
//         int x;
//         cin >> x;

//         int maxEle = arr[0];
//         int minEle = arr[0];

//         int days = 1;
//         for(int i = 1; i < arr.size(); i++) {
//             int diff1 = abs(arr[i] - maxEle);
//             int diff2 = abs(arr[i] - minEle);

//             if(diff1 > x || diff2 > x) {
//                 days++;
//                 maxEle = arr[i];
//                 minEle = arr[i];
//             }

//             maxEle = max(maxEle, arr[i]);
//             minEle = min(minEle, arr[i]);
//         }

//         cout << days <<  " ";
//     }
// }

// bool isSafe(vector<int> &arr) {
//     bool result = false;
//     int n = arr.size();
//     if (arr[1] > arr[0] && arr[1] > arr[2]) {
//         for (int i = 1; i < n - 1; i += 2) {
 
//             if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
//                 result = true;
//             }

//             else {
//                 result = false;
//                 break;
//             }
//         }
 
//         if (result == true && n % 2 == 0) {
//             if (arr[n - 1] <= arr[n - 2]) {
//                 result = false;
//             }
//         }
//     }

//     else if (arr[1] < arr[0] && arr[1] < arr[2]) {
//         for (int i = 1; i < n - 1; i += 2) {
 
//             if (arr[i] < arr[i - 1] && arr[i] < arr[i + 1]) {
//                 result = true;
//             }
//             else {
//                 result = false;
//                 break;
//             }
//         }

//         if (result == true && n % 2 == 0) {
//             if (arr[n - 1] >= arr[n - 2]) {
//                 result = false;
//             }
//         }
//     }
 
//     return result;
// }

// int main(int argc,char** argv) {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);
//     int t = 1;
//     cin >> t;
//     while(t-- > 0) {
//         int n;
//         cin >> n;
//         vector<int> arr(n, 0);
//         for(int i = 0; i < n; i++)
//             cin >> arr[i];

//         if(isSafe(arr) || arr.size() <= 2) {
//             cout << 0 << "\n";
//             continue;
//         }
        
//         vector<int> temp;
//         int count = 0;
//         for(int i = 0; i < arr.size(); i++) {
//             temp = arr;
//             temp.erase(i + temp.begin());
//             if(isSafe(temp))
//                 count++;
//         }

//         if(count == 0)
//             cout << -1 << "\n";
        
//         else 
//             cout << count << "\n";
//     }
// }

int main(int argc,char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin >> t;
    while(t-- > 0) {
        int n;
        cin >> n;
        vector<int> arr(n, 0);
        
    }
}