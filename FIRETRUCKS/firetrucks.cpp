#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int minDistSum(int V, vector<int>& fire, vector<int>& office, vector<vector<pair<int, int>>>& adj) {
    int ret = 0;
    vector<int> dist(V+1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[0] = 0;
    pq.emplace(0, 0);
    while(!pq.empty()) {
        int here = pq.top().second;
        int cost = pq.top().first;
        pq.pop();
        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            if (cost + adj[here][i].second < dist[there]) {
                dist[there] = cost + adj[here][i].second;
                pq.emplace(dist[there], there);
            }
        }
    }
    for (int i = 0; i < fire.size(); ++i) {
        ret += dist[fire[i]];
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tests;
    cin >> tests;
    for (int testIdx = 0; testIdx < tests; ++testIdx) {
        int V, E, N, M;
        int from, to, cost;
        cin >> V >> E >> N >> M;
        vector<vector<pair<int, int>>> adj(V+1);
        vector<int> fire(N), office(M);
        for (int i = 0; i < E; ++i) {
            cin >> from >> to >> cost;
            adj[from].emplace_back(to, cost);
            adj[to].emplace_back(from, cost);
        }
        for (int i = 0; i < N; ++i)
            cin >> fire[i];
        for (int i = 0; i < M; ++i) {
            cin >> office[i];
            adj[0].emplace_back(office[i], 0);
        }
        cout << minDistSum(V, fire, office, adj) << endl;
    }
    return 0;
}