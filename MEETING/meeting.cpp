#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_INPUT_LEN = 10000;

int man[MAX_INPUT_LEN + 1];
int woman[MAX_INPUT_LEN + 1];
int gap[MAX_INPUT_LEN + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTestCases;
    cin >> numOfTestCases;
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        int inputLen;
        cin >> inputLen;
        for (int i = 0; i < inputLen; ++i) {
            cin >> man[i];
        }
        for (int i = 0; i < inputLen; ++i) {
            cin >> woman[i];
        }
        sort(man, man + inputLen);
        sort(woman, woman + inputLen);

        int sum = 0;
        for (int i = 0; i < inputLen; ++i) {
            sum += abs(man[i] - woman[i]);
        }
        cout << sum << '\n';
        
    }
    return 0;
}