#include <bits/stdc++.h>

using namespace std;

const int FULL_SIZE = 8*7*6*5*4*3*2;

int getIndex(const vector<int>& series) {
    int ret = 0;
    int N = series.size();
    int mult = 10;
    for (int i = 0; i < N; ++i) {
        ret += series[i] * mult;
        mult *= 10;
    }

    return ret;;
}

int bfs(vector<int> series) {
    int N = series.size();
    vector<int> answer;
    answer = series;
    sort(answer.begin(), answer.end());
    if (answer == series) 
        return 0;

    unordered_set<int> discover;
    queue<pair<vector<int>, int>> bfsQ;
    discover.reserve(FULL_SIZE);
    bfsQ.push(make_pair(series, 0));
    discover.insert(getIndex(series));
    while(!bfsQ.empty()) {
        pair<vector<int>, int> popped = bfsQ.front();
        bfsQ.pop();
        for (int i = 0; i < N - 1; ++i) {
            for (int j = i + 1; j < N; ++j) {
                vector<int> newSeries = popped.first;
                reverse(newSeries.begin() + i, newSeries.begin() + j + 1);
                if (newSeries == answer) return popped.second + 1;
                int hash = getIndex(newSeries);
                if (discover.find(hash) == discover.end()) {
                    discover.insert(hash);
                    bfsQ.push(make_pair(newSeries, popped.second+1));
                }
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int numOfTests;
    cin >> numOfTests;
    
    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N;
        cin >> N;
        vector<int> series(N), idxToNum;
        map<int, int> numToIdx;
        for (int i = 0; i < N; ++i) {
            cin >> series[i];
        }
        idxToNum = series;
        sort(idxToNum.begin(), idxToNum.end());
        for (int i = 0; i < N; ++i)
            numToIdx[idxToNum[i]] = i;
        for (int i = 0; i < N; ++i)
            series[i] = numToIdx[series[i]];
        cout << bfs(series) << endl;
    }
    return 0;
}