#include <bits/stdc++.h>

using namespace std;

const int MAX_INPUT_SIZE = 100;
const long long DIVISOR = 1000000007;


long long cache[MAX_INPUT_SIZE + 1];

long long fibo (int num) {
    if (num == 1) return 1;
    if (num == 2) return 2;
    long long & ret = cache[num];
    if (ret != -1) return ret;
    ret = (fibo(num - 1) + fibo(num - 2)) % DIVISOR;
    return ret;
}

int tileCount (int num) {
    if (num <= 2) return 0;
    if (num % 2 == 1) {
        return (fibo(num) - fibo(num / 2) + DIVISOR) % DIVISOR;
    } else {
        return (fibo(num) + DIVISOR - fibo(num / 2) + DIVISOR - fibo((num / 2) - 1)) % DIVISOR;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numOfTestCases;
    int input;

    cin >> numOfTestCases;
    memset(cache, -1, sizeof(cache));
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        cin >> input;
        cout << tileCount(input) << '\n';
    }
    return 0;
}