#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query
{
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator >> (istream &is, Query &q)
{
    // Реализуйте эту функцию
    string operation_code;
    is >> operation_code;

    if (operation_code == "NEW_BUS")
    {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        vector<string> &stops = q.stops;
        stops.resize(stop_count);

        for (string &stop : stops)
        {
            is >> stop;
        }
    }
    else if (operation_code == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS")
    {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (operation_code == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse
{
    // Наполните полями эту структуру
    vector<string> buses;
};

ostream &operator << (ostream &os, const BusesForStopResponse &r)
{
    // Реализуйте эту функцию
    if (r.buses.size() == 0)
    {
        os << "No stop" << endl;
    }
    else
    {
        for (const string &bus : r.buses)
        {
            os << bus << " ";
        }
        os << endl;
    }
    return os;
}

struct StopsForBusResponse
{
    // Наполните полями эту структуру
    string bus;
    vector<string> stops;
    map<string, vector<string>> stops_to_buses;
};

ostream &operator << (ostream &os, const StopsForBusResponse &r)
{
    // Реализуйте эту функцию
    if (r.stops.size() == 0)
    {
        os << "No bus" << endl;
    }
    else
    {
        for (const string &stop : r.stops)
        {
            cout << "Stop " << stop << ": ";
            if (r.stops_to_buses.at(stop).size() == 1)
            {
                cout << "no interchange";
            }
            else
            {
                for (const string &other_bus : r.stops_to_buses.at(stop))
                {
                    if (r.bus != other_bus)
                    {
                        cout << other_bus << " ";
                    }
                }
            }
            cout << endl;
        }
    }
    return os;
}

struct AllBusesResponse
{
    // Наполните полями эту структуру
    map<string, vector<string>> buses_to_stops;
};

ostream &operator << (ostream &os, const AllBusesResponse &r)
{
    // Реализуйте эту функцию
    if (r.buses_to_stops.empty())
    {
        os << "No buses" << endl;
    }
    else
    {
        for (const auto &bus_item : r.buses_to_stops)
        {
            os << "Bus " << bus_item.first << ": ";
            for (const string &stop : bus_item.second)
            {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}

class BusManager
{
public:
    void AddBus(const string &bus, const vector<string> &stops)
    {
        // Реализуйте этот метод
        buses_to_stops[bus] = stops;

        for (const string &stop : stops)
        {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const
    {
        // Реализуйте этот метод
        vector<string> result;

        try
        {
            result = stops_to_buses.at(stop);
        }
        catch (...) {}

        return {result};
    }

    StopsForBusResponse GetStopsForBus(const string &bus) const
    {
        // Реализуйте этот метод
        vector<string> result;

        try
        {
            result = buses_to_stops.at(bus);
        }
        catch (...) {}

        return {bus, result, stops_to_buses};
    }

    AllBusesResponse GetAllBuses() const
    {
        // Реализуйте этот метод
        return {buses_to_stops};
    }
private:
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main()
{
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i)
    {
        cin >> q;
        switch (q.type)
        {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
