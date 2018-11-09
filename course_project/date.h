#pragma once

#include <string>
#include <ostream>

using namespace std;

class Date
{
public:
    Date();
    Date(const string &str);
    Date(int year, int month, int day);
    Date(istream &is);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
private:
    int _year;
    int _month;
    int _day;
    void checkFormat(bool arg, const string& str);
    void setDate(int year, int month, int day);
    void setDate(const string &str);
};

bool operator<(const Date &lhs, const Date &rhs);
bool operator==(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);
ostream &operator<<(ostream &stream, const Date &date);
Date ParseDate(istream &is);
