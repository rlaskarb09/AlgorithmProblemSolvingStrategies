#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_SIZE = 100;
const int DIVISOR = 10000000;

int countCache[MAX_SIZE + 1][MAX_SIZE + 1];

int polyCounts(int totalBlocks, int firstBlocks) {
    if (firstBlocks == totalBlocks) return 1;
    int & ret = countCache[totalBlocks][firstBlocks];
    if (ret != -1) return ret;
    int remainBlocks = totalBlocks - firstBlocks;
    ret = 0;
    for (int i = 1; i <= remainBlocks; ++i) {
        ret += (i + firstBlocks - 1) * polyCounts(remainBlocks, i);
        ret %= DIVISOR;
    }
    return ret;
}

int getCounts(int totalBlocks) {
    int counts = 0;
    for (int i = 1; i <= totalBlocks; ++i) {
        counts += polyCounts(totalBlocks, i);
        counts %= DIVISOR;
    }

    return counts;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(countCache, -1, sizeof(countCache));
    int numOfTestCases;
    cin >> numOfTestCases;
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        int inputNum;
        cin >> inputNum;
        cout << getCounts(inputNum) << '\n';
    }

    return 0;
}