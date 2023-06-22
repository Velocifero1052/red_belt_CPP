//
// Created by comme on 6/23/2023.
//

#ifndef RED_BELT_C___STUDENT_H
#define RED_BELT_C___STUDENT_H

#include <map>
#include <string>

using namespace std;

struct Student {
    string first_name;
    string last_name;
    map<string, double> marks;
    double rating;

    bool operator < (const Student& other) const {
        return GetName() < other.GetName();
    }

    bool Less(const Student& other) const {
        return rating > other.rating;
    }

    string GetName() const {
        return first_name + " " + last_name;
    }
};

#endif
