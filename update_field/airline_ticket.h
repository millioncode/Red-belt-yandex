#pragma once

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
int ToInt(const string& s);
struct Date {
        int year, month, day;
        Date operator=(const string& s);
};
Date Date::operator=(const string& s) {
    auto it1 = find(s.begin(), s.end(), '-');
    auto it2 = find(++it1, s.end(), '-');
    string year (s.begin(), prev(it1));
    string month (it1, it2);
    string day (++it2, s.end());
    this->year = ToInt(year);
    this->month = ToInt(month);
    this->day = ToInt(day);
    return *this;
}
int ToInt(const string& s) {
    auto value = 0;
    for(const auto& a : s) {
        int number;
        switch (a) {
        case '0':
            number=0;
            break;
        case '1':
            number=1;
            break;
        case '2':
            number=2;
            break;
        case '3':
            number=3;
            break;
        case '4':
            number=4;
            break;
        case '5':
            number=5;
            break;
        case '6':
            number=6;
            break;
        case '7':
            number=7;
            break;
        case '8':
            number=8;
            break;
        case '9':
            number=9;
            break;
        default:
            break;
        }
        value = 10*value + number;
    }
    return value;
}
struct Time {
        int hours, minutes;
        Time operator=(const string& s);
};
Time Time::operator=(const string& s) {
    auto it1 = find(s.begin(), s.end(), ':');
    string hour (s.begin(), prev(it1));
    string min (++it1, s.end());
    this->hours = ToInt(hour);
    this->minutes = ToInt(min);
    return *this;
}
struct AirlineTicket {
        string from;
        string to;
        string airline;
        Date departure_date;
        Time departure_time;
        Date arrival_date;
        Time arrival_time;
        int price;
};


