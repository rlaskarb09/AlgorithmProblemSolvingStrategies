#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 8;

map<vector<int>, int> toSort;

void preCalc() {
    int N = MAX_N;
    vector<int> series(N);
    for (int i = 0; i < N; ++i) series[i] = i;
    queue<pair<vector<int>, int>> bfsQ;
    bfsQ.emplace(series, 0);
    toSort[series] = 0;
    while(!bfsQ.empty()) {
        pair<vector<int>, int> popped = bfsQ.front();
        bfsQ.pop();
        for (int i = 0; i < N - 1; ++i)
            for (int j = i + 1; j < N; ++j) {
                vector<int> newSeries = popped.first;
                reverse(newSeries.begin() + i, newSeries.begin() + j + 1);
                if (toSort.count(newSeries) == 0) {
                    // for (int i = 0; i < N; ++i) cout << newSeries[i] << " ";
                    // cout << ", cost=" << popped.second + 1 << endl;
                    toSort[newSeries] = popped.second + 1;
                    bfsQ.emplace(newSeries, popped.second + 1);
                }
            }
    }
}

vector<int> getFullSeries(const vector<int>& series) {
    vector<int> ret(MAX_N);
    for (int i = 0; i < MAX_N; ++i) ret[i] = i;
    for (int i = 0; i < series.size(); ++i)
        ret[i] = series[i];

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    preCalc();
    cout << "Done preCalc" << endl;
    int numOfTests;
    cin >> numOfTests;
    preCalc();
    
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
        
        vector<int> fullSeries = getFullSeries(series);
        cout << toSort[fullSeries] << endl;
    }
    return 0;
}