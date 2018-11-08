#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>

using namespace std;





void proceedCommand(const string &cmd, Database &db)
{
    if (cmd.empty())
    {
        return;
    }

    stringstream ss(cmd);
    string command, dateStr, event;
    Date d;

    ss >> command;

    if (command == "Add")
    {  
        ss >> dateStr >> event;
        d = Date(dateStr);
        db.AddEvent(d, event);
    }
    else if (command == "Del")
    {
        ss >> dateStr;
        d = Date(dateStr);
        if (!(ss >> event))
        {
            cout << "Deleted " << db.DeleteDate(d) << " events" << endl;
        }
        else
        {
            if (db.DeleteEvent(d, event))
            {
                cout << "Deleted successfully\n";
            }
            else
            {
                cout << "Event not found\n";
            }
        }
    }
    else if (command == "Find")
    {   
        ss >> dateStr;
        d = Date(dateStr);
        set<string> events = db.Find(d);

        for (auto i : events)
        {
            cout << i << endl;
        }
    }
    else if (command == "Print")
    {
        db.Print();
    }
    else
    {
        throw invalid_argument("Unknown command: " + command);
    }
}

int main()
{
    Database db;

    string command;
    while (getline(cin, command))
    {
        // Считайте команды с потока ввода и обработайте каждую
        try
        {
            proceedCommand(command, db);
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
            break;
        }
    }

    return 0;
}