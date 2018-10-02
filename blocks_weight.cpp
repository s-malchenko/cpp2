#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    unsigned n = 0, density = 0;
    cin >> n >> density;
    uint64_t totalWeight = 0;

    for (unsigned i = 0; i < n; ++i)
    {
        uint64_t d = 0, weight = density;

        for (unsigned j = 0; j < 3; ++j)
        {
            cin >> d;
            weight *= d;
        }

        totalWeight += weight;
    }

    cout << totalWeight << endl;
    return 0;
}
