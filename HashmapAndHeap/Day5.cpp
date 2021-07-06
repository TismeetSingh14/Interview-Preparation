#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// QUESTION 1
// INSERT DELETE GET RANDOM O(1) - DUPLICATES ALLOWED LEETCODE
class RandomizedCollection {
public:
    unordered_map<int,unordered_set<int>> m;
    vector<int> arr;
    RandomizedCollection() {

    }
    
    bool insert(int val) {
        arr.push_back(val);
        m[val].insert(arr.size() - 1);
        return m[val].size() == 1 ? true:false;
    }
    
    bool remove(int val) {
        if(m.find(val) == m.end())
            return false;
        int remIdx;
        for(int k:m[val]) {
            remIdx = k;
            break;
        }
        m[val].erase(remIdx);
        arr[remIdx] = arr.back();
        m[arr.back()].insert(remIdx);
        m[arr.back()].erase(arr.size() - 1);
        arr.pop_back();
        if(m[val].size() == 0)
            m.erase(val);
        return true;
    }
    
    int getRandom() {
        return arr[rand() % arr.size()];
    }
};

// QUESTION 2
// FIND ALL ANAGRAMS IN A STRING LEETCODE
vector<int> findAnagrams(string s, string p) {
    unordered_map<char,int> mp;
    for(char ch: p)
        mp[ch]++;

    unordered_map<char,int> ms;
    int mtc = 0;
    int i = 0;
    while(i < p.length()) {
        ms[s[i]]++;
        if(ms[s[i]] <= mp[s[i]])
            mtc++;
        i++;
    }
    vector<int> ans;
    if(mtc == p.length())
        ans.push_back(i-p.length());

    while(i < s.length()) {
        ms[s[i]]++;
        if(ms[s[i]] <= mp[s[i]])
            mtc++;
        ms[s[i-p.length()]]--;
        if(ms[s[i-p.length()]] < mp[s[i-p.length()]])
            mtc--;
        if(mtc == p.length())
            ans.push_back(i-p.length() + 1);
        i++;
    }

    return ans;
}

// QUESTION 3
// CHECK IF ANY ANAGRAM OF A STRING IS PALINDROME OR NOT GFG
bool isAnagramPalindrome(string s) {
    unordered_map<char,int> mp;

    for(char ch: s)
        mp[ch]++;
    
    int odd = 0;
    for(auto k:mp) {
        if(k.second % 2 != 0)
            odd++;
    }

    return odd == 1 || odd == 0;
}

// QUESTION 4
// MINIMUM WINDOW SUBSTRING LEETCODE
string minWindow(string s, string t) {
    if(s.length() < t.length())
        return "";
    unordered_map<char, int> mt;
    unordered_map<char, int> ms;

    for(char ch:t)
        mt[ch]++; 

    int matchCount = 0;
    int j = 0;
    int i = 0;
    int si,ei;
    int minLen = 1e9;

    while(j < s.length()) {
        ms[s[j]]++;
        if(ms[s[j]] <= mt[s[j]])
            matchCount++;

        if(matchCount == t.length()) {
            while(matchCount == t.length() && i <= j) {
                if(minLen > j - i + 1) {
                    minLen = j - i + 1;
                    si = i;
                    ei = j;
                }

                ms[s[i]]--;
                if(ms[s[i]] < mt[s[i]])
                    matchCount--;
                i++;
            }
        }
        j++;
    }
    
    if(minLen == 1e9)
        return "";
    string ans = "";
    for(int i = si; i<=ei;i++)
        ans += s[i];

    return ans;
}


// QUESTION 5
// GROUP ANAGRAMS LEETCODE
string strSort(string s) {
    int counter[26] = {0};
    for (char c : s) {
        counter[c - 'a']++;
    }
    string t;
    for (int c = 0; c < 26; c++) {
        t += string(counter[c], c + 'a');
    }
    return t;
}

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> ans;
    unordered_map<string, vector<string>> map;
    
    for(int i = 0; i < strs.size(); i++) {
        string k = strSort(strs[i]);;
        map[k].push_back(strs[i]);
    }
    
    for(auto k: map)
        ans.push_back(k.second);
    
    return ans;
}

// QUESTION 6
// LENGTH OF LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS GFG
int longestSubstringDistinctChar(string s) {
    unordered_map<char,int> mp;

    int i = 0;
    int len = 0;
    for(int j = 0; j < s.length(); j++) {
        i = max(i, mp[s[j]] + 1);
        len = max(len, j - i + 1);
        mp[s[j]] = j;    
    }

    return len;
}

// QUESTION 7
// SMALLEST SUBARRAY WITH ALL OCCURENCES OF A MOST FREQUENT ELEMENT GFG
void smallestMFE(vector<int> &arr) {
    unordered_map<int,pair<int,pair<int,int>>> mp;

    for(int i = 0; i < arr.size(); i++) {
        if(mp.find(arr[i]) == mp.end()) {
            pair<int,pair<int,int>> k = {1,{i, i}};
            mp[arr[i]] = k;
        }

        mp[arr[i]].first++;
        mp[arr[i]].second.second = i;
    }

    int mfe = -1;
    pair<int,int> range;
    for(auto k:mp) {
        if(k.second.first > mfe) {
            mfe = k.second.first;
            range = k.second.second;
        }
    }

    for(int i = range.first; i <= range.second; i++) {
        cout << arr[i] << " ";
    }
}

// QUESTION 8
// FIND ANAGRAM MAPPINGS LEETCODE
vector<int> anagramMapping(vector<int> &a, vector<int> &b) {
    unordered_map<int,vector<int>> mp;

    for(int i = 0; i < b.size(); i++) 
        mp[b[i]].push_back(i);
    
    vector<int> res(a.size(), -1);
    for(int i = 0; i < a.size(); i++) {
        int remIdx = mp[a[i]].back();
        mp[a[i]].pop_back();
        res[i] = remIdx;
    }

    return res;
}

// QUESTION 9
// K ANAGRAMS GFG
bool isK_Anagram(string s1,string s2, int k) {
    if(s1.length() != s2.length())
        return false;

    unordered_map<char, int> mp;

    for(char ch: s1) 
        mp[ch]++;

    for(char ch:s2)
        mp[ch]--;
    
    int count = 0;
    for(auto k : mp) {
        if(k.second > 0)
            count++;
    }

    return count <= k; 
}

int main(int argc,char** argv) {
    // cout << longestSubstringDistinctChar("geeksforgeeks");
    // vector<int> arr = {4, 1, 0, -2, 2, -1, -3, 3};
    // smallestMFE(arr);
    // vector<int> a = {12,28,46,32,50,12};
    // vector<int> b = {50,12,32,46,12,28};
    // vector<int> ans = anagramMapping(a,b);
    // for(int k:ans)
    //     cout << k << " ";
    // string s = "geeks";
    // string t = "eggkf";
    // cout << isK_Anagram(s,t,1);
}