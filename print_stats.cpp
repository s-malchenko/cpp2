#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// enum class Gender
// {
//     FEMALE,
//     MALE
// };

// struct Person
// {
//     int age;  // возраст
//     Gender gender;  // пол
//     bool is_employed;  // имеет ли работу
// };



// // Это пример функции, его не нужно отправлять вместе с функцией PrintStats
// template <typename InputIt>
// int ComputeMedianAge(InputIt range_begin, InputIt range_end)
// {
//     if (range_begin == range_end)
//     {
//         return 0;
//     }
//     vector<typename InputIt::value_type> range_copy(range_begin, range_end);
//     auto middle = begin(range_copy) + range_copy.size() / 2;
//     nth_element(
//         begin(range_copy), middle, end(range_copy),
//         [](const Person & lhs, const Person & rhs)
//     {
//         return lhs.age < rhs.age;
//     }
//     );
//     return middle->age;
// }

void PrintStats(vector<Person> persons)
{
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    auto gender_it = partition(persons.begin(), persons.end(), [](const Person& p) { return p.gender == Gender::FEMALE; });
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), gender_it) << endl;
    cout << "Median age for males = " << ComputeMedianAge(gender_it, persons.end()) << endl;
    auto job_it = partition(persons.begin(), gender_it, [](const Person& p) { return p.is_employed; });
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), job_it) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(job_it, gender_it) << endl;
    job_it = partition(gender_it, persons.end(), [](const Person& p) { return p.is_employed; });
    cout << "Median age for employed males = " << ComputeMedianAge(gender_it, job_it) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(job_it, persons.end()) << endl;
}

// int main()
// {
//     vector<Person> persons =
//     {
//         {31, Gender::MALE, false},
//         {40, Gender::FEMALE, true},
//         {24, Gender::MALE, true},
//         {20, Gender::FEMALE, true},
//         {80, Gender::FEMALE, false},
//         {78, Gender::MALE, false},
//         {10, Gender::FEMALE, false},
//         {55, Gender::MALE, true},
//     };
//     PrintStats(persons);
//     return 0;
// }
