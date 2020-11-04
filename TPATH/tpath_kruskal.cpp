#include <bits/stdc++.h>

using namespace std;

const int MAX_V = 2000;
const int INF = 987654321;

int V, E;
vector<pair<int, int>> adj[MAX_V];
vector<int> weights;
vector<tuple<int, int, int>> inputEdges;

struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n): parent(n), rank(n, 1) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find (int u) {
        if (u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if(rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if(rank[u] == rank[v]) ++rank[v];
    }
};

int kruskalMinUpperBound(int low) {
    DisjointSet sets(V);
    for (int i = 0; i < inputEdges.size(); ++i) {
        if (get<0>(inputEdges[i]) < weights[low]) continue;
        sets.merge(get<1>(inputEdges[i]), get<2>(inputEdges[i]));
        if (sets.find(0) == sets.find(V-1))
            return get<0>(inputEdges[i]); 
    }
    return INF;
}

int minWeightDifference() {
    int ret = INF;
    for (int i = 0; i < weights.size(); ++i)
        ret = min(ret, kruskalMinUpperBound(i) - weights[i]);
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