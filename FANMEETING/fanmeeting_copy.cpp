#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
 
//두 긴 자연수의 곱을 반환한다
//각 배열에는 각 수의 자릿수가 1의 자리에서부터 시작해 저장되어 있다
//예:multiply([3,2,1], [6,5,4])=123*456=56088=[8, 8, 0, 6, 5]
vector<int> multiply(const vector<int> &a, const vector<int> &b)
{
        vector<int> c(a.size() + b.size() + 1, 0);
        for (int i = 0; i < a.size(); i++)
               for (int j = 0; j < b.size(); j++)
                       c[i + j] += (a[i] * b[j]);
        //normalize(c);
        return c;
}
//a+=b*(10^k)를 구현한다
void addTo(vector<int> &a, const vector<int> &b, int k)
{
        int length = b.size();
        a.resize(max(a.size(), b.size() + k));
 
        for (int i = 0; i< length; i++)
               a[i + k] += b[i]; //이렇게 함으로써 굳이 다른 vector를 선언하지 않아도 되고 간편해졌다
        //정규화 생략
        /*
        for (int i = 0; i < a.size(); i++)
        {
               if (a[i] > 10)
               {
                       a[i + 1] += a[i] / 10;
                       a[i] %= 10;
               }
        }
        */
}
 
//a-=b;를 구현한다 a>=b를 가정한다
void subFrom(vector<int> &a, const vector<int> &b)
{
        int length = b.size();
        a.resize(max(a.size(), b.size()) + 1);
 
        for (int i = 0; i< length; i++)
               a[i] -= b[i];
        //정규화 생략
        /*
        for (int i = 0; i < a.size(); i++)
        {
               if (a[i] < 0)
               {
                       a[i] += 10;
                       a[i + 1] -= 1;
               }
        }
        */
}
 
//두 긴 정수의 곱을 반환한다
//(a0+a1)*(b0+b1)=(a0*b0)(=z0)+(a1*b0+a0*b1)(=z1)+(a1*b1)(=z2)의 원리
vector<int> karatsuba(const vector<int> &a, const vector<int> &b)
{
        int an = a.size(), bn = b.size();
        //a가 b보다 짧을 경우 둘을 바꾼다
        if (an < bn)
               return karatsuba(b, a);
        //기저 사례:a나 b가 비어있는 경우
        if (an == 0 || bn == 0)
               return vector<int>();
        //기저 사례:a가 비교적 짧은 경우 O(n^2) 곱셈으로 변경한다
        if (an <= 50)
               return multiply(a, b);
        int half = an / 2;
        //a와 b를 밑에서 half자리와 나머지로 분리한다
        vector<int> a0(a.begin(), a.begin() + half);
        vector<int> a1(a.begin() + half, a.end());
        vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
        vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
        //z2=a1*b1
        vector<int> z2 = karatsuba(a1, b1);
        //z0=a0*b0
        vector<int> z0 = karatsuba(a0, b0);
        //a0=a0+a1;
        //b0=b0+b1
        addTo(a0, a1, 0);
        addTo(b0, b1, 0);
        //z1=(a0+a1)*(b0+b1)-z0-z2
        vector<int> z1 = karatsuba(a0, b0);
        subFrom(z1, z0);
        subFrom(z1, z2);
        //result=z0+z1*10^half+z2*10^(half*2)
        vector<int> result;
        addTo(result, z0, 0);
        addTo(result, z1, half);
        addTo(result, z2, half + half);
        return result;
}
 
/*
카라츠바의 빠른 곱셈을 이용해 팬미팅 문제를 해결하는 함수
*/
int hugs(const string &members, const string &fans)
{
        int N = members.size(), M = fans.size();
        vector<int> A(N), B(M);
        for (int i = 0; i < N; i++)
               A[i] = (members[i] == 'M') ? 1 : 0;
        for (int i = 0; i < M; i++)
               B[M - i - 1] = (fans[i] == 'M') ? 1 : 0;
        //karatsuba 알고리즘에서 자리 올림은 생략한다
        vector<int> C = karatsuba(A, B); //남자와 남자가 껴안을 경우 1, 그 외 0
        int allHugs = 0;
        for (int i = N - 1; i < M; i++)
               if (C[i] == 0)
                       allHugs++;
        return allHugs;
}
 
int main(void)
{
        int test_case;
        string members, fans;
 
        cin >> test_case;
        if (test_case < 0 || test_case>20)
               exit(-1);
 
        for (int i = 0; i < test_case; i++)
        {
               cin >> members >> fans;
               if (members.size() < 1 || fans.size() < 1 || members.size() > 200000 || fans.size() > 200000)
                       exit(-1);
               cout << hugs(members, fans) << endl;
        }
        return 0;
}