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

// long long nod(long long a, long long b)
// {
//     a = abs(a);
//     b = abs(b);

//     while (a > 0 && b > 0)
//     {
//         if (a > b)
//         {
//             a %= b;
//         }
//         else
//         {
//             b %= a;
//         }
//     }

//     return a + b;
// }

// class Rational
// {
// public:
//     Rational()
//     {
//         num = 0;
//         den = 1;
//     }

//     Rational(int numerator, int denominator)
//     {
//         num = numerator;
//         den = denominator;
//         reduce();
//     }

//     int Numerator() const
//     {
//         return num;
//     }

//     int Denominator() const
//     {
//         return den;
//     }

// private:
//     int num;
//     int den;

//     void reduce()
//     {
//         if (num == 0)
//         {
//             den = 1;
//             return;
//         }

//         int div = nod(num, den);

//         num /= div;
//         den /= div;

//         if ((num < 0) != (den < 0))
//         {
//             num = -abs(num);
//             den = abs(den);
//         }
//         else
//         {
//             num = abs(num);
//             den = abs(den);
//         }
//     }
// };

void AssertRational(int num, int den, const Rational &r)
{
    AssertEqual(r.Numerator(), num);
    AssertEqual(r.Denominator(), den);
}

void TestDefaultConstructor()
{
    Rational r;
    AssertRational(0, 1, r);
}

void TestReducingPositive()
{
    Rational r(2, 4);
    AssertRational(1, 2, r);
    r = Rational(105, 15);
    AssertRational(7, 1, r);
    r = Rational(2000000, 4000000);
    AssertRational(1, 2, r);
    r = Rational(997, 677);
    AssertRational(997, 677, r);
}

void TestReducingNegative()
{
    Rational r(-2, 4);
    AssertRational(-1, 2, r);
    r = Rational(105, -15);
    AssertRational(-7, 1, r);
    r = Rational(-2000000, -4000000);
    AssertRational(1, 2, r);
    r = Rational(997, -677);
    AssertRational(-997, 677, r);
    r = Rational(-677, 997);
    AssertRational(-677, 997, r);
}

void TestZero()
{
    Rational r(0, 3);
    AssertRational(0, 1, r);
    r = Rational(0, -56);
    AssertRational(0, 1, r);
    r = Rational(0, 4000000);
    AssertRational(0, 1, r);
}

int main()
{
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
    runner.RunTest(TestReducingPositive, "TestReducingPositive");
    runner.RunTest(TestReducingNegative, "TestReducingNegative");
    runner.RunTest(TestZero, "TestZero");
    return 0;
}
