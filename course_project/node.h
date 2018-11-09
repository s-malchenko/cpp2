#include "date.h"
#include <string>
#include <memory>

using namespace std;

class Node
{
public:
    virtual bool Evaluate(const Date &date, const string &event) const = 0;
};

class EmptyNode : public Node
{
public:
    bool Evaluate(const Date &date, const string &event) const override;
};

enum Comparison
{
    Less = 0,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum LogicalOperation
{
    Or = 0,
    And
};

class DateComparisonNode : public Node
{
public:
    DateComparisonNode(Comparison cmp, const Date &date);
    bool Evaluate(const Date &date, const string &event) const override;

private:
    const Comparison _cmp;
    const Date _date;
};

class EventComparisonNode : public Node
{
public:
    EventComparisonNode(Comparison cmp, const string &event);
    bool Evaluate(const Date &date, const string &event) const override;

private:
    const Comparison _cmp;
    const string _event;
};

class LogicalOperationNode : public Node
{
public:
    LogicalOperationNode(LogicalOperation op, const shared_ptr<Node> &left, const shared_ptr<Node> &right);
    bool Evaluate(const Date &date, const string &event) const override;

private:
    const LogicalOperation _op;
    shared_ptr<Node> _left;
    shared_ptr<Node> _right;
};
