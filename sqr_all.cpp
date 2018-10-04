#include <iostream>
#include <utility>
#include <map>
#include <vector>

using namespace std;

template <typename T1> T1 Sqr(T1 v);
template <typename T1, typename T2> pair<T1, T2> Sqr(const pair<T1, T2> p);
template <typename T> vector<T> Sqr(const vector <T> &v);
template <typename T1, typename T2> map<T1, T2> Sqr(const map<T1, T2> &m);

template <typename T1>
T1 Sqr(T1 v)
{
    return v * v;
}

template <typename T1, typename T2>
pair<T1, T2> Sqr(const pair<T1, T2> p)
{
    pair<T1, T2> result = p;
    result.first = Sqr(result.first);
    result.second = Sqr(result.second);
}

template <typename T>
vector<T> Sqr(const vector <T> &v)
{
    vector<T> result = v;

    for (T &i : result)
    {
        i = Sqr(i);
    }

    return result;
}

template <typename T1, typename T2>
map<T1, T2> Sqr(const map<T1, T2> &m)
{
    map<T1, T2> result = m;

    for (auto &i : result)
    {
        i.second = Sqr(i.second);
    }

    return result;
}

int main()
{
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v))
    {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs =
    {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs))
    {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}