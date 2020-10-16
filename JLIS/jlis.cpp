#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_LEN = 100;

const long long NEGINF = numeric_limits<long long>::min();

int aSize, bSize, A[100], B[100];
int cache[101][101];

int jlis(int indexA, int indexB) {
    int& ret = cache[indexA + 1][indexB + 1];
    if (ret != -1) return ret;
    ret = 0;
    long long a = (indexA == -1? NEGINF : A[indexA]);
    long long b = (indexB == -1? NEGINF : B[indexB]);
    long long maxElement = max(a, b);

    for (int nextA = indexA + 1; nextA < aSize; ++nextA)
        if (maxElement < A[nextA])
            ret = max(ret, jlis(nextA, indexB) + 1);
    for (int nextB = indexB + 1; nextB < bSize; ++nextB)
        if (maxElement < B[nextB])
            ret = max(ret, jlis(indexA, nextB) + 1);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTestCases;

    cin >> numOfTestCases;
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        memset(cache, -1, sizeof(cache));
        cin >> aSize >> bSize;
        for (int i = 0; i < aSize; ++i) {
            cin >> A[i];
        }
        for (int i = 0; i < bSize; ++i) {
            cin >> B[i];
        }
        cout << jlis (-1, -1) << '\n';
    }

}