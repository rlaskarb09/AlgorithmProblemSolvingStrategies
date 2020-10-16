#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 10;
const int MAX_WORDS = 50;
const int MAX_WORD_LEN = 100;


bool isMatched(string wildcardWord, string inputWord) {
    vector<int> matchIndices(wildcardWord.size(), 0);
    int wildcardWordSize = wildcardWord.size();
    int inputWordSize = inputWord.size();
    int lastStarIdx = -1;
    int wildcardIdx = 0;
    int inputIdx = -1;
    while (true) {
        if (wildcardIdx == wildcardWordSize && inputIdx == inputWordSize - 1) {
            return true;
        } else if (wildcardIdx >= wildcardWord.size()) {
            if (lastStarIdx >= 0) {
                wildcardIdx = lastStarIdx + 1;
                matchIndices[lastStarIdx] += 1;
                inputIdx = matchIndices[lastStarIdx];
            } else {
                return false;
            }
        } else if (inputIdx >= inputWordSize - 1) {
            if (wildcardWord[wildcardIdx] == '*') {
                matchIndices[wildcardIdx] = inputIdx;
                lastStarIdx = wildcardIdx;
                ++wildcardIdx;
            } else {
                return false;
            }
        }
        else if (wildcardWord[wildcardIdx] == '?') {
            matchIndices[wildcardIdx] = ++inputIdx;
            ++wildcardIdx;
        } else if (wildcardWord[wildcardIdx] == '*') {
            matchIndices[wildcardIdx] = inputIdx;
            lastStarIdx = wildcardIdx;
            ++wildcardIdx;
        } else if (wildcardWord[wildcardIdx] == inputWord[inputIdx + 1]) {
            matchIndices[wildcardIdx] = ++inputIdx;
            ++wildcardIdx;
        } else if (lastStarIdx >= 0) {
            wildcardIdx = lastStarIdx + 1;
            matchIndices[lastStarIdx] += 1;
            inputIdx = matchIndices[lastStarIdx];
        } else {
            return false;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numOfTestCases;
    cin >> numOfTestCases;

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        string wildcardWord;
        vector<string> acceptedWords;
        int numOfWords;
        cin >> wildcardWord;
        cin >> numOfWords;
        for (int i = 0; i < numOfWords; ++i) {
            string inputWord;
            cin >> inputWord;
            if (isMatched(wildcardWord, inputWord)) {
                acceptedWords.push_back(inputWord);
            }
        }
        sort(acceptedWords.begin(), acceptedWords.end());
        for (int i = 0; i < acceptedWords.size(); ++i) {
            cout << acceptedWords[i] << "\n";
        }
    }
}