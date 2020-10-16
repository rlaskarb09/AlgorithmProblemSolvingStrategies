#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_ELEMENTS = 500;

int inputElements[MAX_ELEMENTS + 1];
int currentLen[MAX_ELEMENTS + 1];
int numOfElements;

int getLis() {
    for (int i = 1; i <= numOfElements; i++) {
        int maxIdx = 0;
        for (int j = 0; j < i; ++j) {
            if (inputElements[j] < inputElements[i] && currentLen[j] > currentLen[maxIdx]) {
                maxIdx = j;
            }
        }
        currentLen[i] = currentLen[maxIdx] + 1;
    }

    return *max_element(currentLen, currentLen + (numOfElements + 1));
}

int main() {
    int numOfTestCases;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> numOfTestCases;

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        memset(currentLen, 0, sizeof(currentLen));
        cin >> numOfElements;
        for (int i = 1; i <= numOfElements; ++i) {
            cin >> inputElements[i];
        }
        cout << getLis() << "\n";
    }
    return 0;
}