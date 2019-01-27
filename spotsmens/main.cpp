/* 0.09/0.8 - если знаете как еще ускорить - пишите на scfocus@yandex.ru
*/
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
#include "test_runner.h"
#include "profile.h"
using namespace std;
void Add(list <unsigned>& sports, const vector<pair<unsigned, unsigned>>& mans) {
    // сохраняем в переменную конец листа - для ускорения на 0.8
    auto it_end_sports = sports.end();
    // вектор итерраторов на соответствующие элементы. Инициализирую концом листа - т.к.
    //могут быть значения, которых нет в базе
    vector <list <unsigned>::iterator> adress (100001, it_end_sports);
    // константную сложность делаю.
    for(const auto& m : mans) {
        auto it_adress = adress[m.second];
        adress[m.first] = sports.insert(it_adress, m.first);
    }
}
void Test() {
        list <unsigned> sportsmens;
        vector <pair<unsigned, unsigned>> aaa = {{42,0}, {17, 42}, {13, 0}, {123, 42}, {5, 13}};
        Add(sportsmens, aaa);
        list <unsigned> value {17, 123, 42, 5, 13};
        if (value == sportsmens) cerr << "OK" << endl;
}
int main()
{
    Test();
    // отключение даст выигрыш 0.04
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t N;
    cin >> N;
    list <unsigned> sportsmens;
    vector < pair<unsigned, unsigned>> mans;
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
