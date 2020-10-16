#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000;

void setInsert(vector<int> &a, int idx) {
    int n = idx / 32;
    int m = idx % 32;
    a[n] |= (1 << m);
}

void setRemove(vector<int> &a, int idx) {
    int n = idx / 32;
    int m = idx % 32;

    a[n] &= ~(1 << m);
}

void setCopy(vector<int> &dst, vector<int> &src) {
    dst = vector<int>(src);
}

int setCound(vector<int> &a) {
    int count = 0;
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < 32; ++j) {
            if (((unsigned int)a[i]) % 2 == 1) {
                count += 1;
            }
            a[i] = (a[i] >> 1);
        }
    }
}

void printSet(vector<int> a) {
    for (int i = 0; i< a.size(); ++i) {
        for (int j = 0; j < 32; ++j) {
            if (a[i] & (1 << j)) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
    }
    cout << endl;
}

void printAnswer(vector<int> itemSet, vector<string> names, vector<pair<int, int>> items, int valueSum) {
    int count = 0;
    vector<int> idxs;
    for (int i = 0; i < itemSet.size(); ++i) {
        for (int j = 0; j < 32; ++j) {
            if (((unsigned int)itemSet[i]) % 2 == 1) {
                count += 1;
                int index = i * 32 + j;
                idxs.push_back(index);
            }
            itemSet[i] = itemSet[i] >> 1;
        }
    }
    cout << valueSum << ' ' << count << endl;
    for (int i = 0; i < idxs.size(); ++i) {
        cout << names[idxs[i]] << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int numOfTests;
    cin >> numOfTests;
    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N, W;
        cin >> N >> W;
        vector<pair<int, int>> items(N);
        vector<string> names(N);
        vector<int> vals(W + 1);
        vector<vector<int>> itemSet(W + 1, vector<int>((N + 1) / 32 + 1));
        for (int i = 0; i < N; ++i) {
            cin >> names[i] >> items[i].first >> items[i].second;
        }
        for (int i = 0; i < N; ++i) {
            int& size = items[i].first;
            int& value = items[i].second;
            vector<int> newVals(W + 1);
            vector<vector<int>> newItemSet(W + 1, vector<int>((N + 1) / 32 + 1));
            for (int j = 1; j <= W; ++j) {
                if (j < size) {
                    newVals[j] = vals[j];
                    setCopy(newItemSet[j], itemSet[j]);
                } else {
                    if (vals[j - size] + value > vals[j]) {
                        newVals[j] = vals[j - size] + value;
                        setCopy(newItemSet[j], itemSet[j - size]);
                        setInsert(newItemSet[j], i);
                        // printSet(newItemSet[j]);
                    } else {
                        newVals[j] = vals[j];
                        setCopy(newItemSet[j], itemSet[j]);
                    }
                }
            }
            vals = newVals;
            itemSet = newItemSet;
        }
        printAnswer(itemSet[W], names, items, vals[W]);
    }

    return 0;
}