#include <vector>
#include <string>
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

int main()
{
    int num, value = 0;
    cin >> value >> num;
    vector<operation_t> expression(num);

    for (auto &op : expression)
    {
        cin >> op;
    }

    for (int i = 0; i < expression.size(); ++i)
    {
        cout << '(';
    }

    cout << value;

    for (const auto &op : expression)
    {
        cout << ") " << op.sign << ' ' << op.number;
    }
    return 0;
}