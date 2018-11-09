#include "database.h"
#include <ostream>

void Database::Add(const Date &date, const string &event)
{
    _base[date].push_back(event);
}

size_t Database::RemoveIf(function<bool(const Date &date, const string &event)> pred)
{
}

set<string> Database::FindIf(function<bool(const Date &date, const string &event)> pred) const
{
    return {};
}

void Database::Print(ostream &os) const
{
}

string Database::Last(const Date &date) const
{
    return {};
}
