#include <set>
#include <iterator>
#include <iostream>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int> &numbers, int border)
{
    auto it = numbers.lower_bound(border);

    if (it == numbers.begin())
    {
        return it;
    }
    else if (it == numbers.end())
    {
        return prev(it);
    }

    if (abs(*it - border) < abs(*prev(it) - border))
    {
        return it;
    }
    else
    {
        return prev(it);
    }
}

int main()
{
    set<int> numbers = {1, 4, 6};
    cout <<
         *FindNearestElement(numbers, 0) << " " <<
         *FindNearestElement(numbers, 3) << " " <<
         *FindNearestElement(numbers, 5) << " " <<
         *FindNearestElement(numbers, 6) << " " <<
         *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;

    set<int> number = {6};
    cout <<
         *FindNearestElement(number, 0) << " " <<
         *FindNearestElement(number, 3) << " " <<
         *FindNearestElement(number, 5) << " " <<
         *FindNearestElement(number, 6) << " " <<
         *FindNearestElement(number, 100) << endl;
    return 0;
}
