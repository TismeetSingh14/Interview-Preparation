#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// QUESTION 1
// NEXT GREATER ELEMENT IN AN ARRAY ON THE RIGHT
// COMPLEXITY O(2N), APPROXIMATED AS O(N)
void ngeRight(vector<int> &arr) {
    stack<int> st;
    vector<int> ans(arr.size(), -1);

    for(int i = 0; i < arr.size(); i++) {
        while(st.size() != 0 && arr[st.top()] < arr[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = i;
        }
        st.push(i);
    }

    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    cout << "\n";
}

// QUESTION 2
// NEXT SMALLER ELEMENT IN AN ARRAY ON THE RIGHT
// COMPLEXITY O(2N), APPROXIMATED AS O(N)
void nseRight(vector<int> &arr) {
    stack<int> st;
    vector<int> ans(arr.size(), -1);

    for(int i = 0; i < arr.size(); i++) {
        while(st.size() != 0 && arr[st.top()] > arr[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = i;
        }
        st.push(i);
    }

    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    cout << "\n";
}

// QUESTION 3
// NEXT GREATER ELEMENT IN AN ARRAY ON THE LEFT
// COMPLEXITY O(2N), APPROXIMATED AS O(N)
void ngeLeft(vector<int> &arr) {
    stack<int> st;
    vector<int> ans(arr.size(), -1);

    for(int i = arr.size() - 1; i >= 0; i--) {
        while(st.size() != 0 && arr[st.top()] < arr[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = i;
        }
        st.push(i);
    }

    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    cout << "\n";
}

// QUESTION 4
// NEXT SMALLER ELEMENT IN AN ARRAY ON THE LEFT
// COMPLEXITY O(2N), APPROXIMATED AS O(N)
void nseLeft(vector<int> &arr) {
    stack<int> st;
    vector<int> ans(arr.size(), -1);

    for(int i = arr.size() - 1; i >= 0; i--) {
        while(st.size() != 0 && arr[st.top()] > arr[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = i;
        }
        st.push(i);
    }

    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    cout << "\n";
}

// QUESTION 5
// NEXT GREATER ELEMENT IN AN ARRAY ON THE RIGHT (CYCLIC/CIRCULAR)
// COMPLEXITY O(3N), APPROXIMATED AS O(N)
void ngeRightCircular(vector<int> &arr) {
    stack<int> st;
    vector<int> ans(arr.size(), -1);

    for(int i = 0; i < arr.size(); i++) {
        while(st.size() != 0 && arr[st.top()] < arr[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = i;
        }
        st.push(i);
    }

    for(int i = 0; i < arr.size(); i++) {
        while(st.size() != 0 && arr[st.top()] < arr[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = i;
        }
    }

    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    cout << "\n";
}

// QUESTION 6
// DAILY TEMPERATURES LEETCODE
// APPROACH - NGE STACK BASED
vector<int> dailyTemperatures(vector<int> &arr) {
    stack<int> st;
    vector<int> ans(arr.size(), -1);

    for(int i = 0; i < arr.size(); i++) {
        while(st.size() != 0 && arr[st.top()] < arr[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = i - idx;
        }
        st.push(i);
    }

    return ans;
}

// QUESTION 7
// STOCK SPAN PROBLEM GFG
vector<int> stockSpan(vector<int> &arr) {
    stack<int> st;
    vector<int> ans(arr.size(), 0);

    for(int i = arr.size() - 1; i >= 0; i--) {
        while(st.size() != 0 && arr[st.top()] < arr[i]) {
            int idx = st.top();
            st.pop();
            ans[idx] = idx - i;
        }
        st.push(i);
    }

    while(st.size() != 0) {
        int idx = st.top();
        st.pop();
        ans[idx] = idx + 1;
    }

    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout<< "\n";
    return ans;

}

// QUESTION 8
// MAXIMUM DIFFERENCE BETWEEN NEAREST SMALLER ELEMENTS ON RIGHT AND LEFT
int maxDiffNSE(vector<int> &arr) {
    int maxDiff = -1e8;
    stack<int> st;

    for(int i = 0; i < arr.size(); i++) {
        while(st.size() != 0 && arr[st.top()] > arr[i]) {
            int idx = st.top();
            st.pop();
            int top;
            if(st.size() == 0)
                top = 0;
            else 
                top = arr[st.top()];
            maxDiff = max(maxDiff,abs(top - arr[i]));
        }

        st.push(i);
    }

    return maxDiff;
}

// QUESTION 9
// LARGEST RECTANGLE IN HISTOGRAM LEETCODE
int largestAreaOfRectangle(vector<int> &arr) {
    stack<int> st;
    st.push(-1);
    int maxArea = -1e8;

    for(int i = 0; i < arr.size(); i++) {
        while(st.top() != -1 && arr[st.top()] >= arr[i]) {
            int idx = st.top();
            st.pop();
            int area = (i - st.top() - 1)*arr[idx];
            maxArea = max(maxArea, area);
        }

        st.push(i);
    }

    while(st.top() != -1) {
        int idx = st.top();
        st.pop();
        int area = (arr.size() - st.top() - 1) * arr[idx];
        maxArea = max(area, maxArea);
    }

    return maxArea;
}

// QUESTION 10
// MAXIMAL RECTANGLE LEETCODE
int maximalRectangle(vector<vector<int>> &matrix) {

    int maxArea = -1e8;
    vector<int> hist(matrix[0].size(), 0);
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
            if(matrix[i][j] == 0) {
                hist[j] = 0;
            }

            else {
                hist[j] += 1;
            }
        }

        maxArea = max(maxArea, largestAreaOfRectangle(hist));
    }

    return maxArea;
}

// QUESTION 11
// ASTEROID COLLISION LEETCODE
vector<int> asteroidCollision(vector<int> &arr) {
    stack<int> st;

    stack<int> st;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > 0)
            st.push(arr[i]);
        else {
            while (st.size() != 0 && st.top() > 0 && -arr[i] > st.top())
                st.pop();

            if (st.size() != 0 && st.top() == -arr[i])
                st.pop();

            else if (st.size() == 0 || st.top() < 0)
                st.push(arr[i]);
        }
    }

    vector<int> ans(st.size(), 0);

    for (int i = ans.size() - 1; i >= 0; i--) {
        ans[i] = st.top();
        st.pop();
    }

    return ans;
}

int main(int argc,char** argv) {
    vector<int> arr = {100, 80};
    ngeRight(arr);
    nseRight(arr);
    ngeLeft(arr);
    nseLeft(arr);
    ngeRightCircular(arr);
    stockSpan(arr);
    cout << maxDiffNSE(arr);
    cout << "\n";
    vector<vector<int>> matrix = {{1,0,1,0,0},{1,0,1,1,1},{1,1,1,1,1},{1,0,0,1,0}};
    cout << maximalRectangle(matrix);
}