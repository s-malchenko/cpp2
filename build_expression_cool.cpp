#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

struct operation_t
{
    string sign;
    int number;
};

istream& operator>>(istream &stream, operation_t &oper)
{
    stream >> oper.sign >> oper.number;
    return stream;
}

bool needBrackets(const string &prev, const string &next)
{
    return ((prev == "+" || prev == "-") && (next == "*" || next == "/"));
}

bool bracketsPredicate(const operation_t &op)
{
    static string prev("*");
    bool result = needBrackets(prev, op.sign);
    prev = op.sign;
    return result;
}

int main()
{
    int num, value = 0;
    cin >> value >> num;
    vector<operation_t> expression(num);

    for (auto &op : expression)
    {
        cin >> op;
    }

    size_t numOfBrackets = count_if(expression.begin(), expression.end(), bracketsPredicate);

    for (size_t i = 0; i < numOfBrackets; ++i)
    {
        cout << '(';
    }

    cout << value;

    for (const auto &op : expression)
    {
        static string prev("*");

        if (needBrackets(prev, op.sign))
        {
            cout << ")";
        }

        prev = op.sign;
        cout << " " << op.sign << ' ' << op.number;
    }
    return 0;
}