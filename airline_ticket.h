//
// Created by Rakhmon Radjabov on 07/06/23.
//

#ifndef RED_BELT_C___AIRLINE_TICKET_H
#define RED_BELT_C___AIRLINE_TICKET_H
#include "test_runner.h"
#pragma once

#include <string>
#include <tuple>
#include <iomanip>

using namespace std;

struct Date {
    int year, month, day;
};

struct Time {
    int hours, minutes;
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

ostream& operator << (ostream& os, const Date& date) {
    os << setw(4) << setfill('0') << date.year << '-'
       << setw(2) << setfill('0') << date.month << '-'
       << setw(2) << setfill('0') << date.day;
    return os;
}

std::istream& operator>>(std::istream& stream, Date& date) {

    string string_buffer;
    stream >> string_buffer;
    stringstream ss(string_buffer);

    ss >> date.year;
    if ((char)ss.peek() != '-')
        throw std::domain_error("Wrong date format: " + string_buffer);
    ss.ignore(1);
    if(ss.eof()){
        throw std::domain_error("Wrong date format: " + string_buffer);
    }
    ss >> date.month;

    if ((char)ss.peek() != '-')
        throw std::domain_error("Wrong date format: " + string_buffer);

    ss.ignore(1);

    if(string_buffer.find('-', string_buffer.length() - 1) == string_buffer.length() - 1){
        throw std::domain_error("Wrong date format: " + string_buffer);
    }

    ss >> date.day;

    if(!ss.eof())
        throw std::domain_error("Wrong date format: " + string_buffer);

    auto new_date = Date{date.year, date.month, date.day};
    date = new_date;

    return stream;
}

std::istream& operator>>(std::istream& stream, Time& time) {
    int hours, minutes;
    stream >> hours;
    stream.ignore(1);
    stream >> minutes;
    time.hours = hours;
    time.minutes = minutes;
    return stream;
}

ostream& operator << (ostream& os, const Time& time) {
    os << setw(2) << setfill('0') << time.hours << ':'
       << setw(2) << setfill('0') << time.minutes;
    return os;
}

bool operator<(const Date& lhs, const Date rhs) {
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date rhs) {
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date rhs) {
    return tie(lhs.year, lhs.month, lhs.day) != tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator==(const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

bool operator!=(const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) != tie(rhs.hours, rhs.minutes);
}

#define UPDATE_FIELD(ticket, field, values) {                                                                                                    \
        auto it = values.find(#field);                                                                                                           \
        bool found = it != values.end();                                                                                                         \
        if (found) {                                                                                                                             \
            istringstream is(it->second);                                                                                                        \
            cout << it->second;                                                                                                 \
            is >> ticket.field;                                                                                                                     \
        }\
}


// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time


void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
            {"departure_date", "2018-2-28"},
            {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
            {"price", "12550"},
            {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}


#endif //RED_BELT_C___AIRLINE_TICKET_H
