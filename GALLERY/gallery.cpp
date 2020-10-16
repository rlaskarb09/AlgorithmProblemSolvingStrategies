#include <bits/stdc++.h>

using namespace std;

int answer;

bool dfs(int here, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& monitored) {
    visited[here] = true;
    if(adj[here].size() == 0) {
        ++answer;
        monitored[here] = true;
        return true;
    }
    int childCount = 0;
    bool childMonitored = true;
    for (auto there: adj[here]) {
        if(!visited[there]) {
            bool childInstalled = dfs(there, adj, visited, monitored);
            if(childInstalled) monitored[here] = true;
            if(!monitored[there]) {
                childMonitored = false;
            }
            ++childCount;
        }
    }
    if (childCount == 0) return false;
    if (!childMonitored) {
        ++answer;
        monitored[here] = true;
        for (auto there: adj[here]) {
            monitored[there] = true;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        answer = 0;
        int G, H;
        cin >> G >> H;
        vector<vector<int>> adj = vector<vector<int>>(G, vector<int>());
        vector<bool> visited(G, false);
        vector<bool> monitored(G, false);
        for (int i = 0; i < H; ++i) {
            int from, to;
            cin >> from >> to;
            adj[from].push_back(to);
            adj[to].push_back(from);
        }

        for (int i = 0; i < G; ++i) {
            if(!visited[i]) {
                dfs(i, adj, visited, monitored);
                if (!monitored[i]) {
                    ++answer;
                    monitored[i] = true;
                }
            }
        }

        cout << answer << endl;
    }

    return 0;
}