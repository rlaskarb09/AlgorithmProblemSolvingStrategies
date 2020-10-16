#include <bits/stdc++.h>


using namespace std;

void normalize(vector<int>& num) {
    num.push_back(0);
    // handle carry
    for (int i = 0; i + 1 < num.size(); ++i) {
        if (num[i] < 0) {
            int borrow = (abs(num[i]) + 9) / 10;
            num[i + 1] -= borrow;
            num[i] += borrow * 10;
        }
        else {
            num[i+1] += num[i] / 10;
            num[i] %= 10;
        }
    }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<int> c(a.size() + b.size() + 1, 0);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            c[i + j] += a[i] * b[j];
        }
    }
    normalize(c);
    for (int i = c.size() - 1; i >= 0; --i) {
        if (c[i] == 0) {
            c.pop_back();
        } else {
            break;
        }
    } 
    return c;
}

void addTo(vector<int>& a, const vector<int>& b, int k) {
    for(int i = 0; i < b.size(); i++) {
        if(a.size() < i + k + 1) {
            a.push_back(0);
        }
        a[i + k] += b[i];
        if (a[i + k] >= 10) {
            a[i + k] -= 10;
            if (a.size() < i + k + 2) {
                a.push_back(1);
            } else {
                a[i + k + 1] += 1;
            }
        }
    }
}

void subFrom(vector<int>& a, const vector<int>& b) {
    int zeroStartIdx = a.size();
    for(int i = 0; i < a.size(); i++) {
        if (i < b.size()) {
            a[i] -= b[i];
        }
        if (a[i] < 0) {
            a[i] += 10;
            a[i + 1] -= 1;
        }
    }
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] == 0) {
            a.pop_back();
        } else {
            break;
        }
    }
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
    int an = a.size(), bn = b.size();
    if (an < bn) return karatsuba(b, a);
    if (an == 0 || bn == 0) return vector<int> ();
    if (an <= 50) return multiply(a, b);
    int half = an / 2;
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
    vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
    vector<int> z2 = karatsuba(a1, b1);
    vector<int> z0 = karatsuba(a0, b0);
    addTo(a0, a1, 0);
    addTo(b0, b1, 0);
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);
    vector<int> ret;
    addTo(ret, z0, 0);
    addTo(ret, z1, half);
    addTo(ret, z2, half + half);
    return ret;
}

int main() {    
    int numA[54] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
                    1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int numB[54] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 
                    9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // int numA[10] = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    // int numB[10] = {2, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    vector<int> numAVec(numA, numA + (sizeof(numA) / sizeof(int)));
    vector<int> numBVec(numB, numB + (sizeof(numB) / sizeof(int)));
    // vector<int> resultVec = multiply(numAVec, numBVec);
    vector<int> resultVec = karatsuba(numBVec, numAVec);
    // subFrom(numAVec, numBVec);
    // for (int i = numAVec.size() - 1; i >= 0; --i) {
    //     printf("%d",numAVec[i]);
    // }
    for (int i = resultVec.size() - 1; i >= 0; --i) {
        cout << resultVec[i];
    }
    printf("\n");

    return 0;
}