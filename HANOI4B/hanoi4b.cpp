#include <bits/stdc++.h>

using namespace std;

const int MAX_DISCS = 12;

int c[1 << (MAX_DISCS * 2)];

int getDiskIndex(int state, int disk) {
    return (state >> (disk * 2)) & 3;
}
int setState(int state, int disk, int index) {
    return (state & ~(3 << (disk * 2))) | (index << (disk * 2));
}

int sgn (int x) {
    if (x == 0) return 0;
    if (x < 0) return -1;
    return 1;
}

int incr (int x) {
    if (x < 0) return x -1;
    return x + 1;
}

int bidir (int discs, int begin, int end) {
    if (begin == end) return 0;
    memset(c, 0, sizeof(c));
    queue<int> bidirQ;
    bidirQ.push(begin);
    c[begin] = 1;
    bidirQ.push(end);
    c[end] = -1;
    while(!bidirQ.empty()) {
        int here = bidirQ.front();
        bidirQ.pop();
        int top[4] = {-1, -1, -1, -1};
        for (int i = discs - 1; i >= 0; --i) {
            top[getDiskIndex(here, i)] = i;
        }
        for (int i = 0; i < 4; ++i) {
            if (top[i] == -1) continue;
            for (int j = 0; j < 4; ++j) {
                if (i != j && (top[j] == -1 || top[i] < top[j])) {
                    int there = setState(here, top[i], j);
                    if (c[there] == 0)  {
                        c[there] = incr(c[here]);
                        bidirQ.push(there);
                    } else if (sgn(c[there]) != sgn(c[here])) {
                        return abs(c[here]) + abs(c[there]) - 1;
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tests;
    cin >> tests;

    for (int testIdx = 0; testIdx < tests; ++testIdx) {
        int N;
        int begin = 0, end = 0;
        cin >> N;
        for (int i = 0; i < 4; ++i) {
            int disks;
            cin >> disks;
            for (int j = 0; j < disks; ++j) {
                int disk;
                cin >> disk;
                // disk-1 because index of input disk starts from 1
                begin = setState(begin, disk-1, i); 
            }
        }
        for (int i = 0; i < N; ++i)
            end = setState(end, i, 3);
        
        cout << bidir(N, begin, end) << endl;
    }


    return 0;
}