// не проходит 7/7 тест 0.99/0.8 - как ускорить хз
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include "test_runner.h"
#include "profile.h"
using namespace std;
void Add(list <unsigned>& sports, const vector<pair<unsigned, unsigned>>& mans) {
    for(const auto& m : mans) {
        auto it = sports.begin();
        for (; it!=sports.end(); ++it) {
            if (*it==m.second) break;
        }
        sports.insert(it, m.first);
    }
}

void Test() {
    {
        LOG_DURATION("time ");
        list <unsigned> sportsmens;
//        Add(sportsmens, {42,0});
//        Add(sportsmens, {17, 42});
//        Add(sportsmens, {13, 0});
//        Add(sportsmens, {123, 42});
//        Add(sportsmens, {5, 13});
        vector <pair<unsigned, unsigned>> aaa = {{42,0}, {17, 42}, {13, 0}, {123, 42}, {5, 13}};
        Add(sportsmens, aaa);
        list <unsigned> value {17, 123, 42, 5, 13};
        if (value == sportsmens) cerr << "OK" << endl;
    }
}
int main()
{
    Test();
    size_t N;
    cin >> N;
    list <unsigned> sportsmens;
    vector < pair<unsigned, unsigned>> mans;
    //mans.reserve(N);
    unsigned first, second;
    for(size_t i=0; i<N; ++i) {
        cin >> first >> second;
        mans.push_back(make_pair(first, second));
    }
    Add(sportsmens, mans );
    for(const auto& i : sportsmens) {
        cout << i << " ";
    }
    return 0;
}
