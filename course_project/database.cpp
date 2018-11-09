#include "database.h"
#include <ostream>

void Database::Add(const Date &date, const string &event)
{
}

int Database::RemoveIf(function<bool(const Date& date, const string& even)> pred)
{
    return 1;
}

set<string> Database::FindIf(function<bool(const Date& date, const string& even)> pred) const
{
    return {};
}

void Database::Print(ostream &os) const
{
}

string Database::Last(const Date& date) const
{
    return {};
}
