#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

// QUESTION 1
// MINIMUM NUMBER OF REFUELING STOPS LEETCODE
int minStops(int target, int sf, vector<vector<int>>& stations) {
    if(sf >= target)
        return 0;
    priority_queue<int> pq;
    int stops = 0;
    int curFuel = sf;

    int i = 0;
    while(curFuel < target) {
        while(i < stations.size() && stations[i][0] <= curFuel) {
            pq.push(stations[i][1]);
            i++;
        }

        if(pq.empty())
            return -1;
        curFuel += pq.top();
        pq.pop();
        stops++;
    }

    return stops;
}

// QUESTION 2
// POTIONS(HARD VERSION) CODEFORCES
int maxDrink(vector<int> &arr) {
    priority_queue<int, vector<int>, greater<int>> pq;
    int pos = 0;
    int neg = 0;
    int count = 0;

    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] >= 0) {
            pos += arr[i];
            count++;
        }

        if(arr[i] < 0) {
            if(neg + abs(arr[i]) <= pos) {
                pq.push(arr[i]);
                neg += abs(arr[i]);
            }

            else {
                if(pq.size() == 0)
                    continue;
                
                int temp = abs(pq.top());
                if(abs(arr[i]) < temp) {
                    pq.pop();
                    pq.push(arr[i]);
                    neg = neg - temp + abs(arr[i]);
                }
            }
        }
    }

    return count + pq.size();
}

// QUESTION 3
// X OF A KIND IN A DECK LEETCODE
bool hasGroupsSizeX(vector<int>& deck) {
    unordered_map<int, int> count;
    int res = 0;
    for (int i : deck) count[i]++;
    for (auto i : count) res = __gcd(i.second, res);
    return res > 1;
}

// QUESTION 4
// 

int main(int argc, char** argv) {
    
}