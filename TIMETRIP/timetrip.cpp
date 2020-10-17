#include <bits/stdc++.h>

using namespace std;

const int BIG_INT = 987654321;
const int INF = BIG_INT * 2;
const int MAX_V = 100;

int V, W;

vector<pair<int, int>> adj[MAX_V];

vector<int> bellmanFord(int src) {
    vector<int> upper(V, INF);
    upper[src] = 0;
    bool updated;
    for (int iter = 0; iter < V; ++iter) {
        updated = false;
        for (int here = 0; here < V; ++here) {
            for (int i = 0; i < adj[here].size(); ++i) {
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                if (upper[there] > upper[here] + cost) {
                    upper[there] = upper[here] + cost;
                    updated = true;
                }
            }
        }
        if(!updated) break;
    }
    if (updated) {
        if (upper[1] > BIG_INT) 
            return upper;
        upper.clear();
    }
    return upper;
}

void changeSign() {
    for (int i = 0; i < V; ++i) 
        for (int j = 0; j < adj[i].size(); ++j) 
            adj[i][j].second *= -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tests;
    cin >> tests;
    for (int testIdx = 0; testIdx < tests; ++testIdx) {
        string retFirst, retSecond;
        cin >> V >> W;
        for (int i = 0; i < MAX_V; ++i) adj[i].clear();
        for (int i = 0; i < W; ++i) {
            int from, to, cost;
            cin >> from >> to >> cost;
            adj[from].emplace_back(to, cost);
        }
        vector<int> upper = bellmanFord(0);
        if (upper.size() == 0) {
            retFirst = "INFINITY";
        } else if (upper[1] > BIG_INT) {
            cout << "UNREACHABLE\n";
            continue;
        } else {
            retFirst = to_string(upper[1]);
        }
        changeSign();
        upper = bellmanFord(0);
        if (upper.size() == 0) {
            retSecond = "INFINITY";
        } else {
            retSecond = to_string(-upper[1]);
        }
        cout << retFirst << " " << retSecond << "\n";
    }
    
    return 0;
}