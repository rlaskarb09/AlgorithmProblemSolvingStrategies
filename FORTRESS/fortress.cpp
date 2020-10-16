#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    vector<TreeNode*> childs;
};

struct Fortress {
    int r;
    int x;
    int y;
};

bool comparator(Fortress a, Fortress b) {
    return a.r < b.r;
}

bool isChild(Fortress a, Fortress b) {
    return ((b.r - a.r) * (b.r - a.r)) > ((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N;
        cin >> N;
        vector<Fortress> fortresses(N);
        vector<TreeNode> treeNodes(N);
        for (int i = 0; i < N; ++i) {
            cin >> fortresses[i].x >> fortresses[i].y >> fortresses[i].r;
        }
        sort(fortresses.begin(), fortresses.end(), comparator);
        vector<int> rootIdxs;
        for (int i = 0; i < N; ++i) {
            for (auto it = rootIdxs.begin(); it != rootIdxs.end(); ++it) {
                if (isChild(fortresses[*it], fortresses[i])) {
                    treeNodes[j].childs.push_back(&(treeNodes[rootIdxs[j]]));
                    rootIdxs.erase(rootIdxs.begin() + j);
                }
            }
            rootIdxs.push_back(i);
        }
    }
    return 0;
}