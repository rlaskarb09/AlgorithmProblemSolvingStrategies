#include <bits/stdc++.h>

using namespace std;

const int ALPHABETS = 26;
int adj[ALPHABETS][ALPHABETS];
vector<int> visited, order;

void dfs(int idx) {
    visited[idx] = 1;
    for (int i = 0; i < ALPHABETS; ++i) 
        if (adj[idx][i] && visited[i] == 0)
            dfs(i);
    
    order.push_back(idx);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N;
        cin >> N;
        memset(adj, 0, sizeof(adj));
        visited = vector<int>(ALPHABETS, 0);
        vector<string> words(N);
        for (int i = 0; i < N; ++i) cin >> words[i];
        for (int i = 0; i < N - 1; ++i) {
            for (int j = 0; j < words[i].size() && j < words[i+1].size(); ++j) {
                if (words[i][j] != words[i+1][j]) {
                    adj[words[i][j] - 'a'][words[i+1][j] - 'a'] = 1;
                    break;
                }
            }
        }
        order.clear();
        for (int i = 0; i < ALPHABETS; ++i) 
            if (visited[i] == 0) dfs(i);
        reverse(order.begin(), order.end());
        bool isDone = false;
        for (int i = 0; i < ALPHABETS; ++i) {
            for (int j = i + 1; j < ALPHABETS; ++j) {
                if (adj[order[j]][order[i]]) {
                    order = vector<int>();
                    isDone = true;
                    break;
                }
            }
            if (isDone) break;
        }
        if (order.size() == 0) 
            printf("INVALID HYPOTHESIS\n");
        else {
            for (int i = 0; i < order.size(); ++i) {
                printf("%c", (char)order[i] + 'a');
            }
            printf("\n");
        }
    }
    return 0;
}