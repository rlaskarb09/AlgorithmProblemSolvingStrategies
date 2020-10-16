#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_CITIES = 50;
const int MAX_DAYS = 100;

double transfer[MAX_CITIES][MAX_CITIES];
double locateProb[MAX_DAYS + 1][MAX_CITIES];

void calcLocateProb(int numOfCities, int days) {
    for (int i = 1; i <= days; ++i) {
        for (int j = 0; j < numOfCities; ++j) {
            for (int k = 0; k < numOfCities; ++k) {
                locateProb[i][j] += locateProb[i-1][k] * transfer[k][j];
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numOfTestCases;
    cin >> numOfTestCases;
    int numOfCities, days, start;
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        cin >> numOfCities >> days >> start;
        for (int i = 0; i < numOfCities; ++i) {
            int count = 0;
            for (int j = 0; j < numOfCities; ++j) {
                int inputNum;
                cin >> inputNum;
                transfer[i][j] = inputNum;
                if (inputNum == 1) count++;
            }
            if (count > 0) 
                for (int j = 0; j < numOfCities; ++j) {
                    transfer[i][j] /= count;
                }
        }
        // init locate probability
        for (int i = 0; i <= days; ++i) {
            for (int j = 0; j < numOfCities; ++j) {
                locateProb[i][j] = 0;
            }            
        }
        locateProb[0][start] = 1.0;
        // calculate probabilities
        calcLocateProb(numOfCities, days);
        // print probabilities of each cities
        int numOfPrints;
        cin >> numOfPrints;
        for (int i = 0; i < numOfPrints; ++i) {
            int cityIdx;
            cin >> cityIdx;
            cout << setprecision(8) << locateProb[days][cityIdx] << ' ';
        }        
        cout << '\n';
    }

    return 0;
}