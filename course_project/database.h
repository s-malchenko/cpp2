#pragma once

#include "date.h"
#include <string>
#include <set>
#include <map>
#include <functional>

using namespace std;

class Database
{
public:
    void Add(const Date &date, const string &event);
    int RemoveIf(function<bool(const Date& date, const string& even)> pred);
    set<string> FindIf(function<bool(const Date& date, const string& even)> pred) const;
    void Print(ostream &os) const;
    string Last(const Date& date) const;
private:
    map<Date, set<string>>base;
};
