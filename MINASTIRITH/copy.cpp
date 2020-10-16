#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
 
const int INF = 987654321;
const double pi = 2.0*acos(0); //cos(π/2)=0 -> 따라서 아크코사인(0)=π/2
int postNum;
double y[100], x[100], r[100]; //y 좌표, x 좌표, 경계 반지름
pair<double, double> ranges[100]; //활꼴의 시작과 끝 지점
 
int solveLinear(double, double); //미리 선언
 
//초소 반경들을 미나스아노르의 구간(활꼴)으로 바꾸기
void convertToRange(void)
{
        for (int i = 0; i < postNum; i++)
        {
            //tan(loc)=y[i]/x[i] -> arctan(y[i]/x[i]) = loc
            double loc = fmod(2 * pi + atan2(y[i], x[i]), 2 * pi);
            //sin(θ)=(r[i]/2.0)/8.0 이므로 θ를 구하기 위해선 arcsin
            double range = 2.0*asin(r[i] / 2.0 / 8.0);
            ranges[i] = make_pair(loc - range, loc + range); //loc-range, loc+range는 [0, 2π] 범위 초과할 수 있음
        }
}
 
//ranges[i]의 범위가 [0, 2π] 범위 초과할 수 있으므로 다음 조건을 확인해야됨
//0을 덮는 구간이 하나만 포함된다면 최적해
//두개 이상 포함될 경우
//1. 두 구간의 중심 사이에 0이 있을 경우 어느 구간을 선택해도 됨
//2. 두 구간의 중심 사이에 0이 없을 경우 0과 더 가까운 쪽 선택
int solveCircular(void) //0을 덮을 구간을 선택하고 나머지를 선형으로 푼다
{
        int result = INF;
        //각 구간을 시작 위치의 오름차순으로 정렬
        sort(ranges, ranges + postNum);
        //0을 덮을 구간 선택
        for (int i = 0; i < postNum; ++i) {
        }
        for (int i = 0; i < postNum; i++)
               if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi)
               {
                       //0을 덮는 부분을 빼고 남는 중심각의 범위는 아래와 같다
                       double begin = fmod(ranges[i].second, 2 * pi);
                       double end = fmod(ranges[i].first + 2 * pi, 2 * pi);
                       //[begin,end] 선분을 주어진 구간을 사용해서 덮는다
                       result = min(result, 1 + solveLinear(begin, end));
               }
        return result;

}

int solveLinear(double begin, double end)
{
    cout <<"solveLinear:: begin: " << begin << ", end: " << end << endl;
        int used = 0, idx = 0;
        //덮지 못한 선분이 남아있는 동안 계속(다 덮는다면 반복문 탈출)
        while (begin < end)
        {
               //begin보다 이전에 시작하는 구간 중 가장 늦게 끝나는 구간 찾는다
               double maxCover = -1;
               while (idx < postNum && ranges[idx].first <= begin)
               {
                       maxCover = max(maxCover, ranges[idx].second);
                       idx++;
               }
               //덮을 구간을 찾지 못한 경우
               if (maxCover <= begin)
                       return INF;
               //선분의 덮인 부분 잘라낸다
               begin = maxCover;
               used++;
        }
        cout <<"solveLinear:: return: " << used << endl;
        return used;
}
 
int main(void)
{
        int test_case;
        cin >> test_case;
        if (test_case < 1 || test_case>50)
               exit(-1);
 
        for (int i = 0; i < test_case; i++)
        {
               cin >> postNum;
               if (postNum < 1 || postNum>100)
                       exit(-1);
               for (int j = 0; j < postNum; j++)
                       cin >> y[j] >> x[j] >> r[j];
               convertToRange(); //초소 반경들을 변경
               cout.precision(8);
               if (solveCircular() != INF)
                       cout << solveCircular() << endl;
               else
                       cout << "IMPOSSIBLE" << endl;
        }
        return 0;
}