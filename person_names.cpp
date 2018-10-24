#include <string>
#include <map>
#include <iostream>

using namespace std;

class Person
{
public:
    void ChangeFirstName(int year, const string &first_name)
    {
        firstNames[year] = first_name;
    }

    void ChangeLastName(int year, const string &last_name)
    {

        lastNames[year] = last_name;
    }

    string GetFullName(int year)
    {
        string name, firstName, lastName;

        firstName = nameForYear(firstNames, year);
        lastName = nameForYear(lastNames, year);

        if (firstName.empty() && lastName.empty())
        {
            name = "Incognito";
        }
        else if (firstName.empty())
        {
            name = lastName + " with unknown first name";
        }
        else if (lastName.empty())
        {
            name = firstName + " with unknown last name";
        }
        else
        {
            name = firstName + " " + lastName;
        }

        return name;
    }

private:
    map<int, string> firstNames;
    map<int, string> lastNames;

    string nameForYear(const map<int, string> &m, int year)
    {
        const auto it = m.upper_bound(year);

        if (it == m.begin())
        {
            return "";
        }
        else
        {
            return prev(it)->second;
        }
    }
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990})
    {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
