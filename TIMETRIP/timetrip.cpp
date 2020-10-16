#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAX_V = 1000;

int V;

vector<pair<int, int>> adj[MAX_V];

// If negative cycle exists, upper with size()==0 will be returned
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
    if (updated) upper.clear();
    return upper;
}

int main() {
    V = 6;
    adj[0].emplace_back(1, 100);
    adj[1].emplace_back(2, -1);
    adj[2].emplace_back(3, -1);
    adj[3].emplace_back(4, -1);
    adj[4].emplace_back(5, -1);
    adj[1].emplace_back(5, -1);
    adj[2].emplace_back(5, -1);
    adj[3].emplace_back(5, -1);
    bellmanFord(0);
    return 0;
}