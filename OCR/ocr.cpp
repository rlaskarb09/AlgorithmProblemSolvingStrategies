#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int M, Q;
    cin >> M >> Q;
    vector<double> init(M);
    vector<vector<double>> prior(M, vector<double>(M)), trans(M, vector<double>(M));
    map<string, int> strToIdx;
    vector<string> idxToStr(M);
    for (int i = 0; i < M; ++i) {
        string word;
        cin >> word;
        strToIdx.insert(make_pair(word, i));
        idxToStr[i] = word;
    }
    for (int i = 0; i < M; ++i) {
        cin >> init[i];
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> trans[i][j];
        }
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> prior[i][j];
        }
    }

    for (int testIdx = 0; testIdx < Q; ++testIdx) {
        int numOfWords;
        cin >> numOfWords;
        vector<int> wordIdx;
        vector<vector<double>> prob(numOfWords, vector<double>(M));
        vector<vector<int>> prevIdx (numOfWords, vector<int>(M));
        for (int i = 0; i < numOfWords; ++i) {
            string inputWord;
            cin >> inputWord;
            wordIdx.push_back(strToIdx.find(inputWord)->second);
        }
        for (int j = 0; j < M; ++j) {
            prob[0][j] = init[j] * prior[j][wordIdx[0]];
        }

        for (int i = 1; i < numOfWords; ++i) {
            for (int j = 0; j < M; ++j) {
                for (int k = 0; k < M; ++k) {
                    double num = prob[i - 1][k] * trans[k][j] * prior[j][wordIdx[i]];
                    if (prob[i][j] < prob[i - 1][k] * trans[k][j] * prior[j][wordIdx[i]]) {
                        prevIdx[i][j] = k;
                        prob[i][j] = prob[i - 1][k] * trans[k][j] * prior[j][wordIdx[i]];
                    }
                }
            }
        }
        int maxIdx = -1;
        double maxVal = -1;
        for (int i = 0; i < prob[numOfWords - 1].size(); ++i) {
            if (prob[numOfWords - 1][i] > maxVal) {
                maxIdx = i;
                maxVal = prob[numOfWords - 1][i];
            }
        }

        vector<string> answer;
        for (int i = numOfWords - 1; i >= 0; --i) {
            answer.push_back(idxToStr[maxIdx]);
            maxIdx = prevIdx[i][maxIdx];
        }

        for (auto it = answer.rbegin(); it != answer.rend(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
    
    return 0;
}