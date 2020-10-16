#include <bits/stdc++.h>

using namespace std;

vector<int> getPartialMatch(const string& N) {
    int m = N.size();
    vector<int> pi(m, 0);

    int begin = 1, matched = 0;
    while(begin + matched < m) {
        if (N[begin + matched] == N[matched]) {
            ++matched;
            pi[begin + matched - 1] = matched;
        }
        else {
            if (matched == 0)
                ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];    
            }
        }
    }
    return pi;
}

vector<int> kmpSearch(const string& a, const string& b) {
    int aSize = a.size(), bSize = b.size();
    vector<int> result;
    vector<int> pi = getPartialMatch(b);
    int begin = 0, matched = 0;
    while (begin + bSize <= aSize) {
        if (matched < bSize && a[begin + matched] == b[matched]) {
            ++matched;
            if (matched >= bSize) {
                result.push_back(begin);
            }
        }
        else {
            if (matched == 0)
                ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return result;
}

int getFirstIdx(const string& a, const string& b) {
    int aSize = a.size(), bSize = b.size();
    vector<int> pi = getPartialMatch(b);
    int begin = 0, matched = 0;
    while (begin + bSize <= aSize) {
        if (matched < bSize && a[begin + matched] == b[matched]) {
            ++matched;
            if (matched >= bSize) {
                return begin;
            }
        }
        else {
            if (matched == 0)
                ++begin;
            else {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return 0;
}

int getNumOfShifts (const string& a, const string& b) {
    return getFirstIdx(a + a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N;
        cin >> N;
        int answer = 0;
        vector<string> inputs(N + 1);
        for (int i = 0; i <= N; ++i) {
            cin >> inputs[i];
        }
        for (int i = 0; i < N; ++i) {
            if (i % 2 == 0) 
                answer += getNumOfShifts(inputs[i+1], inputs[i]);
            else
                answer += getNumOfShifts(inputs[i], inputs[i+1]);
        }
        cout << answer << endl;
    }

    return 0;
}