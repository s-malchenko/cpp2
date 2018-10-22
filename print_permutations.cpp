#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

ostream& operator<<(ostream &s, const vector<int> &v)
{
    for (const auto& i : v)
    {
        s << i << " ";
    }

    return s;
}

int main()
{
    unsigned n = 0;
    cin >> n;

    if (n > 9 || n == 0)
    {
        return 0;
    }

    vector<int> v;

    for (unsigned i = n; i > 0; --i)
    {
        v.push_back(i);
    }

    cout << v << endl;

    while (prev_permutation(v.begin(), v.end()))
    {
        cout << v << endl;
    }

    return 0;
}