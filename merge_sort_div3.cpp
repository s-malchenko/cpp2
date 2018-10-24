#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    static const unsigned num = 3;

    if (range_end - range_begin < num)
    {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    RandomIt middle1 = elements.begin() + (elements.size() / num);
    RandomIt middle2 = middle1 + (elements.size() / num);
    MergeSort(elements.begin(), middle1);
    MergeSort(middle1, middle2);
    MergeSort(middle2, elements.end());
    vector<typename RandomIt::value_type> tmp;
    merge(elements.begin(), middle1, middle1, middle2, back_inserter(tmp));
    merge(tmp.begin(), tmp.end(), middle2, elements.end(), range_begin);
}

int main()
{
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}