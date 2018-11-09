#include "date.h"
#include <string>

using namespace std;

struct Node
{
    virtual int Evaluate() const = 0;
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

struct DateComparisonNode : public Node
{
    DateComparisonNode(Comparison cmp, const Date &date) : _cmp(cmp), _date(date) {}

private:
    const Comparison _cmp;
    const Date _date;
};

struct EventComparisonNode : public Node
{
    EventComparisonNode(Comparison cmp, const string &event) : _cmp(cmp), _event(event) {}

private:
    const Comparison _cmp;
    const string _event;
};

struct LogicalOperationNode : public Node
{
    LogicalOperationNode(LogicalOperation op, const Node &left, const Node &right) :
    _op(op), _left(left), _right(right) {}

private:
    const LogicalOperation _op;
    const Node _left;
    const Node _right;
};
