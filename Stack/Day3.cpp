#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// QUESTION 1
// TO IMPLEMENT K QUEUES IN AN ARRAY OF GIVEN SIZE GFG
class KQueues {
    int *arr;
    int *front;
    int *rear;
    int *next;
    int free;
    int n,k;
    public:

    KQueues(int n, int k);
    bool isFull() {return (free == -1);}
    void enqueue(int data, int qn);
    int dequeue(int qn);
    bool isEmpty(int qn) {return (front[qn] == -1);}
};

KQueues::KQueues(int k1, int n1) {
    k = k1, n = n1;
    arr = new int[n];
    front = new int[k];
    rear = new int[k];
    next = new int[n];
 
    for (int i = 0; i < k; i++)
        front[i] = -1;
 
    free = 0;
    for (int i=0; i<n-1; i++)
        next[i] = i+1;
    next[n-1] = -1;
}

void KQueues::enqueue(int data, int qn) {
    if (isFull()) {
        cout << "Queue Overflow\n";
        return;
    }
 
    int addIdx = free;
    free = next[addIdx];
    if (isEmpty(qn))
        front[qn] = addIdx;
    else
        next[rear[qn]] = addIdx;
    next[addIdx] = -1;
    rear[qn] = addIdx;
    arr[addIdx] = data;
}

int KQueues::dequeue(int qn) {
    if (isEmpty(qn)) {
         cout << "Queue Underflow\n";
         return 1e8;
    }

    int remIdx = front[qn];
    front[qn] = next[remIdx];
    next[remIdx] = free;
    free = remIdx;
    return arr[remIdx];
}

// QUESTION 2
// GAS STATION LEETCODE
int gasStation(vector<int> &gas, vector<int> &cost) {

    int sumGas = 0;
    int sumCost = 0;
    vector<int> prefix(gas.size(), 0);
    prefix[0] = gas[0] - cost[0];

    for(int i = 0; i < gas.size(); i++) {
        sumGas += gas[i];
        sumCost += cost[i];
        if(i > 0)
            prefix[i] = gas[i] - cost[i] + prefix[i - 1];
    }

    int minIdx = -1;
    int psf = 1e8;

    for(int i = 0; i < prefix.size(); i++) {
        if(psf > prefix[i]) {
            psf = prefix[i];
            minIdx = i;
        }
    }

    return sumGas >= sumCost ? (minIdx + 1)%(gas.size()) : -1;
}

// QUESTION 3
// A NEW WAY TO PRINT BINARY NUMBERS FROM 1 TO N
void printBinaryNumbers(int n) {
    queue<string> que;
    que.push("1");

    while(n-->0) {
        string f = que.front();
        que.pop();
        que.push(f + "0");
        que.push(f + "1");
        cout << f << "\n";
    }
}

// QUESTION 4
// REMOVE DUPLICATE LETTERS LEETCODE
string removeDuplicateLetters(string s) {
    stack<char> st;

    int freq[26] = {0};
    bool check[26] = {0};
    for(int i = 0; i < s.length(); i++) {
        freq[s[i] - 'a']++;
    }
    for(int i = 0; i < s.length(); i++) {
        if(check[s[i] - 'a'] == 0) {
            while(st.size() != 0 &&  ((st.top() - 'a') > (s[i] - 'a')) && freq[st.top() - 'a'] > 0) {
                char ch = st.top();
                st.pop();
                check[ch - 'a'] = 0;
            }
            
            st.push(s[i]);
            check[s[i] - 'a'] = 1;

        }
        freq[s[i]-'a']--;
    }

    string ans = "";
    while(st.size() != 0) {
        ans = st.top() + ans;
        st.pop();
    }

    return ans;
}

// QUESTION 5
// BACKSPACE STRING COMPARE LEETCODE
bool backspaceCompare(string s, string t) {
    int i = s.length() - 1;
    int j = t.length() - 1;
    int count1 = 0;
    int count2 = 0;
    while(i >= 0 && j >= 0) {
        while(i >= 0 && (s[i] == '#' || count1 > 0)) {
            if(s[i] == '#') 
                count1++;
            else
                count1--;
            i--;
        }
        
        while(j >= 0 && (t[j] == '#' || count2 > 0)) {
            if(t[j] == '#')
                count2++;
            else
                count2--;
            j--;
        }
        
        if(i >= 0 && j < 0)
            return false;
        
        if(j >= 0 && i < 0)
            return false;
        
        if(i >= 0 && j >= 0 && s[i] != t[j]) {
            return false;
        }            
        i--;
        j--;  
    }
    
    while(i>=0)
    {
        if(s[i]=='#'){i--;count1++;}
        else if(count1){i--;count1--;}
        else{return false;}
    }
    while(j>=0)
    {
        if(t[j]=='#'){j--;count2++;}
        else if(count2){j--;count2--;}
        else {return false;}
    }
    
    return true;
}

