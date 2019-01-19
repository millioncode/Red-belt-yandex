#include <iostream>
#include <string>
#include <deque>
#include <set>
#include <map>
#include <test_runner.h>
using namespace std;
long long time_ = 0;
int id = 0;
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
class Hotel {
    public:
        Hotel(const string& name): name_(name),id_hotel(id), reserved_rooms_(0), last_clients_(0)
        {}
        void Add(const long long& time, const int& client_id,
                 const int& room_count) {
            time_ = time;
            if (clients_rooms_time_.count(client_id) == 0 ) {
                last_clients_++;
            }
            clients_rooms_time_[client_id].push_back(rooms_time(time, room_count));
            reserved_rooms_ += room_count;
        }
        void Update_clients() {
            for(auto& i:clients_rooms_time_) {
                for(auto& j : i.second) {
                    if (time_ - j.time >= day_sec ) {
                        reserved_rooms_ -= j.rooms_count;
                        i.second.pop_front();
                    }
                    else break;
                    if (i.second.empty() ) {
                        --last_clients_;
                        clients_rooms_time_.erase(i.first);
                    }
                }
            }
        }
        int GetRooms() {
            Update_clients();
            return reserved_rooms_;
        }
        int GetClients() {
            Update_clients();
            return last_clients_;
        }
        string GetName() const {
            return name_;
        }
        int GetId() const {
            return id_hotel;
        }
    private:
        static const int day_sec = 86400;
        const string name_;
        const int id_hotel;
        map <int, deque<rooms_time>> clients_rooms_time_;

        int reserved_rooms_;
        int last_clients_;
};
struct Hotels {
        vector < Hotel > hotels;
        map <string, int> name_id_;
        void BOOK(const long long& time, const string& name, const int& client_id, const int& room_count) {
            int value;
            if (name_id_.count(name) > 0 ) {
                value = name_id_[name];
            } else {
                name_id_[name] = ++id;
                hotels.push_back(Hotel(name));
                value = id;
            }
            hotels[value].Add(time, client_id, room_count);
        }
        int CLIENTS(const string& hotel_name) {
            if (name_id_.count(hotel_name) >0 ) {
                int value;
                value = name_id_.at(hotel_name);
                return hotels.at(value).GetClients();
            } else return 0;
        }
        int ROOMS(const string& hotel_name) {
            if (name_id_.count(hotel_name) >0 ) {
                int value;
                value = name_id_.at(hotel_name);
                return hotels.at(value).GetRooms();
            } else return 0;
        }
};
//BOOK time hotel_name client_id room_count
bool operator < (const Hotel& a, const Hotel& b) {
    return a.GetName() < b.GetName();
}
void Test() {
    Hotels hotels;
    ASSERT_EQUAL(hotels.CLIENTS("Marriott"), 0);
    ASSERT_EQUAL(hotels.ROOMS("Marriott"), 0);
    // валится на следующей команде - предполоительно не проходит предпоследнюю
    // функцию в Hotel::Add
    hotels.BOOK(10, "FourSeasons", 1, 2);
    ASSERT_EQUAL(hotels.CLIENTS("FourSeasons"), 1);
    ASSERT_EQUAL(hotels.ROOMS("FourSeasons"), 2);

  /* Следующие тесты проходит
    Hotel Marriott("Marriott");
    ASSERT_EQUAL(Marriott.GetClients(), 0);
    ASSERT_EQUAL(Marriott.GetRooms(), 0);
    Hotel FourSeasons("FourSeasons");
    FourSeasons.Add(10, 1, 2);
    ASSERT_EQUAL(FourSeasons.GetClients(), 1);
    ASSERT_EQUAL(FourSeasons.GetRooms(), 2);
    Marriott.Add(10, 1, 1);
    FourSeasons.Add(86409, 2, 1);
    ASSERT_EQUAL(FourSeasons.GetClients(), 2);
    ASSERT_EQUAL(FourSeasons.GetRooms(), 3);
    ASSERT_EQUAL(Marriott.GetClients(), 1);
    Marriott.Add(86410, 2, 10);
    ASSERT_EQUAL(FourSeasons.GetClients(), 1);
    ASSERT_EQUAL(FourSeasons.GetRooms(), 1);
    ASSERT_EQUAL(Marriott.GetRooms(), 10);
*/
    cout << "OK"<< endl;

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
