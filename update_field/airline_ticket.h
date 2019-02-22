#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
using namespace std;

struct Date {
        int year, month, day;
        Date& operator=(const string& s);
};

struct Time {
        int hours, minutes;
        Time operator=(const string& s);

};

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

Date& Date::operator=(const string& s) {
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
bool operator ==(const Date& a, const Date& b) {
    return tie(a.year, a.month, a.day) == tie(b.year, b.month, b.day);
}

Time Time::operator=(const string& s) {
    auto it1 = find(s.begin(), s.end(), ':');
    string hour (s.begin(), it1);
    string min (++it1, s.end());
    this->hours = ToInt(hour);
    this->minutes = ToInt(min);
    return *this;
}
bool operator ==(const Time& a, const Time& b) {
    return tie(a.hours, a.minutes) == tie(b.hours, b.minutes);
}

ostream& operator<<(ostream& os, const Date& d) {
  return os << d.year << '-' << d.month << '-' << d.day;
}
ostream& operator<<(ostream& os, const Time& t) {
  return os << t.hours << ':' << t.minutes;
}

istream& operator >> (istream& is, Date& d) {
    string s;
    is >> s;
    d=s;
    return is;
}
istream& operator >> (istream& is, Time& d) {
    string s;
    is >> s;
    d=s;
    return is;
}
