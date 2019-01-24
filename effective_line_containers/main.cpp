#include <iostream>
#include <vector>
#include "profile.h"

using namespace std;
const int SIZE = 10000000;
template <typename T>
void LogVecPararm(const vector<T>& v) {
    cout <<"Length = " << v.size() << ", ";
    cout <<"Capacity = " << v.capacity() << endl;
    const T* ptr = v.data();
    for(size_t i=0; i<v.capacity(); ++i) {
        cout <<ptr+i << " = " <<  *(ptr+i) << endl;
    }
}
int main()
{
    vector <int> v {1,2,3};
    LogVecPararm(v);
    v.push_back(4);
    LogVecPararm(v);
    v.shrink_to_fit();
    LogVecPararm(v);
    int value;
    {
        LOG_DURATION("push_back_1_without");
        vector<int> v1;
        {
            LOG_DURATION("insert push_back_1_without:")
            for(int i=0; i<SIZE; i++) {
                v1.push_back(i);
            }
        }
    }
    {
        LOG_DURATION("push_back_with_w/o_reserve");
        vector<int> v2(SIZE);
        v2.shrink_to_fit();
        {
            LOG_DURATION("insert push_back_with_w/o_reserve");
            for(int i=0; i<SIZE; i++) {
                v2.push_back(i);
            }
        }
    }
    {
        LOG_DURATION("push_back_with_reserve");
        vector<int> v2;
        v2.reserve(SIZE);
        {
            LOG_DURATION("insert push_back_with_reserve")
            for(int i=0; i<SIZE; i++) {
                v2.push_back(i);
            }
        }
    }
    {
        LOG_DURATION("push_back_with_reserve_+1");
        vector<int> v2;
        v2.reserve(SIZE);
        {
            LOG_DURATION("insert push_back_with_reserve_+1")
            for(int i=0; i<SIZE+1; i++) {
                v2.push_back(i);
            }
        }
    }
    return 0;
}
