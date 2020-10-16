#include <bits/stdc++.h>

using namespace std;

const double INF = numeric_limits<double>::max();
const int MAX_N = 10000;

double dijkstra(vector<vector<pair<int, double>>> adj, int start, int end) {
    int N = end + 1;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    vector<double> dist(N, INF);
    // vector<bool> visited(N, false);
    dist[start] = 1.0;
    pq.emplace(1.0, start);
    while(!pq.empty()) {
        double cost = pq.top().first;
        int here = pq.top().second;
        pq.pop();
        // if(visited[here]) continue;
        // visited[here] = true;
        for(int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            if (cost * adj[here][i].second < dist[there]) {
                dist[there] = cost * adj[here][i].second;
                pq.emplace(dist[there], there);
            }
        }
    }
    return dist[end];
}

// double dijkstra(vector<pair<int, double>> *adj, int start, int end) {
//     int N = end + 1;
//     vector<bool> visited(N, false);
//     vector<double> dist(N, INF);
//     dist[start] = 1;
    
//     while(true) {
//         int here;
//         double closest = INF;
//         for (int i = 0; i < N; ++i) {
//             if (!visited[i] && dist[i] < closest) {
//                 here = i;
//                 closest = dist[i];
//             }
//         }
//         if (closest == INF) break;
//         visited[here] = true;
//         for (int i = 0; i < adj[here].size(); ++i) {
//             int there = adj[here][i].first;
//             if (visited[there]) continue;
//             dist[there] = min(dist[there], dist[here] * adj[here][i].second);
//         }
//     }
//     return dist[end];
// }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tests;
    cin >> tests;

    for (int testIdx = 0; testIdx < tests; ++testIdx) {
        int N, M;
        int from, to;
        double cost;
        cin >> N >> M;
        vector<vector<pair<int, double>>> adj(N);
        for (int i = 0; i < M; ++i) {
            cin >> from >> to >> cost;
            adj[from].emplace_back(to, cost);
            adj[to].emplace_back(from, cost);
        }
        int start = 0, end = N - 1;
        cout << fixed;
        cout.precision(10);
        cout << fixed << dijkstra(adj, start, end) << endl;
    }
    return 0;
}