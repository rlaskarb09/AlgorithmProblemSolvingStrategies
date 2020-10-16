#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N, K;
        cin >> N >> K;

        list<int> soldiers;
        for (int i = 0; i < N - 1; ++i) {
            soldiers.push_back(i + 2);
        }

        int remain = N - 3;

        bool isFirst = true;
        auto it = soldiers.begin();
        while(remain > 0) {
            for (int i = 0; i < K - 1; ++i) {
                it = ++it;
                if (it == soldiers.end()) {
                    it = soldiers.begin();
                }
            }
            it = soldiers.erase(it);
            if (it == soldiers.end()) {
                it = soldiers.begin();
            }
            --remain;
        }

        for (auto it = soldiers.begin(); it != soldiers.end(); ++it) {
            cout << (*it) << ' ';
        }
        cout << endl;
    }
    
}