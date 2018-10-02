#include <iostream>
#include <cstdint>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

// enum class Lang
// {
//     DE, FR, IT
// };

// struct Region
// {
//     string std_name;
//     string parent_std_name;
//     map<Lang, string> names;
//     int64_t population;
// };

tuple<string, string, map<Lang, string>, int64_t> tieRegion(const Region &region)
{
    return make_tuple(region.std_name, region.parent_std_name, region.names, region.population);
}

bool operator<(const Region &lhs, const Region &rhs)
{
    return tieRegion(lhs) < tieRegion(rhs);
}

int FindMaxRepetitionCount(const vector<Region> &regions)
{
    int n = 0;
    map<Region, int> count;

    for (const auto &i : regions)
    {
        ++count[i];
    }

    for (const auto &i : count)
    {
        if (i.second > n)
        {
            n = i.second;
        }
    }

    return n;
}

// int main()
// {
//     cout << FindMaxRepetitionCount(
//     {
//         {
//             "Moscow",
//             "Russia",
//             {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//             89
//         }, {
//             "Russia",
//             "Eurasia",
//             {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//             89
//         }, {
//             "Moscow",
//             "Russia",
//             {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//             89
//         }, {
//             "Moscow",
//             "Russia",
//             {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//             89
//         }, {
//             "Russia",
//             "Eurasia",
//             {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//             89
//         },
//     }) << endl;

//     cout << FindMaxRepetitionCount(
//     {
//         {
//             "Moscow",
//             "Russia",
//             {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//             89
//         }, {
//             "Russia",
//             "Eurasia",
//             {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//             89
//         }, {
//             "Moscow",
//             "Russia",
//             {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
//             89
//         }, {
//             "Moscow",
//             "Toulouse",
//             {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//             89
//         }, {
//             "Moscow",
//             "Russia",
//             {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//             31
//         },
//     }) << endl;

//     return 0;
// }
