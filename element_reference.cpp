#include <iostream>
#include <map>
#include <exception>

using namespace std;

template <typename K, typename V>
V &GetRefStrict(map<K, V> &m, K key)
{
    try
    {
        return m.at(key);
    }
    catch (...)
    {
        throw runtime_error("No element");
    }
}

int main()
{
    map<int, string> m = {{0, "value"}};
    string &item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
}