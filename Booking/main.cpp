#include <iostream>
#include <string>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <stdint.h>
#include <test_runner.h>
using namespace std;
static const int DAY_SEC = 86400;

struct rooms_time {
        explicit rooms_time(const int64_t & t, const int& r, const int& c) : time(t), rooms_count(r), client(c) {}
        int64_t time;
        int rooms_count;
        int client;
};
struct BookInfo {
        void CHANGE(const int64_t& time, const int64_t& client_id,
                    const int& room_count) {
            if (client_count_.lower_bound(client_id) == client_count_.end() ) {
                client_count_[client_id] = 1;
                ++last_uniq_clients_;
            } else ++client_count_.at(client_id);

            book_info_.push(rooms_time(time, room_count, client_id));
            reserved_rooms_ += room_count;
        }
        void UPDATE(const int64_t& time) {
            while ( !book_info_.empty() && book_info_.front().time <= time - DAY_SEC )
            {
                    reserved_rooms_ -= book_info_.front().rooms_count;
                    --client_count_[book_info_.front().client];
                    book_info_.pop();
            }
            for(auto& x : client_count_) {
                if (x.second == 0) {
                    client_count_.erase(x.first);
                    --last_uniq_clients_;
                }
            }
        }
        queue <rooms_time> book_info_;
        map <int, int64_t> client_count_;

        int reserved_rooms_ = 0;
        int64_t last_uniq_clients_ = 0;
};
class Hotels {
    public:
        Hotels() {}
        void BOOK(const int64_t& time, const string& name, const int& client_id,
                 const int& room_count) {
            if (all_data_base.lower_bound(name)==all_data_base.end() ) all_data_base[name]= BookInfo();
            all_data_base[name].CHANGE(time, client_id, room_count);
            time_ = time;
            for(auto& hotels : all_data_base) {
                hotels.second.UPDATE(time_);
            }
        }
        int64_t CLIENTS(const string& name) const {
            if (all_data_base.lower_bound(name) == all_data_base.end() ) return 0;
            return all_data_base.at(name).last_uniq_clients_;
        }
        int ROOMS(const string& name) const {
            if (all_data_base.lower_bound(name) == all_data_base.end() ) return 0;
            return all_data_base.at(name).reserved_rooms_;
        }
    private:
        map <string, BookInfo> all_data_base;
        int64_t time_ = 0;
};
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
            int client_id, room_count;
            int64_t time;
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
