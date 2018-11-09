#include "date.h"
#include <exception>
#include <iomanip>

Date::Date()
{
    setDate(1, 1, 1);
}
Date::Date(const string &str)
{
    stringstream ss(str.c_str());
    setDate(ss);
}
Date::Date(int year, int month, int day)
{
    setDate(year, month, day);
}
Date::Date(istream &is)
{
    setDate(is);
}
int Date::GetYear() const { return _year; }
int Date::GetMonth() const { return _month; }
int Date::GetDay() const { return _day; }

void Date::checkFormat(bool arg, const string &str)
{
    if (!arg)
    {
        throw invalid_argument("Wrong date format: " + str);
    }
}

void Date::setDate(int year, int month, int day)
{
    if (month < 1 || month > 12)
    {
        throw invalid_argument("Month value is invalid: " + to_string(month));
    }

    if (day < 1 || day > 31)
    {
        throw invalid_argument("Day value is invalid: " + to_string(day));
    }

    _year = year;
    _month = month;
    _day = day;
}

void Date::setDate(istream &is)
{
    int year, month, day;
    char c;
    checkFormat(bool(ss >> year), str);
    checkFormat(bool(ss >> c), str);
    checkFormat(c == '-', str);
    checkFormat(bool(ss >> month), str);
    checkFormat(bool(ss >> c), str);
    checkFormat(c == '-', str);
    checkFormat(bool(ss >> day), str);
    checkFormat(!(ss >> c), str);
    setDate(year, month, day);
}

bool operator<(const Date &lhs, const Date &rhs)
{
    if (lhs.GetYear() < rhs.GetYear())
    {
        return true;
    }
    else if (lhs.GetYear() > rhs.GetYear())
    {
        return false;
    }

    if (lhs.GetMonth() < rhs.GetMonth())
    {
        return true;
    }
    else if (lhs.GetMonth() > rhs.GetMonth())
    {
        return false;
    }

    if (lhs.GetDay() < rhs.GetDay())
    {
        return true;
    }

    return false;
}

ostream &operator<<(ostream &stream, const Date &date)
{
    stream << setfill('0') << setw(4) << date.GetYear() << "-"
           << setw(2) << date.GetMonth() << "-" << setw(2) << date.GetDay();
    return stream;
}

Date ParseDate(istream &is)
{
    return {is};
}
