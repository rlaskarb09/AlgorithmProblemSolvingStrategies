#include <bits/stdc++.h>

using namespace std;

const int MAX_CITIES = 5000;

int N, K;
int L[MAX_CITIES], M[MAX_CITIES], G[MAX_CITIES];

// true if there exist equal to or more than K signs from 0 ~ dist
bool decision(double dist) {
    int signSum = 0;
    
    for (int i = 0; i < N; ++i) {
        if (dist >= L[i]) {
            signSum += M[i] / G[i] + 1;
        }
        else if (dist >= L[i] - M[i] && dist < L[i]) {
            signSum += (int)((dist - (L[i] - M[i])) / G[i]) + 1;
        }

        if (signSum >= K)
            return true;
    }

    return false;
}

int optimize() {
    double low = 0, high = 8030000;
    for (int iter = 0; iter < 100; ++iter) {
        double mid = (low + high) / 2;
        if (decision(mid)) {
            high = mid;
        } else {
            low = mid;
        }
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
            cin >> L[i] >> M[i] >> G[i];
        }

        int result = (int)round(optimize());
        cout << result << '\n';
    }
    

    return 0;
}