#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_INPUT_LEN = 100;
const int MAX_INPUT_NUM = 1000;
const int MAX_S = 10;
const int MAX_INT = 987654321;

struct SameNumbers {
    int number;
    int numOfNumbers;
};

int inputLen;
int inputs[MAX_INPUT_NUM];
int s;
vector<SameNumbers> sameNumbers;
int cache[MAX_INPUT_LEN][MAX_S + 1];

int getPartialMse (int beginIdx, int endIdx) {
    int mean;
    int sum = 0;
    int count = 0;
    int mse = 0;

    for (int i = beginIdx; i < endIdx; ++i) {
        sum += sameNumbers[i].number * sameNumbers[i].numOfNumbers;
        count += sameNumbers[i].numOfNumbers;
    }
    if (count > 0) {
        mean = int(round(((double)sum) / count));
        for (int i = beginIdx; i < endIdx; ++i) {
            mse += (sameNumbers[i].number - mean) * (sameNumbers[i].number - mean) * sameNumbers[i].numOfNumbers;
        }
    }

    return mse;
}

int getMse (int idx, int currentS) {
    if (idx <= currentS - 1) return 0;
    int & ret = cache[idx][currentS];
    if (ret != -1) return ret;
    if (currentS == 1) {
        ret = getPartialMse(0, idx + 1);
        return ret;
    }
    ret = MAX_INT;
    for (int i = currentS - 1; i <= idx; ++i) {
        ret = min(ret, getMse(i - 1, currentS -1) + getPartialMse(i, idx + 1));
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTestCases;

    cin >> numOfTestCases;

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        sameNumbers.clear();
        memset(cache, -1, sizeof(cache));
        cin >> inputLen >> s;
        for (int i = 0; i < inputLen; ++i) {
            cin >> inputs[i];
        }
        sort(inputs, inputs + inputLen);

        int startIdx = 0;
        int currentNum = inputs[0];
        for (int i = 1; i < inputLen; ++i) {
            if (inputs[i] != currentNum) {
                sameNumbers.push_back({currentNum, i - startIdx});
                startIdx = i;
                currentNum = inputs[i];
            }
            if (i == inputLen - 1) {
                sameNumbers.push_back({currentNum, i - startIdx + 1});
            }
        }

        if (sameNumbers.size() <= s) {
            cout << "0\n";
            continue;
        }

        cout << getMse(sameNumbers.size() - 1, s) << '\n';
    }
    
    return 0;
}   