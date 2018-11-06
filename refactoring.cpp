#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:
    Human(const string &name, const string &type) : name_(name), type_(type) {}

    virtual void Walk(const string &destination) const
    {
        Description() << " walks to " << destination << endl;
    }

    ostream &Description() const
    {
        return cout << type_ + ": " + name_;
    }

    const string name_;
    const string type_;
};

class Student : public Human
{
public:
    Student(const string &name, const string &favouriteSong) :
        Human(name, "Student"),
        favouriteSong_(favouriteSong)
    {}

    void Learn() const
    {
        Description() << " learns" << endl;
    }

    void Walk(const string &destination) const override
    {
        Human::Walk(destination);
        SingSong();
    }

    void SingSong() const
    {
        Description() << " sings a song: " << favouriteSong_ << endl;
    }

private:
    const string favouriteSong_;
};


class Teacher : public Human
{
public:
    Teacher(const string &name, const string &subject) :
        Human(name, "Teacher"),
        subject_(subject)
    {}

    void Teach() const
    {
        Description() << " teaches: " << subject_ << endl;
    }

private:
    const string subject_;
};

class Policeman : public Human
{
public:
    Policeman(const string &name) : Human(name, "Policeman") {}

    void Check(const Human &h)
    {
        Description() << " checks " << h.type_ << ". " << h.type_ << "'s name is: " << h.name_ << endl;
    }
};

void VisitPlaces(const Human &h, const vector<string> &places)
{
    for (const auto &p : places)
    {
        h.Walk(p);
    }
}

int main()
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});

    cout << endl << "Correct output:" << endl;
    cout << "Teacher: Jim walks to: Moscow\nTeacher: Jim walks to: London\nPoliceman: Bob checks Student. Student's name is: Ann\n";
    cout << "Student: Ann walks to: Moscow\nStudent: Ann sings a song: We will rock you\nStudent: Ann walks to: London\n";
    cout << "Student: Ann sings a song: We will rock you\n";

    return 0;
}