// QUESTION 6
// VALIDATE STACK SEQUENCES LEETCODE
bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    stack<int> st;
    
    int i = 0;
    int j = 0;
    
    while(i < pushed.size() && j < popped.size()) {
        st.push(pushed[i]);
        i++;
        while(st.size() != 0 && st.top() == popped[j]) {
            st.pop();
            j++;
        }
    }
    
    while(j < popped.size()) {
        if(st.top() == popped[j]) {
            st.pop();
            j++;
        }
        
        else
            return false;
    }
    return true;
}

// QUESTION 7
// TO EVALUATE INFIX EXPRESSION
int precedenceOf(char ch) {
    if(ch == '*' || ch == '/') 
        return 2;
    if(ch == '-' || ch == '+') 
        return 1;
    return 0;
}

int operate(char ch, int opd1, int opd2) {
    if(ch == '-')
        return opd2 - opd1;
    if(ch == '*') 
        return opd2 * opd1;
    if(ch == '+') 
        return opd2 + opd1;
    if(ch == '/')
        return opd2 / opd1;
}

int solvingInfixExpression(string s) {
    stack<int> opd;
    stack<char> opr;

    for(int i = 0; i < s.length(); i++) {

        if(s[i] == ' ')
            continue;

        else if(s[i] == '(') {
            opr.push(s[i]);
        }

        else if(isdigit(s[i])) {
            int val = 0;
            while(i < s.length() && isdigit(s[i])) {
                val = (val*10) + (s[i]-'0');
                i++;
            }
            opd.push(val);
            i--;
        }

        else if(s[i] == ')') {
            while(opr.size() != 0 && opr.top() != '(') {
                int opd1 = opd.top();
                opd.pop();
                int opd2 = opd.top();
                opd.pop();
                char ch = opr.top();
                opr.pop();
                opd.push(operate(ch, opd1, opd2));
            }
            
            if(opr.size() != 0)
                opr.pop();
        }

        else {
            while(opr.size() != 0 && precedenceOf(opr.top()) >= precedenceOf(s[i])) {
                int opd1 = opd.top();
                opd.pop();
                int opd2 = opd.top();
                opd.pop();
                char ch = opr.top();
                opr.pop();
                opd.push(operate(ch, opd1, opd2));
            }

            opr.push(s[i]);
        }
    }

    while(opr.size() != 0) {
        int opd1 = opd.top();
        opd.pop();
        int opd2 = opd.top();
        opd.pop();
        char ch = opr.top();
        opr.pop();
        opd.push(operate(ch, opd1, opd2));
    }

    return opd.top();
}

// QUESTION 8
// INFIX TO PREFIX CONVERSION
string infixToPrefixConversion(string s) {
    stack<string> opd;
    stack<char> opr;

    for(int i = 0; i < s.length(); i++) {

        if(s[i] == ' ')
            continue;

        else if(s[i] == '(') {
            opr.push(s[i]);
        }

        else if(isalnum(s[i])) {
            string val = "";
            while(i < s.length() && isalnum(s[i])) {
                val += s[i];
                i++;
            }
            opd.push(val);
            i--;
        }

        else if(s[i] == ')') {
            while(opr.size() != 0 && opr.top() != '(') {
                string opd1 = opd.top();
                opd.pop();
                string opd2 = opd.top();
                opd.pop();
                char ch = opr.top();
                opr.pop();
                string ans = ch + opd2 + opd1;
                opd.push(ans);
            }
            
            if(opr.size() != 0)
                opr.pop();
        }

        else {
            while(opr.size() != 0 && precedenceOf(opr.top()) >= precedenceOf(s[i])) {
                string opd1 = opd.top();
                opd.pop();
                string opd2 = opd.top();
                opd.pop();
                char ch = opr.top();
                opr.pop();
                string ans = ch + opd2 + opd1;
                opd.push(ans);
            }

            opr.push(s[i]);
        }
    }

    while(opr.size() != 0) {
        string opd1 = opd.top();
        opd.pop();
        string opd2 = opd.top();
        opd.pop();
        char ch = opr.top();
        opr.pop();
        string ans = ch + opd2 + opd1;
        opd.push(ans);
    }

    return opd.top();
}

