#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int main()
{
    unsigned n = 0;
    cin >> n;
    vector<int64_t> v(n);
    int64_t sum = 0;

    for (auto &i : v)
    {
        cin >> i;
        sum += i;
    }

    int64_t avg = 0;

    if (!v.empty())
    {
        avg = sum / static_cast<int64_t>(v.size());
    }

    vector<unsigned> days;

    for (unsigned i = 0; i < v.size(); ++i)
    {
        if (v[i] > avg)
        {
            days.push_back(i);
        }
    }

    cout << days.size() << endl;

    for (auto i : days)
    {
        cout << i << " ";
    }

    return 0;
}
