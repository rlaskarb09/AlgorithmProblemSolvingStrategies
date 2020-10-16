#include <bits/stdc++.h>

using namespace std;

int append(int here, int newDigit, int N) {
    int there = here * 10 + newDigit;
    if (there >= N) return N + there % N;
    return there;
}

string bfs(string digits, int N, int M) {
    vector<int> parent(2 * N + 1, -1), choice(2 * N + 1, -1);
    queue<int> bfsQ;
    sort(digits.begin(), digits.end());
    bfsQ.push(0);
    parent[0] = 0;
    while(!bfsQ.empty()) {
        int here = bfsQ.front();
        bfsQ.pop();
        for (int i = 0; i < digits.size(); ++i) {
            int newDigit = digits[i] - '0';
            int there = append(here, newDigit, N);
            if (parent[there] == -1) {
                parent[there] = here;
                choice[there] = newDigit;
                bfsQ.push(there);
            }
        }
    }
    if (parent[N + M] == -1) return "IMPOSSIBLE";
    string ret;
    int here = N + M;
    while(parent[here] != here) {
        ret.push_back(choice[here] + '0');
        here = parent[here];
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        string D;
        int N, M;
        cin >> D >> N >> M;
        cout << bfs(D, N, M) << endl;
    }


    return 0;
}