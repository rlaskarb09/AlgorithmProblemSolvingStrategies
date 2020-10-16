#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MIN_INPUT_LEN = 8;
const int MAX_INPUT_LEN  = 10000;
const int BIG_INT = 987654321;

char inputChar[MAX_INPUT_LEN + 1];
int input[MAX_INPUT_LEN + 1];
int cache[MAX_INPUT_LEN + 1];

int getScore(int startIdx, int digits) {
    // every digits same -> return 1
    bool returnFlag = true;
    int firstNum = input[startIdx];
    int secondNum = input[startIdx + 1];
    for (int i = 1; i < digits; i++) {
        if (input[startIdx + i] != firstNum) {
            returnFlag = false;
            break;
        }
    }
    if (returnFlag) return 1;
    returnFlag = true;
    // increasing or decreasing by 1 -> return 2
    for (int i = 1; i < digits; i++) {
        if (input[startIdx + i] != firstNum + i) {
            returnFlag = false;
            break;
        }
    }
    if (returnFlag) return 2;
    returnFlag = true;
    for (int i = 1; i < digits; i++) {
        if (input[startIdx + i] != firstNum - i) {
            returnFlag = false;
            break;
        }
    }
    if (returnFlag) return 2;
    returnFlag = true;
    // repeat two number -> return 4
    for (int i = 2; i < digits; ++i) {
        if (i % 2 == 0) {
            if (input[startIdx + i] != firstNum) {
                returnFlag = false;
                break;
            }
        } else {
            if (input[startIdx + i] != secondNum) {
                returnFlag = false;
                break;
            }
        }
    }
    if (returnFlag) return 4;
    returnFlag = true;
    // an arithmetical progression -> return 5
    int gap = secondNum - firstNum;
    for (int i = 2; i < digits; ++i) {
        if (input[startIdx + i] - input[startIdx + i - 1] != gap) {
            returnFlag = false;
            break;
        }
    }
    if (returnFlag) return 5;
    // else, return 10
    return 10;
}

int piDifficulty(int idx) {
    if (idx < 3) return BIG_INT;
    int& ret = cache[idx];
    if (ret != -1) return ret;
    
    if (idx <= 5) {
        ret = getScore(1, idx);
        return ret;
    }
    int minScore = BIG_INT;
    minScore = min(minScore, piDifficulty(idx - 3) + getScore(idx - 2, 3));
    minScore = min(minScore, piDifficulty(idx - 4) + getScore(idx - 3, 4));
    minScore = min(minScore, piDifficulty(idx - 5) + getScore(idx - 4, 5));

    ret = minScore;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTestCases;
    cin >> numOfTestCases;
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        memset(cache, -1, sizeof(cache));
        cin >> inputChar;
        int length = strlen(inputChar);
        for (int i = 0; i < length; i++) {
            input[i + 1] = inputChar[i] - '0';
        }
        cout << piDifficulty(length) << '\n';
    }

    return 0;
}