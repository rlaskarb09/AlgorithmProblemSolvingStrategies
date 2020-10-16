#include <bits/stdc++.h>

using namespace std;

const int MAX_NUM = 1000;

int N, K;
int visited[MAX_NUM];
struct Course {
    double ratio;
    int r;
    int c;
};
Course courses[MAX_NUM];

bool compare(Course a, Course b)
{
    return a.ratio < b.ratio;
}

// True if cumulativeRank is equal to or smaller than rank with numOfCourses >= K
// bool decision(double rank) {
//     int numerator = 0;
//     int denominator = 0;
//     memset(visited, 0, sizeof(visited));
//     for (int i = 0; i < N - K; ++i) {
//         numerator = 0;
//         denominator = 0;
//         for (int j = 0; j < N; ++j) {
//             if (!visited[j]) {
//                 numerator += courses[j].r;
//                 denominator += courses[j].c;
//             }

//         }
//         double minVal = 987654321;
//         int minIdx = -1;
//         for (int j = 0; j < N; ++j) {
//             if (visited[j]) continue;
//             numerator -= courses[j].r;
//             denominator -= courses[j].c;
//             if (((double)numerator) / denominator < minVal) {
//                 minVal = ((double)numerator) / denominator;
//                 minIdx = j;
//             }
//             numerator += courses[j].r;
//             denominator += courses[j].c;
//         }
//         if (minVal <= rank) return true;
//         visited[minIdx] = 1;
//     }

//     return false;
// }

bool decision (double average) {
    vector<double> v;
    for (int i = 0; i < N; ++i) {
        v.push_back(average * courses[i].c - courses[i].r);
    }
    sort(v.begin(), v.end());
    double sum = 0;
    for (int i = N - K; i < N; ++i) {
        sum += v[i];
    }
    return sum >= 0;
}

double optimize() {
    double high = 1, low = 0;

    for (int it = 0; it < 100; ++it) {
        double mid = (high + low) / 2;
        if (decision(mid))
            high = mid;
        else
            low = mid;
    }

    return high;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        cin >> N >> K;
        for (int i = 0; i < N; ++i) {
            cin >> courses[i].r >> courses[i].c;
            courses[i].ratio = ((double)courses[i].r) / courses[i].c;
        }

        double result = optimize();
        printf("%.10f\n", result);
    }
    return 0;
}