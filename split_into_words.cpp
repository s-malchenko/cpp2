#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> SplitIntoWords(const string &s)
{
    auto it_begin = s.begin();
    auto it_end = it_begin;

    vector<string> result;

    while (it_begin != s.end())
    {
        it_end = find(it_begin, s.end(), ' ');

        if (it_begin != it_end)
        {
            result.push_back({it_begin, it_end});
        }

        if (it_end != s.end())
        {
            it_begin = it_end + 1;
        }
        else
        {
            break;
        }
    }

    return result;
}

int main()
{
    string s = "    C   Cpp   Java    Python     ";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it)
    {
        if (it != begin(words))
        {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
