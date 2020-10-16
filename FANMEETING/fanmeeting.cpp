#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 20;
const int MAX_INPUT_LEN = 200000;

char fansInput[MAX_INPUT_LEN + 1];
char membersInput[MAX_INPUT_LEN + 1];

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
    vector<int> c(a.size() + b.size() - 1, 0);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            c[i + j] += a[i] * b[j];
        }
    }
    // normalize(c);
    return c;
}

void addTo(vector<int>& a, const vector<int>& b, int k) {
    // for(int i = 0; i < b.size(); i++) {
    //     while(a.size() < i + k + 1) {
    //         a.push_back(0);
    //     }

    //     a[i + k] += b[i];
    //     // if (a[i + k] >= 10) {
    //     //     a[i + k] -= 10;
    //     //     if (a.size() < i + k + 2) {
    //     //         a.push_back(1);
    //     //     } else {
    //     //         a[i + k + 1] += 1;
    //     //     }
    //     // }
    // }
    int length = b.size();
    a.resize(max(a.size(), b.size() + k)); 

    for (int i = 0; i< length; i++)
        a[i + k] += b[i];
}

void subFrom(vector<int>& a, const vector<int>& b) {
    // int zeroStartIdx = a.size();
    // for(int i = 0; i < a.size(); i++) {
    //     if (i < b.size()) {
    //         a[i] -= b[i];
    //     }
    //     if (a[i] < 0) {
    //         a[i] += 10;
    //         a[i + 1] -= 1;
    //     }
    // }
    // for (int i = a.size() - 1; i >= 0; --i) {
    //     if (a[i] == 0) {
    //         a.pop_back();
    //     } else {
    //         break;
    //     }
    // }
    for (int i = 0; i < b.size(); ++i)
	{
		a[i] -= b[i];
	}
    while (a.size() > 0 && a.back() == 0) {
        a.pop_back();
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
    // for (int i = ret.size() - 1; i >= 0; --i) {
    //     if (ret[i] == 0) {
    //         ret.pop_back();
    //     } else {
    //         break;
    //     }
    // }
    return ret;
}

int main() {  
    int numOfTestCases;

    scanf("%d", &numOfTestCases);
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        // init
        memset(fansInput, 0, sizeof(fansInput));
        memset(membersInput, 0, sizeof(membersInput));
        // get input
        scanf("%s", membersInput);
        scanf("%s", fansInput);
        // reserve size in advance
        int memberNum = strlen(membersInput);
        int fanNum = strlen(fansInput);
        vector<int> members(memberNum);
        vector<int> fans(fanNum);
        for (int i = 0; i < memberNum; i++) {
            members[i] = (membersInput[i] == 'M') ? 1 : 0;
        }
        for (int i = 0; i < fanNum; i++) {
            fans[fanNum - i - 1] = (fansInput[i] == 'M') ? 1 : 0;
        }

        vector<int> result = karatsuba(members, fans);
     
        int hugNum = 0;
        for (int i = members.size() - 1; i < fans.size(); i++) {
            if (result[i] == 0) {
                ++hugNum;
            }
        }

        printf("%d\n", hugNum);        
    }

    return 0;
}