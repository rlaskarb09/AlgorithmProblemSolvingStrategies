#include <bits/stdc++.h>

using namespace std;

struct FenwickTree {
    vector<int> tree;
    FenwickTree(int n): tree(n + 1) {}

    int sum (int pos) {
        pos++;
        int ret = 0;
        while (pos > 0) {
            ret += tree[pos];
            pos &= (pos - 1);
        }
        return ret;
    }

    void add(int pos, int value) {
        pos++;
        while (pos < tree.size()) {
            tree[pos] += value;
            pos += (pos & -pos);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int n;
        cin >> n;
        FenwickTree fenwick(1000001);
        int answer = 0;
        for (int i = 0; i < n; ++i) {
            int input;
            cin >> input;
            answer += i - fenwick.sum(input);
            fenwick.add(input, 1);
        }
        cout << answer << endl;
    }
    return 0;
}