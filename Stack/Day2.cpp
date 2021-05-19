#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;

// QUESTION 1
// CHECK WHETHER STRING OF PARENTHESES IS VALID LEETCODE
char closingChar(char ch) {
    if(ch == ')')
        return '(';
    if(ch == '}')
        return '{';
    if(ch == ']')
        return '[';
    if(ch == '>')
        return '<';
    return ' ';
}

bool validParentheses(string s) {

    stack<int> st;

    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '(' || s[i] == '[' || s[i] == '{' || s[i] == '<') {
            st.push(i);
        }

        else {
            char ch = closingChar(s[i]);
            if(s[st.top()] != ch) {}
                return false;
            st.pop();
        }
    }

    return st.size() == 0? true:false;
}

// QUESTION 2
// LONGEST VALID PARENTHESES LEETCODE
int longestValidParentheses(string s) {
    stack<int> st;
    int maxLen = -1e8;
    st.push(-1);

    for(int i = 0; i < s.length(); i++) {
        if(st.top() != -1 && s[i] == ')' && s[st.top()] == '(') {
            st.pop();
            maxLen = max(maxLen, (i - st.top()));
        }

        else 
            st.push(i);
    }

    return maxLen;
}

// QUESTION 3
// MINIMUM REVERSAL OF PARENTHESES TO MAKE STRING BALANCED GFG
// IN THIS WE CONSIDER 4 CONDITIONS, FIRST USE LONGEST VALID PARENTHESES TO REMOVE
// ALL BALANCED PAIRS. THEN CONSIDER FOUR CASES ON THE COUNT OF OPENING AND CLOSING PARENTHESES
// 1. ODD ODD
// 2. EVEN ODD
// 3. ODD EVEN
// 4. EVEN EVEN
// FOR CASES 2 AND 3, THE PARENTHESES CANNOT BE BALANCED BY REVERSING
// FOR CASES 1 AND 4, FIND FORMULA
// EVEN CASE -> CP/2 + OP/2
// ODD CASE -> (CP - 1)/2 + (OP - 1)/2 + 2
int minReversal(string s) {
    stack<int> st;
    st.push(-1);

    for(int i = 0; i < s.length(); i++) {
        if(st.top() != -1 && s[i] == ')' && s[st.top()] == '(')
            st.pop();

        else 
            st.push(i);
    }

    int cp = 0; // COUNT OF CLOSING PARENTHESES
    int op = 0; // COUNT OF OPENING PARENTHESES
    while(st.top() != -1) {
        if(s[st.top()] == ')')
            cp++;
        else 
            op++;
        st.pop();
    }

    if((op % 2 == 0 && cp % 2 != 0) || (op % 2 != 0 && cp % 2 == 0))
        return -1;

    else if(op % 2 == 0 && cp % 2 == 0) 
        return cp/2 + op/2;

    return (cp-1)/2 + (op-1)/2 + 2;
}

// QUESTION 4
// MINIMUM ADD TO MAKE PARENTHESES VALID LEETCODE 
int minAddOfParentheses(string s) {
    stack<int> st;
    st.push(-1);

    for(int i = 0; i < s.length(); i++) {
        if(st.top() != -1 && s[i] == ')' && s[st.top()] == '(')
            st.pop();

        else 
            st.push(i);
    }

    return st.size();
}

// QUESTION 5
// LENGTH OF LONGEST UNBALANCED SUBSEQUENCE
// IF STRING IS BALANCED ANSWER IS STRING.LENGTH() - 1
// IF STRING IS UNBALANCED ANSWER IS STRING.LENGTH()
// JUST USE ISVALID FUNCTION TO CHECK WHETHER STRING IS BALANCED OR NOT

