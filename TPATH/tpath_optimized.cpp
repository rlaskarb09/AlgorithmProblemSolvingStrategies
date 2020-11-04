#include <bits/stdc++.h>

using namespace std;

const int MAX_V = 2000;
const int INF = 987654321;

int V, E;
vector<pair<int, int>> adj[MAX_V];
vector<int> weights;
bool visited[MAX_V];

// check whether equal sign is required at if clause
bool hasPath(int lo, int hi) {
    memset(visited, 0, sizeof(visited));
    queue<int> bfsQ;
    visited[0] = true;
    bfsQ.push(0);
    while(!bfsQ.empty()) {
        int here = bfsQ.front();
        bfsQ.pop();
        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            int weight = adj[here][i].second;
            if (weight >= lo && weight <= hi && !visited[there]) {
                if (there == V - 1) return true;
                visited[there] = true;
                bfsQ.push(there);
            }
        }
    }
    return false;
}

int minWeightDifference() {
    int ret = INF;
    int minUpperBound = 0;

    for (int lo = 0; lo < weights.size(); ++lo) {
        bool foundPath = false;
        for (int hi = minUpperBound; hi < weights.size(); ++hi) {
            if (hasPath(weights[lo], weights[hi])) {
                foundPath = true;
                minUpperBound = hi;
                ret = min(ret, weights[hi] - weights[lo]);
                break;
            }
        }
        if (!foundPath) break;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tests;
    cin >> tests;
    for (int testIdx = 0; testIdx < tests; ++testIdx) {
        for (int i = 0; i < MAX_V; ++i)
            adj[i].clear();
        cin >> V >> E;
        weights = vector<int>(E);

        for (int i = 0; i < E; ++i) {
            int from, to, weight;
            cin >> from >> to >> weight;
            weights[i] = weight;
            adj[from].emplace_back(to, weight);
            adj[to].emplace_back(from, weight);
        }


        sort(weights.begin(), weights.end());
        cout << minWeightDifference() << endl;
    }
    return 0;
}