// QUESTION 9
// INFIX TO POSTFIX CONVERSION
string infixToPostfixConversion(string s) {
    stack<string> opd;
    stack<char> opr;

    for(int i = 0; i < s.length(); i++) {

        if(s[i] == ' ')
            continue;

        else if(s[i] == '(') {
            opr.push(s[i]);
        }

        else if(isalnum(s[i])) {
            string val = "";
            while(i < s.length() && isalnum(s[i])) {
                val += s[i];
                i++;
            }
            opd.push(val);
            i--;
        }

        else if(s[i] == ')') {
            while(opr.size() != 0 && opr.top() != '(') {
                string opd1 = opd.top();
                opd.pop();
                string opd2 = opd.top();
                opd.pop();
                char ch = opr.top();
                opr.pop();
                string ans = opd2 + opd1 + ch;               
                opd.push(ans);
            }
            
            if(opr.size() != 0)
                opr.pop();
        }

        else {
            while(opr.size() != 0 && precedenceOf(opr.top()) >= precedenceOf(s[i])) {
                string opd1 = opd.top();
                opd.pop();
                string opd2 = opd.top();
                opd.pop();
                char ch = opr.top();
                opr.pop();
                string ans = opd2 + opd1 + ch;
                opd.push(ans);
            }

            opr.push(s[i]);
        }
    }

    while(opr.size() != 0) {
        string opd1 = opd.top();
        opd.pop();
        string opd2 = opd.top();
        opd.pop();
        char ch = opr.top();
        opr.pop();
        string ans = opd2 + opd1 + ch;        
        opd.push(ans);
    }

    return opd.top();
}

// QUESTION 10
// TO EVALUATE POSTFIX EXPRESSION
int solvingPostfixExpression(string s) {
    stack<int> st;

    for(int i = 0; i < s.length(); i++) {
        if(s[i] == ' ')
            continue;

        else if(isdigit(s[i])) {
            st.push(s[i] - '0');
        }

        else {
            int op1 = st.top();
            st.pop();
            int op2 = st.top();
            st.pop();
            st.push(operate(s[i], op1, op2));
        }
    }

    return st.top();
}

// QUESTION 11
// TO CONVERT POSTFIX TO INFIX
string postfixToInfixConversion(string s) {
    stack<string> st;

    for(int i = 0; i < s.length(); i++) {
        if(s[i] == ' ')
            continue;

        else if(isalnum(s[i])) {
            string op(1, s[i]);
            st.push(op);
        }

        else {
            string op1 = st.top();
            st.pop();
            string op2 = st.top();
            st.pop();
            string a = "(" + op2 + s[i] + op1 + ")";
            st.push(a);
        }
    }

    return st.top();
}

// QUESTION 12
// TO CONVERT POSTFIX TO PREFIX
string postfixToPrefixConversion(string s) {
    stack<string> st;

    for(int i = 0; i < s.length(); i++) {
        if(s[i] == ' ')
            continue;

        else if(isalnum(s[i])) {
            string op(1, s[i]);
            st.push(op);
        }

        else {
            string op1 = st.top();
            st.pop();
            string op2 = st.top();
            st.pop();
            string a = s[i] + op2 + op1;
            st.push(a);
        }
    }

    return st.top();
}

// QUESTION 13
// TO EVALUATE PREFIX EXPRESSION
int solvingPrefixExpression(string s) {
    stack<int> st;

    for(int i = s.length() - 1; i >= 0; i--) {
        if(s[i] == ' ')
            continue;

        else if(isdigit(s[i])) {
            st.push(s[i] - '0');
        }

        else {
            int op1 = st.top();
            st.pop();
            int op2 = st.top();
            st.pop();
            st.push(operate(s[i], op2, op1));
        }
    }

    return st.top();
}

// QUESTION 14
// TO CONVERT PREFIX TO INFIX
string prefixToInfixConversion(string s) {
    stack<string> st;

    for(int i = s.length() - 1; i >= 0; i--) {
        if(s[i] == ' ')
            continue;

        else if(isalnum(s[i])) {
            string op(1, s[i]);
            st.push(op);
        }

        else {
            string op1 = st.top();
            st.pop();
            string op2 = st.top();
            st.pop();
            string a = "(" + op2 + s[i] + op1 + ")";
            st.push(a);
        }
    }

    string ans = st.top();
    reverse(ans.begin(), ans.end());

    for(int i = 0; i < ans.length(); i++) {
        if(ans[i] == '(') 
            ans[i] = ')';
        else if(ans[i] == ')') 
            ans[i] = '(';
    }
    return ans;
}

// QUESTION 15
// TO CONVERT POSTFIX TO PREFIX
string prefixToPostfixConversion(string s) {
    stack<string> st;

    for(int i = s.length() - 1; i >= 0; i--) {
        if(s[i] == ' ')
            continue;

        else if(isalnum(s[i])) {
            string op(1, s[i]);
            st.push(op);
        }

        else {
            string op1 = st.top();
            st.pop();
            string op2 = st.top();
            st.pop();
            string a = op1 + op2 + s[i];
            st.push(a);
        }
    }

    return st.top();
}

// QUESTION 16
// TRAPPING RAIN WATER LEETCODE




int main(int argc, char** argv) {
    // printBinaryNumbers(16);
}