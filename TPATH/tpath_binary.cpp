#include <bits/stdc++.h>

using namespace std;

const int MAX_V = 2000;
const int INF = 987654321;

int V, E;
vector<pair<int, int>> adj[MAX_V];
vector<int> weights;
vector<tuple<int, int, int>> inputEdges;
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

int binarySearchMinUpperBound(int low) {
    int lo = low - 1, hi = weights.size();
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (hasPath(weights[low], weights[mid]))
            hi = mid;
        else
            lo = mid;
    }
    if (hi == weights.size()) return INF;
    return weights[hi];
}

int minWeightDifference() {
    int ret = INF;
    for (int i = 0; i < weights.size(); ++i) {
        ret = min(ret, binarySearchMinUpperBound(i) - weights[i]);
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
        inputEdges = vector<tuple<int, int, int>>(E);
        weights = vector<int>(E);

        for (int i = 0; i < E; ++i) {
            int from, to, weight;
            cin >> from >> to >> weight;
            inputEdges[i] = tie(weight, from, to);
            adj[from].emplace_back(to, weight);
            adj[to].emplace_back(from, weight);
        }


        sort(inputEdges.begin(), inputEdges.end());
        for (int i = 0; i < E; ++i)
            weights[i] = get<0>(inputEdges[i]);
        cout << minWeightDifference() << endl;
    }
    return 0;
}