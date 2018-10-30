#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

class Figure
{
public:
    Figure(const string &name) : name_(name) {}

    string Name() const
    {
        return name_;
    }
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;

protected:
    const string name_;
};

class Triangle : public Figure
{
public:
    Triangle(int a, int b, int c) : Figure("TRIANGLE")
    {
        a_ = a;
        b_ = b;
        c_ = c;
    }

    double Perimeter() const override
    {
        return a_ + b_ + c_;
    }

    double Area() const override
    {
        double p = (a_ + b_ + c_) / 2.0;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }
private:
    int a_, b_, c_;
};

class Rect : public Figure
{
public:
    Rect(int a, int b) : Figure("RECT")
    {
        a_ = a;
        b_ = b;
    }

    double Perimeter() const override
    {
        return 2 * (a_ + b_);
    }

    double Area() const override
    {
        return a_ * b_;
    }
private:
    int a_, b_;
};

class Circle : public Figure
{
public:
    Circle(int r) : Figure("CIRCLE")
    {
        r_ = r;
    }

    double Perimeter() const override
    {
        return 2 * 3.14 * r_;
    }

    double Area() const override
    {
        return 3.14 * r_ * r_;
    }
private:
    int r_;
};

template <typename S>
shared_ptr<Figure> CreateFigure(S &stream)
{
    string name;
    stream >> name;
    int a, b, c;

    if (name == "TRIANGLE")
    {
        stream >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
    else if (name == "RECT")
    {
        stream >> a >> b;
        return make_shared<Rect>(a, b);
    }
    else
    {
        stream >> a;
        return make_shared<Circle>(a);
    }
}

int main()
{
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); )
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD")
        {
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto &current_figure : figures)
            {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}