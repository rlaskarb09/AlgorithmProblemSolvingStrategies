#include <bits/stdc++.h>

using namespace std;

const int MAX_ = 1000000000 + 1;
const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";
int length[51];

char expand(const string& dragonCurve, int generations, int skip) {
    if (generations == 0) {
        assert (skip < dragonCurve.size());
        return dragonCurve[skip];
    }
    for (int i = 0; i < dragonCurve.size(); ++i) {
        if(dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
            if(skip >= length[generations])
                skip -= length[generations];
            else if (dragonCurve[i] == 'X')
                return expand(EXPAND_X, generations-1, skip);
            else
                return expand(EXPAND_Y, generations-1, skip);
        }
        else if (skip > 0)
            --skip;
        else
            return dragonCurve[i];        
    }
    return '#'; // not executed
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    length[0] = 1;
    for (int i = 1; i <= 50; ++i) {
        length[i] = min(MAX_, length[i -1] * 2 + 2);
    }

    int numOfTests;
    cin >> numOfTests;
    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N, P, L;
        string dragon("FX");
        string answer;
        cin >> N >> P >> L;
        for (int i = 0; i < L; ++i) {
            answer.push_back(expand(dragon, N, P + i - 1));
        }
        cout << answer << endl;
    }

    return 0;
}