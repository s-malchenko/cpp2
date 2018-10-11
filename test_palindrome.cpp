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

// bool IsPalindrom(const string &str)
// {
//     // Вы можете вставлять сюда различные реализации функции,
//     // чтобы проверить, что ваши тесты пропускают корректный код
//     // и ловят некорректный
    
//     if (str.empty())
//     {
//         return true;
//     }

//     for (size_t i = 0; i < str.size() / 2; ++i)
//     {
//         if (str[i] != str[str.size() - i - 1])
//         {
//             return false;
//         }
//     }

//     return true;
// }

void testString(const string& str, bool palindrome)
{
    AssertEqual(IsPalindrom(str), palindrome, str);
}

void TestPalindrome()
{
    testString("", true);
    testString(" ", true);
    testString("3", true);
    testString("  ", true);
    testString("   ", true);
    testString("madam", true);
    testString("level", true);
    testString("wasitacaroracatisaw", true);
    testString("\t\nwasitacaroracatisaw\n\t", true);
    testString("\t\nwasitacar\no\nracatisaw\n\t", true);
    testString(" wasitacaroracatisaw ", true);
    testString("wasita carorac atisaw", true);

    testString("fe", false);
    testString("fefef\nef", false);
    testString("fefef\tef", false);
    testString("\nwasitacaroracatisaw", false);
    testString("nwasitacaroracatisaw\n", false);
    testString("nwasitacaroracatisaw\t", false);
    testString("\nnwasitacaroracatisaw", false);
    testString("was itac arora catisaw", false);
    testString("wasitaca6oracatisaw", false);
    testString("wasitacaroracatisaw ", false);
    testString("wasitacaroracatisa5", false);
    testString(" wasitacaroracatisaw", false);
    testString("Wasitacaroracatisaw", false);
}

int main()
{
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestPalindrome, "TestPalindrome");
    return 0;
}
