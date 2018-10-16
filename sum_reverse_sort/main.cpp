#include "sum_reverse_sort.h"
#include <iostream>


ostream& operator<<(ostream &stream, const vector<int> &t)
{
    stream << "{";
    for (auto i : t)
    {
        stream << i << " ";
    }
    stream << "}";
}

int main()
{
    int a = 2000000;
    int b = 3;
    cout << a << " + " << b << " = " << Sum(a, b) << endl;
    string s("ghlsdflgjhjkfslkjghlkkjj34432klllljj");
    cout << "Reversed " << s << " is " << Reverse(s) << endl;
    vector<int> v = {0, 3, -1, 564, 999, 0};
    std::vector<int> v1 = v;
    Sort(v1);
    cout << "Sorted " << v << " is " << v1 << endl;
    return 0;
}