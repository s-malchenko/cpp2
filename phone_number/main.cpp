#include "phone_number.h"
#include <iostream>

int main()
{
    string s;
    while (true)
    {
        cin >> s;

        try
        {
            PhoneNumber p(s);
            cout << "International: " << p.GetInternationalNumber() << endl;
            cout << "Country: " << p.GetCountryCode() << endl;
            cout << "City: " << p.GetCityCode() << endl;
            cout << "Local: " << p.GetLocalNumber() << endl;
        }
        catch (exception &e)
        {
            cout << "Exception: " << e.what() << endl;
        }
    }
    return 0;
}