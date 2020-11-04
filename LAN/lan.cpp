#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_V = 500;
const double INF = 98765432100.0;

int N, M;
vector<pair<int, int>> pos, inputEdge;
double dist[MAX_V][MAX_V];

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
        if (rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if (rank[u] == rank[v]) ++rank[v];
    }
};

double connectCable() {
    double answer = 0;
    DisjointSet disjoint(N);
    int leftCable = N - 1;
    for (int i = 0; i < M; ++i) 
        if (disjoint.find(inputEdge[i].first) != disjoint.find(inputEdge[i].second)) {
            --leftCable;
            disjoint.merge(inputEdge[i].first, inputEdge[i].second);
        }

    vector<tuple<double, int, int>> edges;
    for (int i = 0; i < N - 1; ++i) 
        for (int j = i + 1; j < N; ++j) 
            edges.emplace_back(dist[i][j], i, j);
    
    sort(edges.begin(), edges.end());
    
    for (int i = 0; i < edges.size(); ++i) {
        double cost = get<0>(edges[i]);
        if (disjoint.find(get<1>(edges[i])) != disjoint.find(get<2>(edges[i]))) {
            --leftCable;
            disjoint.merge(get<1>(edges[i]), get<2>(edges[i]));
            answer += cost;
        }
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tests;
    cin >> tests;

    for (int testIdx = 0; testIdx < tests; ++testIdx) {
        cin >> N >> M;
        pos = vector<pair<int, int>>(N);
        inputEdge = vector<pair<int, int>> (M);
        
        for (int i = 0; i < N; ++i) 
            cin >> pos[i].first;
        for (int i = 0; i < N; ++i) 
            cin >> pos[i].second;

        for (int i = 0; i < N - 1; ++i)
            for (int j = i + 1; j < N; ++j) {
                dist[i][j] = sqrt((double)(pow(pos[i].first - pos[j].first, 2) + 
                                        pow(pos[i].second - pos[j].second, 2)));
            }
                
        for (int i = 0; i < M; ++i) {
            cin >> inputEdge[i].first >> inputEdge[i].second;
        }
        cout.precision(10);
        cout << fixed << connectCable() << endl;
    }
    return 0;
}