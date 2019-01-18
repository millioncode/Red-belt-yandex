#include <iostream>
#include <string>
#include <deque>
#include <set>
#include <test_runner.h>
using namespace std;
long long time_ =0;
class abc_time {
    public:
        abc_time(const long long& t): time(t) {}
        long long time;
};
class clients_time: public abc_time {
    public:
        explicit clients_time(const long long& t, const int& i ): abc_time(t), id(i) {}
        int id;
};
class rooms_time: public abc_time {
    public:
        explicit rooms_time(const long long& t, const int& r) : abc_time(t), room(r) {}
        int room;
};

class Hotel {
    public:
        Hotel(const string& name): name_(name), reserved_rooms_(0), last_clients_(0) {}
        void Add(const long long& time, const int& client_id,
                 const int& room_count) {
            time_ = time;
            // придумать как избавиться от цикла
            /*for(int i=0; i<room_count; i++) {
                rooms_.push_back(rooms_time(time_, 1));
            }*/
            rooms_.push_back(rooms_time(time_, room_count));

            reserved_rooms_ += room_count;

            // удалить из очереди комнат неактуальные
            // обновить данные по комнатам за сутки
            Update_rooms();


            clients_.push_back(clients_time(time_, client_id));
            // удалить неактуальных клиентов
            // оюновить данные по клиентам за сутки
            // проблема с уник клиентами
            /*if (uniq_clients_.lower_bound(client_id)==uniq_clients_.end()) {
                uniq_clients_.insert(client_id);
            }*/
            Update_clients();
            //last_clients_ = uniq_clients_.size();

        }
        void Update_rooms() {
            for(auto& i : rooms_) {
                // если время идет по нарастанию, то получается нет смысла всю очередь проверять
                if (time_ - i.time >= day_sec ) {
                    reserved_rooms_ -= i.room;
                    rooms_.pop_front();
                }
                else break;
            }
            //reserved_rooms_ = rooms_.size();
        }
        void Update_clients() {
            for(auto& i:clients_) {
                if (time_ - i.time >= day_sec ) {
                    //int name = i.id;
                    clients_.pop_front();

                    //uniq_clients_.erase(name);
                    /*if (uniq_clients_.lower_bound(name)==uniq_clients_.end()) {
                        last_clients_--;
                    }*/
                }
                else break;
            }
            uniq_clients_.clear();
            for(auto& x : clients_) {
                uniq_clients_.insert(x.id);
            }
            last_clients_ = uniq_clients_.size();
        }
        int GetRooms() const {
            return reserved_rooms_;
        }
        int GetClients() const {
            return last_clients_;
        }
    private:
        static const int day_sec = 86400;
        const string name_;

        deque <clients_time> clients_;
        deque <rooms_time> rooms_;
        set<int> uniq_clients_;

        int reserved_rooms_;
        int last_clients_;
        //long long time_;
};
void Test() {
    Hotel Marriott("Marriott");
    /*Marriott.Add(10, 1, 1);
    ASSERT_EQUAL(Marriott.GetClients(), 1);
    ASSERT_EQUAL(Marriott.GetRooms(), 1);
    Marriott.Add(20, 2, 2);
    ASSERT_EQUAL(Marriott.GetClients(), 2);
    ASSERT_EQUAL(Marriott.GetRooms(), 3);
    Marriott.Add(86415, 2, 1);
    ASSERT_EQUAL(Marriott.GetClients(), 1);
    ASSERT_EQUAL(Marriott.GetRooms(), 3);
    cout << "OK" << endl;*/
    //ASSERT_EQUAL(Marriott.GetClients(), 0);
    //ASSERT_EQUAL(Marriott.GetRooms(), 0);
    Hotel FourSeasons("FourSeasons");
    FourSeasons.Add(10, 1, 2);
    ASSERT_EQUAL(FourSeasons.GetClients(), 1);
    ASSERT_EQUAL(FourSeasons.GetRooms(), 2);
    //Marriott.Add(10, 1, 1);
    FourSeasons.Add(86409, 2, 1);
    ASSERT_EQUAL(FourSeasons.GetClients(), 2);
    ASSERT_EQUAL(FourSeasons.GetRooms(), 3);
    //ASSERT_EQUAL(Marriott.GetClients(), 1);
    Marriott.Add(86410, 2, 10);
    ASSERT_EQUAL(FourSeasons.GetClients(), 1);
    ASSERT_EQUAL(FourSeasons.GetRooms(), 1);
    //ASSERT_EQUAL(Marriott.GetRooms(), 10);
};
int main()
{
    Test();
    return 0;
}
