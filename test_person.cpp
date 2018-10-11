#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator << (ostream &os, const vector<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream &operator << (ostream &os, const set<T> &s)
{
    os << "{";
    bool first = true;
    for (const auto &x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream &operator << (ostream &os, const map<K, V> &m)
{
    os << "{";
    bool first = true;
    for (const auto &kv : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {})
{
    if (t != u)
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty())
        {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint)
{
    AssertEqual(b, true, hint);
}

class TestRunner
{
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name)
    {
        try
        {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception &e)
        {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...)
        {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

// class Person
// {
// public:
//     void ChangeFirstName(int year, const string &first_name)
//     {
//         history[year].firstName = first_name;
//     }

//     void ChangeLastName(int year, const string &last_name)
//     {

//         history[year].lastName = last_name;
//     }

//     string GetFullName(int year)
//     {
//         fullName validName;
//         string name;

//         // получить имя и фамилию по состоянию на конец года year
//         for (const auto &i : history)
//         {
//             if (i.first > year)
//             {
//                 break;
//             }

//             if (i.second.firstName.size())
//             {
//                 validName.firstName = i.second.firstName;
//             }

//             if (i.second.lastName.size())
//             {
//                 validName.lastName = i.second.lastName;
//             }
//         }

//         if (validName.firstName.empty() && validName.lastName.empty())
//         {
//             name = "Incognito";
//         }
//         else if (validName.firstName.empty())
//         {
//            name = validName.lastName + " with unknown first name";
//         }
//         else if (validName.lastName.empty())
//         {
//             name = validName.firstName + " with unknown last name";
//         }
//         else
//         {
//             name = validName.firstName + " " + validName.lastName;
//         }

//         return name;
//     }

// private:
//     struct fullName
//     {
//         string firstName = "";
//         string lastName = "";
//     };

//     map<int, fullName> history;
// };

void checkNameForYears(int firstYear, int lastYear, const string &name, Person &p)
{
    for (int i = firstYear; i <= lastYear; ++i)
    {
        AssertEqual(p.GetFullName(i), name);
    }
}

void TestIncognito()
{
    Person p;
    checkNameForYears(0, 2000, "Incognito", p);
    p.ChangeFirstName(1992, "Serega");
    checkNameForYears(0, 1991, "Incognito", p);
    p.ChangeLastName(1991, "Serega");
    checkNameForYears(0, 1990, "Incognito", p);
}

void TestFirstName1()
{
    Person p;
    p.ChangeFirstName(1000, "Serega");
    checkNameForYears(1000, 20000, "Serega with unknown last name", p);
    p.ChangeFirstName(500, "Serega1");
    checkNameForYears(500, 999, "Serega1 with unknown last name", p);
    p.ChangeFirstName(30000, "Serega4");
    checkNameForYears(1000, 29999, "Serega with unknown last name", p);
    checkNameForYears(30000, 40000, "Serega4 with unknown last name", p);
}

void TestFirstName2()
{
    Person p;
    p.ChangeLastName(1000, "Serega");
    checkNameForYears(1000, 2000, "Serega with unknown first name", p);
    p.ChangeFirstName(500, "Serega1");
    checkNameForYears(500, 999, "Serega1 with unknown last name", p);
    checkNameForYears(1000, 2000, "Serega1 Serega", p);
    p.ChangeFirstName(500, "Serega1");
    p.ChangeFirstName(1500, "Serega2");
    p.ChangeFirstName(2000, "Serega3");
    checkNameForYears(500, 999, "Serega1 with unknown last name", p);
    checkNameForYears(1000, 1499, "Serega1 Serega", p);
    checkNameForYears(1500, 1999, "Serega2 Serega", p);
    checkNameForYears(2000, 2500, "Serega3 Serega", p);
}

void TestLastName1()
{
    Person p;
    p.ChangeLastName(1000, "Serega");
    checkNameForYears(1000, 2000, "Serega with unknown first name", p);
    p.ChangeLastName(500, "Serega1");
    checkNameForYears(500, 999, "Serega1 with unknown first name", p);
    p.ChangeLastName(3000, "Serega4");
    checkNameForYears(1000, 2999, "Serega with unknown first name", p);
    checkNameForYears(3000, 31000, "Serega4 with unknown first name", p);
}

void TestLastName2()
{
    Person p;
    p.ChangeFirstName(1000, "Serega");
    checkNameForYears(1000, 2000, "Serega with unknown last name", p);
    p.ChangeLastName(500, "Serega1");
    checkNameForYears(500, 999, "Serega1 with unknown first name", p);
    checkNameForYears(1000, 2000, "Serega Serega1", p);
    p.ChangeLastName(500, "Serega1");
    p.ChangeLastName(1500, "Serega2");
    p.ChangeLastName(2000, "Serega3");
    checkNameForYears(500, 999, "Serega1 with unknown first name", p);
    checkNameForYears(1000, 1499, "Serega Serega1", p);
    checkNameForYears(1500, 1999, "Serega Serega2", p);
    checkNameForYears(2000, 2500, "Serega Serega3", p);
}

int main()
{
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestIncognito, "TestIncognito");
    runner.RunTest(TestFirstName1, "TestFirstName1");
    runner.RunTest(TestFirstName2, "TestFirstName2");
    runner.RunTest(TestLastName1, "TestLastName1");
    runner.RunTest(TestLastName2, "TestLastName2");
    return 0;
}
