#include "database.h"
#include <ostream>
#include <algorithm>

vector<BaseEntry> Database::makeEvents(function<bool(const Date &date, const string &event)> pred) const
{
    vector<BaseEntry> found;

    for (const auto i : _base)
    {
        const auto &date = i.first;
        const auto &events = i.second;

        for_each(events.begin(), events.end(),
                 [date, pred, &found](const string & event)
        {
            if (pred(date, event))
            {
                found.push_back(make_pair(date, event));
            }
        });
    }

    return found;
}

void Database::Add(const Date &date, const string &event)
{
    if (!_baseSet[date].count(event))
    {
        _base[date].push_back(event);
    }
}

size_t Database::RemoveIf(function<bool(const Date &date, const string &event)> pred)
{
    size_t deletedSize = 0;
    vector<Date> emptyKeys;

    for (auto &i : _base)
    {
        const auto &date = i.first;
        auto &events = i.second;
        auto it = stable_partition(events.begin(), events.end(),
        [date, pred](const string & event) { return !pred(date, event); });
        deletedSize += events.end() - it;

        for (auto it1 = it; it1 != events.end(); ++it1)
        {
            _baseSet[date].erase(*it1);
        }

        events.erase(it, events.end());

        if (events.empty())
        {
            emptyKeys.push_back(date);
        }
    }

    for (const auto &i : emptyKeys)
    {
        _base.erase(i);
    }

    return deletedSize;
}

vector<BaseEntry> Database::FindIf(function<bool(const Date &date, const string &event)> pred) const
{
    return makeEvents(pred);
}

void Database::Print(ostream &os) const
{
    vector<BaseEntry> events = makeEvents([](const Date &date, const string &event) { return true; });

    for_each(events.begin(), events.end(),
    [&os](const BaseEntry & entry) { os << entry.first << " " << entry.second << endl; });
}

BaseEntry Database::Last(const Date &date) const
{
    auto it = _base.upper_bound(date);

    if (it == _base.begin())
    {
        throw invalid_argument("Date is too low");
    }

    --it;
    return make_pair(it->first, *(it->second.end() - 1));
}

ostream &operator<<(ostream &os, const BaseEntry &entry)
{
    return os << entry.first << " " << entry.second;
}
