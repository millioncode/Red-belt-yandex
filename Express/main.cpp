#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "test_runner.h"

using namespace std;

class RouteManager {
    public:
        void AddRoute(const int& start, const int& finish) {
            reachable_lists_[start].insert(finish);
            reachable_lists_[finish].insert(start);
        }

        int FindNearestFinish(int start, int finish) const {
            int result1 = abs(start - finish);
            if (reachable_lists_.count(start) == 0) {
                return result1;
            }
            const set<int>& reachable_stations = reachable_lists_.at(start);
            if (!reachable_stations.empty()) {
                auto it_low = reachable_stations.lower_bound(finish);
                auto it_upp = reachable_stations.upper_bound(finish);
                int result2;
                if (*it_low==finish) return 0;
                else {
                    if (it_upp==reachable_stations.end() ) {
                        result2 = abs(finish - *prev(it_low));
                    }
                    else {
                        result2 = min(abs(finish - *prev(it_low)), abs(finish - *it_upp) );
                    }
                }
                result1 = min(result1, result2 );
            }
            return result1;
        }
    private:
        map<int, set<int>> reachable_lists_;
};
void test() {
    RouteManager routes;
    routes.AddRoute(-2, 5);
    routes.AddRoute(5, 8);
    routes.AddRoute(10, 4);
    ASSERT_EQUAL(routes.FindNearestFinish(4, 10), 0);
    ASSERT_EQUAL(routes.FindNearestFinish(4, -2), 6);
    ASSERT_EQUAL(routes.FindNearestFinish(5, 0), 2);
    ASSERT_EQUAL(routes.FindNearestFinish(5, 100), 92);
}
int main() {
    RouteManager routes;
    test();
    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }
    return 0;
}
