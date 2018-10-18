#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
    auto found = find_if(numbers.begin(), numbers.end(), [](const auto &i) { return i < 0; });

    for (auto it = found; it != numbers.begin(); it--)
    {
        cout << *(it - 1) << " ";
    }

    cout << endl;
}

int main()
{
    PrintVectorPart({6, 1, 8, -5, 4});
    PrintVectorPart({ -6, 1, 8, -5, 4}); // ничего не выведется
    PrintVectorPart({6, 1, 8, 5, 4});
    return 0;
}