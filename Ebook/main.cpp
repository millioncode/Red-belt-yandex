#include <iostream>
#include <string>
#include <deque>
#include <set>
#include <map>
#include <tuple>
#include <test_runner.h>
using namespace std;
static const int DAY_SEC = 86400;
class abc_time {
    public:
        abc_time(const long long& t): time(t) {}
        long long time;
};
class rooms_time: public abc_time {
    public:
        explicit rooms_time(const long long& t, const int& r) : abc_time(t), rooms_count(r) {}
        int rooms_count;
};
struct BookInfo {
        void CHANGE(const long long& time, const int& client_id,
                    const int& room_count) {
            if (book_info_.count(client_id) == 0 ) {
                ++last_uniq_clients_;
            }
            book_info_[client_id].push_back(rooms_time(time, room_count));
            reserved_rooms_ += room_count;
        }
        void UPDATE(const long long& time) {
            for(auto& clients: book_info_) {
                for(auto& rooms: clients.second) {
                    if (time - rooms.time >= DAY_SEC) {
                        reserved_rooms_ -= rooms.rooms_count;
                        clients.second.pop_front();
                    }
                    else break;
                }
                if (clients.second.empty()) {
                    int name = clients.first;
                    book_info_.erase(name);
                    --last_uniq_clients_;
                }
            }
        }
        map <int, deque<rooms_time>> book_info_;
        int reserved_rooms_ = 0;
        int last_uniq_clients_ = 0;
};
class Hotels {
    public:
        Hotels() {}
        void BOOK(const long long& time, const string& name, const int& client_id,
                 const int& room_count) {
            if (all_data_base.count(name)==0) all_data_base[name]= BookInfo();
            all_data_base[name].CHANGE(time, client_id, room_count);
            time_ = time;
            for(auto& hotels : all_data_base) {
                hotels.second.UPDATE(time_);
            }
        }
        int CLIENTS(const string& name) const {
            if (all_data_base.lower_bound(name) == all_data_base.end() ) return 0;
            return all_data_base.at(name).last_uniq_clients_;
        }
        int ROOMS(const string& name) const {
            if (all_data_base.lower_bound(name) == all_data_base.end() ) return 0;
            return all_data_base.at(name).reserved_rooms_;
        }
    private:
        map <string, BookInfo> all_data_base;
        long long time_ = 0;
};
//BOOK time hotel_name client_id room_count
void Test() {
    Hotels hotels;
    ASSERT_EQUAL(hotels.CLIENTS("Marriott"), 0);
    ASSERT_EQUAL(hotels.ROOMS("Marriott"), 0);

    hotels.BOOK(10, "FourSeasons", 1, 2);
    ASSERT_EQUAL(hotels.CLIENTS("FourSeasons"), 1);
    ASSERT_EQUAL(hotels.ROOMS("FourSeasons"), 2);

    hotels.BOOK(10, "Marriott", 1, 1);
    hotels.BOOK(86409, "FourSeasons", 2, 1);
    ASSERT_EQUAL(hotels.CLIENTS("FourSeasons"), 2);
    ASSERT_EQUAL(hotels.ROOMS("FourSeasons"), 3);
    ASSERT_EQUAL(hotels.CLIENTS("Marriott"), 1);
    hotels.BOOK(86410, "Marriott", 2, 10);
    ASSERT_EQUAL(hotels.ROOMS("FourSeasons"), 1);
    ASSERT_EQUAL(hotels.ROOMS("Marriott"), 10);
}
int main()
{
    Test();
    Hotels hotels;
    int Q;
    cin >> Q;
    for(int i=0; i<Q; i++) {
        string comm;
        cin >> comm;
        if (comm=="BOOK") {
            int time, client_id, room_count;
            string hotel_name;
            cin >> time >> hotel_name >> client_id >> room_count;
            hotels.BOOK(time, hotel_name, client_id, room_count);
        } else if (comm=="CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << hotels.CLIENTS(hotel_name) << endl;
        }
        else if (comm=="ROOMS") {
             string hotel_name;
             cin >> hotel_name;
             cout << hotels.ROOMS(hotel_name) << endl;
        }
    }
    return 0;
}
