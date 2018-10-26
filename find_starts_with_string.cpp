#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string &prefix)
{
    if (range_begin == range_end)
    {
        return make_pair(range_begin, range_end);
    }

    auto first = lower_bound(range_begin, range_end, prefix,
    [](const typename RandomIt::value_type & a, const typename RandomIt::value_type & b) { return b > a.substr(0, b.size()); });

    auto last = upper_bound(range_begin, range_end, prefix,
    [](const typename RandomIt::value_type & a, const typename RandomIt::value_type & b) { return a < b.substr(0, a.size()); });

    return make_pair(first, last);
}

int main()
{
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}