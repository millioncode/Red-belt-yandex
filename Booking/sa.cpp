#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <stdexcept>
#include <set>
#include <random>
#include <algorithm>
#include "profile.h"
#include "test_runner.h"
using namespace std;

class HotelManagerTelegram {
    public:
        HotelManagerTelegram() {}

        void Book(int64_t reserv_time, string hotel_name, int user_id, int room_count) {

            if (room_count != 0 || hotel_name != "") {
                reserv_stat.push({reserv_time, hotel_name, user_id, room_count});
                all_hotels_stat[hotel_name].users_stat[user_id]++;
                all_hotels_stat[hotel_name].rooms_stat += room_count;
            }
            while (86399 < (reserv_time - reserv_stat.front().reserv_time)) {
                try {
                    auto& it_hotel = all_hotels_stat.at(reserv_stat.front().hotel_name);
                    auto& it_user_stat = it_hotel.users_stat.at(reserv_stat.front().user_id);

                    it_user_stat--;

                    if (it_user_stat == 0) {
                        it_hotel.users_stat.erase(reserv_stat.front().user_id);
                    }

                    it_hotel.rooms_stat -= reserv_stat.front().room_count;
                    reserv_stat.pop();
                }
                catch (out_of_range& e) {};

            }

        }

        int Clients(string hotel_name) {
            int result = 0;
            try {
                result = all_hotels_stat.at(hotel_name).users_stat.size();
            }
            catch (out_of_range& e) {}

            return result;
        }

        int Rooms(string hotel_name) {
            int result = 0;

            try {
                result = all_hotels_stat.at(hotel_name).rooms_stat;
            }
            catch (out_of_range& e) {}

            return result;
        }

    private:
        struct reservation {
                int64_t reserv_time;
                string hotel_name;
                int user_id = 0;
                int room_count = 0;
        };

        struct hotel_stat {
                map<int, int> users_stat;
                int rooms_stat = 0;
        };

        queue<reservation> reserv_stat;
        map<string, hotel_stat> all_hotels_stat;
};

//точно не: QR(LOGQ+LOGL), QL(T+LogQ), Q(W+L*Log(Q))
//попробовать Q(LLogQ), Q(LLogQ) + C, Q(LLogQ) + W,
class HotelManagerCoursera {
    public:
        void Book(int64_t time, const string& hotel_name, //Q (LLogQ) + L*Log(Q)
                  int client_id, int room_count) {
            current_time_ = time;
            hotels_[hotel_name].Book({time, client_id, room_count}); //L*Log(Q)
        }
        int Clients(const string& hotel_name) {
            return hotels_[hotel_name].ComputeClientCount(current_time_); //L*Log(Q) + QLogQ
        }
        int Rooms(const string& hotel_name) {
            return hotels_[hotel_name].ComputeRoomCount(current_time_);//L*Log(Q) + + QLogQ
        }

    private:
        struct Booking {
                int64_t time;
                int client_id;
                int room_count;
        };

        class HotelInfo {
            public:
                void Book(const Booking& booking) { //LogQ
                    last_bookings_.push(booking); //O1
                    room_count_ += booking.room_count; //O1
                    ++client_booking_counts_[booking.client_id]; //LogQ = 9
                }
                int ComputeClientCount(int64_t current_time) {
                    RemoveOldBookings(current_time); //O(Q)
                    return client_booking_counts_.size();  //O1
                }
                int ComputeRoomCount(int64_t current_time) {
                    RemoveOldBookings(current_time); //O(Q)
                    return room_count_; //O1
                }
            private:
                static const int TIME_WINDOW_SIZE = 86400;
                queue<Booking> last_bookings_;
                int room_count_ = 0;
                map<int, int> client_booking_counts_;

                void PopBooking() {
                    const Booking& booking = last_bookings_.front(); //O(1)
                    room_count_ -= booking.room_count;   //O(1)
                    const auto client_stat_it =
                            client_booking_counts_.find(booking.client_id);   //O(Log(C))
                    if (--client_stat_it->second == 0) {
                        client_booking_counts_.erase(client_stat_it);  //O(1)
                    }
                    last_bookings_.pop();  //O(1)
                }
                void RemoveOldBookings(int64_t current_time) { //O(Q)
                    while (
                           !last_bookings_.empty() //O(1)
                           && last_bookings_.front().time <= current_time - TIME_WINDOW_SIZE
                           ) {
                        PopBooking(); //O(Log(Q))
                    }
                }
        };

        int64_t current_time_ = 0;
        map<string, HotelInfo> hotels_;
};
/*
void TimeTest(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t Q = 100000;
    int64_t t1 = -1000000000000000000;
    int64_t t2 = 1000000000000000000;
            std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int64_t> random_time(t1, t2);
    std::uniform_int_distribution<ulong> random_id(1, 1000'000'000);
    std::uniform_int_distribution<ulong> random_room(1, 1000);

    std::uniform_int_distribution<size_t> random_query_index(0, Q - 1);

    vector<int64_t> v_time;
    vector<string> v_hotel = {"a", "abcdye", "jhbdsfvkb", "dnlkenrkj", "a","b",
                              "b", "kjnfvjnl", "jn;kelr", "a", "cccc", "xxxx", "csc", "xxxx"};
    std::uniform_int_distribution<size_t> random_query_index_hotel(0, v_hotel.size() - 1);
    vector<ulong> v_id;
    vector<ulong> v_room;
    vector<ulong> v_index_hotel;
    vector<size_t> v_query_index;

    for(size_t i = 0; i < Q; i++){
        v_time.push_back(random_time(gen));
        v_id.push_back(random_id(gen));
        v_room.push_back(random_room(gen));
        v_index_hotel.push_back(random_query_index_hotel(gen));
        v_query_index.push_back(random_query_index(gen));
    }
    sort(v_time.begin(), v_time.end());
    for(auto& i: v_time)
        cout << i << " ";
    cout << endl;
    //  cout <<" v_time.size()=" << v_time.size() << endl;
    //  cout <<" v_id.size()=" << v_id.size() << endl;
    //  cout <<" v_hotel.size()=" << v_hotel.size() << endl;
    //  cout <<" v_room.size()=" << v_room.size() << endl;
    //  cout <<" v_index_hotel.size()=" << v_index_hotel.size() << endl;

    LOG_DURATION("Booker");
    HotelManagerCoursera booker;
    for(size_t i = 0; i < double(2 * Q) / 3; ++i){
        booker.Book(v_time.at(v_query_index.at(i)), v_hotel.at(v_index_hotel.at(i)),
                    v_id.at(v_query_index.at(i)), v_room.at(v_query_index.at(i)));
    }
    for(size_t i = 0; i < double(Q)/ 6; ++i){
        cout << booker.Rooms(v_hotel.at(v_index_hotel.at(i))) << " ";
    }
    cout << "\n";
    for(size_t i = 0; i < double(Q) / 6; ++i){
        cout << booker.Clients(v_hotel.at(v_index_hotel.at(i))) << " ";
    }
    cout << "\n";
}

*/


int main()
{
    TestRunner tr;
    //RUN_TEST(tr, TimeTest); // 202ms

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    HotelManagerTelegram manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t reserv_time;
            string hotel_name;
            int user_id, room_count;
            cin >> reserv_time >> hotel_name >> user_id >> room_count;
            manager.Book(reserv_time, hotel_name, user_id, room_count);
        }
        else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << endl;
        }
        else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << endl;
        }
    }
    return 0;
}
