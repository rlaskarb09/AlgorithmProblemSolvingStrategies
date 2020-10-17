#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAX_V = 500;

int V, E;
// int adjOrigin[2][MAX_V][MAX_V];
int adj[2][MAX_V][MAX_V];
int delay[MAX_V];

void solve() {
    vector<pair<int, int>> order;
    for (int i = 0; i < V; ++i)
        order.emplace_back(delay[i], i);
    sort(order.begin(), order.end());

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (i == j)
                adj[1][i][j] = 0;
            else
                adj[1][i][j] = adj[0][i][j];

    for (int k = 0; k < V; ++k) {
        int w = order[k].second;
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j) {
                adj[0][i][j] = min(adj[0][i][j], adj[0][i][w] + adj[0][w][j]);
                adj[1][i][j] = min(adj[1][i][j], adj[0][i][w] + delay[w] + adj[0][w][j]);
            }
    }
}

int main() {
    cin >> V >> E;
    for (int i = 0; i < V; ++i) 
        cin >> delay[i];
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < V; ++j)
            for (int k = 0; k < V; ++k)
                if (j != k) 
                    adj[i][j][k] = INF;
                else 
                    adj[i][j][k] = 0;
    for (int i = 0; i < E; ++i) {
        int from, to, cost;
        cin >> from >> to >> cost;
        adj[0][from-1][to-1] = cost;
        adj[0][to-1][from-1] = cost;
    }
    solve();
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int from, to;
        cin >> from >> to;
        cout << adj[1][from-1][to-1] << '\n';
    }
    
    return 0;
}