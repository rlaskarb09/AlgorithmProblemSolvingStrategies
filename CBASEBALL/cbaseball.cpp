#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numOfTestCases;
    cin >> numOfTestCases;

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        int aScore, bScore;
        cin >> aScore >> bScore;
        if (bScore < aScore) cout << 0 << '\n';
        else cout << (bScore - aScore) + 4 << '\n';
    }


    return 0;
}
