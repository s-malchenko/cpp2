#include "database.h"
#include <iostream>

void Database::AddEvent(const Date &date, const string &event)
{
    base[date].insert(event);
}

bool Database::DeleteEvent(const Date &date, const string &event)
{
    try
    {
        if (base.at(date).count(event))
        {
            base[date].erase(event);

            if (base[date].empty())
            {
                base.erase(date);
            }

            return true;
        }
    }
    catch (...) {}

    return false;
}
int Database::DeleteDate(const Date &date)
{
    size_t n = 0;

    try
    {
        n = base.at(date).size();
        base.erase(date);
    }
    catch (...) {}

    return n;
}

set<string> Database::Find(const Date &date) const
{
    try
    {
        return base.at(date);
    }
    catch (...) {}

    return {};
}

void Database::Print() const
{
    for (auto date : base)
    {
        for (auto i : date.second)
        {
            cout << date.first << " " << i << endl;
        }
    }
}
