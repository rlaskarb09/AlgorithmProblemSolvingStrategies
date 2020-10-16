#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAX_N = 12;
const int MAX_M = 10;
const int MAX_L = 10;

int N, K, M, L;
int prerequisite[MAX_N];
int classes[MAX_M];
int cache[MAX_M][1 << MAX_N];

// get the number of courses taken
int bitCount (int n) {
    return __builtin_popcount(n);
}

void printBit (int n) {
    unsigned int un = n;
    for (int i = 0; i < 32; ++i) {
        cout << (un % 2);
        un = (un >> 1);
    }
}


int graduate (int semester, int taken) {
    if (bitCount(taken) >= K) return 0;
    if (semester == M) return INF;
    int& ret = cache[semester][taken];
    if (ret != -1) return ret;
    ret = INF;
    // canTake: courses that are not taken and opened in this semester.
    int canTake = (classes[semester] & ~taken);
    // for each classes that i canTake, check satisfying the prerequisit.
    for (int i = 0; i < N; ++i) {
        if ((canTake & (1 << i)) &&
            (taken & prerequisite[i]) != prerequisite[i])
            canTake &= ~(1 << i);
    }
    // now canTake is really can take => courses that opens in this semester && not taken && prerequisit-satisfying
    // for every cases
    for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
        if(bitCount(take) > L) continue;
        ret = min(ret, graduate(semester + 1, taken | take) + 1);
    }
    ret = min(ret, graduate(semester + 1, taken));
    return ret;
}

int main() {
    int numOfTests;
    cin >> numOfTests;
    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        memset(cache, -1, sizeof(cache));
        memset(classes, 0, sizeof(classes));
        memset(prerequisite, 0, sizeof(prerequisite));
        cin >> N >> K >> M >> L;
        for (int i = 0; i < N; ++i) {
            int num, preReqIdx;
            cin >> num;
            for (int j = 0; j < num; ++j) {
                cin >> preReqIdx;
                prerequisite[i] |= (1 << preReqIdx); 
            }
        }
        for (int i = 0; i < M; ++i) {
            int num, courseIdx;
            cin >> num;
            for (int j = 0; j < num; ++j) {
                cin >> courseIdx;
                classes[i] |= (1 << courseIdx); 
            }
        }
        int result = graduate(0, 0);
        if (result == INF)
            cout << "IMPOSSIBLE\n";
        else
            cout << result << '\n';
        
    }

    return 0;
}