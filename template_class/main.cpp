#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <set>
#include <deque>
using namespace std;

template <typename T, typename U>
struct Pair {
  T first;
  U second;
};

template <typename Iter>
struct IterRange {

        Iter first;
        Iter last;

        Iter begin() const {
            return first;
        }

        Iter end() const {
            return last;
        }
};

template <typename Container>
IterRange<typename Container::iterator>
    HEAD(Container& v, const size_t top) {
         return {
            v.begin(), next( v.begin(), min(top, v.size()) )
         };
}
template <typename T>
size_t RangeSize(IterRange <T> v) {
    return v.end()-v.begin();
}
template <typename Iterator>
IterRange<Iterator> MakeRange(Iterator begin, Iterator end) {
    return IterRange<Iterator>{begin, end};
}
int main()
{
    Pair <string, int> si;
    si.first = "hello";
    si.second = 5;
    //------------------------------>
    vector <int> v {1,2,3,4,5};
    for(int& x:HEAD(v, 3) ) {
        x++;
    }
    for(int x:HEAD(v, v.size()) ) {
        cout << x << " ";
    }
    cout << endl;
    //------------------------------>
    cout << RangeSize(HEAD(v,3)) << endl;
    //-------------------------------->

    auto second_half = MakeRange(
                v.begin()+v.size()/2, v.end() );
    for(auto& i : second_half) {
        cout << i << " ";
    }
    //--------------------------------?
    set<int> s = {5,2,3,4,1};
//    auto third_half = MakeRange(
//                s.begin()+s.size()/2, s.end() );
    cout << "\n-------------->" << endl;
    for(int i : HEAD(s, 4) ) {
        cout << i << " ";
    }
    cout << endl;
    deque<int> d {1,2,3,4,5};
    for(auto i:HEAD(d,4) ) {
        cout << i << " ";
    }
    return 0;
}
