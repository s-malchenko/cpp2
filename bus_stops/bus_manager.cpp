#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops)
{
    buses_to_stops[bus] = stops;

    for (const string &stop : stops)
    {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const
{
    vector<string> result;

    try
    {
        result = stops_to_buses.at(stop);
    }
    catch (...) {}

    return {result};
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const
{
    vector<string> result;

    try
    {
        result = buses_to_stops.at(bus);
    }
    catch (...) {}

    return {bus, result, stops_to_buses};
}

AllBusesResponse BusManager::GetAllBuses() const
{
    return {buses_to_stops};
}
