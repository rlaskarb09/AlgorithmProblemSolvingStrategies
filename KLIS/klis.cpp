#include <bits/stdc++.h>

using namespace std;

const int MAX_INPUT_LEN = 500;
const long long MAX_INT = (1LL << 31) - 1;
int N, K;
int inputNum[MAX_INPUT_LEN + 1];
int lengths[MAX_INPUT_LEN + 1] ;
long long counts[MAX_INPUT_LEN + 1];
vector<pair<int, int>> child[MAX_INPUT_LEN + 1];

void getSequence(int count, int curIdx, vector<int> & answer) {
    if (count == 1 && lengths[curIdx] == 1) {
        answer.push_back(inputNum[curIdx]);
        return;
    }
    for (int i = 0; i < child[curIdx].size(); ++i) {
        int childIdx = child[curIdx][i].second;
        if (count > counts[childIdx]) {
            count -= counts[childIdx];
        }
        else {
            answer.push_back(inputNum[curIdx]);
            getSequence(count, childIdx, answer);
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        memset(inputNum, 0, sizeof(inputNum));
        memset(lengths, 0, sizeof(lengths));
        memset(counts, 0, sizeof(counts));
        for (int i = 0; i < MAX_INPUT_LEN + 1; ++i) {
            child[i].clear();
        }
        cin >> N >> K;
        for (int i = 0; i < N; ++i) {
            cin >> inputNum[i + 1];
        }

        for (int i = N; i >= 0; --i) {
            int maxLen = 0;
            for (int j = i + 1; j <= N; ++j) {
                if (inputNum[j] > inputNum[i]) {
                    if (lengths[j] > maxLen) {
                        maxLen = lengths[j];
                        child[i].clear();
                        child[i].emplace_back(inputNum[j], j);
                        counts[i] = counts[j];
                    } else if (lengths[j] == maxLen) {
                        child[i].emplace_back(inputNum[j], j);
                        counts[i] += counts[j];
                        if (counts[i] > MAX_INT) {
                            counts[i] = MAX_INT;
                        }
                    }
                }
            }
            lengths[i] = maxLen + 1;
            if (maxLen == 0) counts[i] = 1;
        }
        for (int i = 0; i <= N; ++i) {
            sort(child[i].begin(), child[i].end());
        }
        // for (int i = 0; i <= N; ++i) {
        //     cout << i << " " << inputNum[i] << " " << lengths[i] << " " << counts[i] << " " << child[i].size();
        //     for (int j = 0; j < child[i].size(); ++j) {
        //         cout << " <" << child[i][j].first << "," << child[i][j].second << "> ";
        //     }
        //     cout << endl;
        // }
        int count = K;
        vector<int> answer;
        cout << lengths[0] - 1 << endl;
        getSequence(count, 0, answer);
        for (int i = 1; i < answer.size(); ++i) {
            cout << answer[i] << ' ';
        }
        cout << endl;
    }

    return 0;
}