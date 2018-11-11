#pragma once

#include "date.h"
#include <string>
#include <set>
#include <map>
#include <functional>
#include <vector>
#include <utility>

using namespace std;
using BaseEntry = pair<Date, string>;

class Database
{
public:
    void Add(const Date &date, const string &event);
    size_t RemoveIf(function<bool(const Date &date, const string &even)> pred);
    vector<BaseEntry> FindIf(function<bool(const Date &date, const string &even)> pred) const;
    void Print(ostream &os) const;
    BaseEntry Last(const Date &date) const;
private:
    map<Date, vector<string>> _base;
    map<Date, set<string>> _baseSet;
    vector<BaseEntry> makeEvents(function<bool(const Date &date, const string &event)> pred) const;
};

ostream &operator<<(ostream &os, const BaseEntry &entry);
