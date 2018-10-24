#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    static const unsigned num = 2;

    if (range_end - range_begin < num)
    {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    RandomIt middle = elements.begin() + (elements.size() / num);
    MergeSort(elements.begin(), middle);
    MergeSort(middle, elements.end());
    merge(elements.begin(), middle, middle, elements.end(), range_begin);
}

int main()
{
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}