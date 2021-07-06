#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// QUESTION 1
// REARRANGE CHARACTERS IN A STRING SUCH THAT NO TWO ADJACENT ARE SAME
string rearrange(string s) {
    unordered_map<char,int> mp;
    for(char ch : s)
        mp[ch]++;

    priority_queue<pair<int,char>> pq;

    for(auto l: mp)
        pq.push({l.second,l.first});
    
    pair<int,char> bl = {-1,'#'};
    string ans = "";
    while(pq.size() != 0) {
        pair<int,char> rp = pq.top();
        pq.pop();
        ans += rp.second;
        if(bl.first > 0) 
            pq.push(bl);
        rp.first--;
        bl = rp;
    }
    
    return ans.length() == s.length() ? ans : "";
}

// QUESTION 2
//

// QUESTION 3
//

// QUESTION 4
// Kth SMALLEST ELEMENT IN A SORTED MATRIX LEETCODE

// QUESTION 5
// Kth SMALLEST PRIME FRACTION LEETCODE

// QUESTION 6
//

int main(int argc,char** argv) {

}