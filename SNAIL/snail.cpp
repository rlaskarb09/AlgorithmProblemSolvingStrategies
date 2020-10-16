#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_DEPTH = 1000;
const int MAX_DAYS = 1000;

int depth, days;
double cache[MAX_DAYS + 1][2 * MAX_DEPTH + 1];

double climb (int day, int climbed) {
    if (day == days) return climbed >= depth ? 1.0 : 0.0;
    double& ret = cache[day][climbed];
    if (ret != -1.0) return ret;
    return ret = (0.75 * climb(day + 1, climbed + 2)) + (0.25 * climb(day + 1, climbed + 1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTestCases;

    cin >> numOfTestCases;

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        cin >> depth >> days;
        for (int i = 0; i < days + 1; ++i) {
            for (int j = 0; j < 2 * depth + 2; ++j) {
                cache[i][j] = -1.0;
            }
        }
        printf("%.10f\n", climb(0, 0));
    }


    return 0;
}