// QUESTION 6
// REMOVE K DIGITS LEETCODE
string removeKdigits(string s, int k) {

    stack<int> st;
    string ans = "";
    for(int i = 0; i < s.length(); i++) {
        while(st.size() != 0 && int(s[st.top()] - '0') >= int(s[i] - '0') && k > 0) {
            st.pop();
            k--;
        }

        st.push(i);
    }

    while(k > 0) {
        st.pop();
        k--;
    }

    while(st.size() != 0) {
        ans = s[st.top()] + ans; 
        st.pop();
    }

    while(ans[0] == '0') {
        ans = ans.substr(1);
    }

    return ans;
}

// QUESTION 7
// FIRST NEGATIVE INTEGER IN EVERY WINDOW OF SIZE K GFG
vector<int> negativeInK(vector<int> &arr, int k) {

    vector<int> ans(arr.size() - k + 1, 0);
    int temp = k;
    int negIdx = -1;
    int i = arr.size() - 1;
    while(temp > 0) {
        if(arr[i] < 0)
            negIdx = i;
        i--;
        temp--;
    }

    ans[i + 1] = negIdx == -1 ? 0: arr[negIdx]; 

    for(; i >= 0; i--) {
        if(arr[i] < 0)
            negIdx = i;
        
        if(negIdx <= i + k - 1) 
            ans[i] = arr[negIdx];

        else 
            ans[i] = 0;
    }

    return ans;
}

// QUESTION 8
// MAXIMUM SUM OF SMALLEST AND SECOND SMALLEST NUMBER IN AN ARRAY GFG
int maxSumOfSmallAndSecSmall(vector<int> &arr) {

    if(arr.size() < 2)
        return -1;

    int maxSum = -1e8;

    for(int i = 0; i < arr.size(); i++) {
        if(i + 1 < arr.size()) 
            maxSum = max(maxSum, arr[i] + arr[i + 1]);
    }

    return maxSum;
}

// QUESTION 9
// REVERSE FIRST K ELEMENTS IN A QUEUE GFG
void kReverse(queue<int> &q, int k) {
    stack<int> st;

    for(int i = 0; i < k; i++) {
        st.push(q.front());
        q.pop();
    }

    while(st.size() != 0) {
        q.push(st.top());
        st.pop();
    }

    for(int i = 0; i < q.size() -k; i++) {
        int k = q.front();
        q.pop();
        q.push(k);
    }
}

// QUESTION 10
// TO IMPLEMENT K STACKS IN AN ARRAY OF GIVEN SIZE GFG
class KStacks {
    int *arr;
    int *top;
    int *next;
    int n, k;
    int free;

    public:
    KStacks(int n, int k);

    bool isFull() {
        return (free == -1);
    }

    void push(int data, int sn);
    int pop(int sn);
    bool isEmpty(int sn) {
        return (top[sn] == -1);
    }
};

KStacks::KStacks(int k1, int n1) {
    k = k1;
    n = n1;

    arr = new int[n];
    top = new int[k];
    next = new int[n];

    for(int i = 0; i < k; i++) {
        top[i] = -1;
    }

    free = 0;
    for(int i = 0; i < n-1; i++) {
        next[i] = i + 1;
    }
    next[n - 1] = -1;
}

void KStacks::push(int data, int sn) {
    if(isFull()) {
        cout << "Stack Overflow\n";
        return;
    } 

    arr[free] = data;
    int addIdx = free;
    free = next[addIdx];
    next[addIdx] = top[sn];
    top[sn] = addIdx;
}

int KStacks::pop(int sn)
{
    if (isEmpty(sn))
    {
         cout << "Stack Underflow\n";
         return 1e8;
    }

    int remIdx = top[sn];
    top[sn] = next[remIdx];
    next[remIdx] = free;
    free = remIdx;
    return arr[remIdx];
}

int main(int argc,char** argv) {
    
    vector<int> arr = {4, 3, 1, 5, 6};
    // int k = 3;
    // vector<int> ans = negativeInK(arr, k);
    // for(int i : ans) {
    //     cout << i << " ";
    // }

    // cout << maxSumOfSmallAndSecSmall(arr);
}