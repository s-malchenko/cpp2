#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
class Matrix
{
public:
    Matrix()
    {
        columns = 0;
    }

    Matrix(int num_rows, int num_cols)
    {
        Reset(num_rows, num_cols);
    }

    void Reset(int num_rows, int num_cols)
    {
        if (num_cols < 0 || num_rows < 0)
        {
            throw out_of_range("wrong params");
        }

        matrix.assign(num_rows, vector<int>(num_cols));

        columns = num_cols;
    }

    int At(int num_rows, int num_cols) const
    {
        return matrix.at(num_rows).at(num_cols);
    }

    int& At(int num_rows, int num_cols)
    {
        return matrix.at(num_rows).at(num_cols);
    }

    int GetNumRows() const
    {
        return matrix.size();
    }

    int GetNumColumns() const
    {
        return columns;
    }

    const vector<vector<int>>& Value() const
    {
        return matrix;
    }

private:
    vector<vector<int>> matrix;
    int columns = 0;
};
// * оператор ввода для класса Matrix из потока istream
istream& operator>>(istream &stream, Matrix &m)
{
    int rows, cols;

    stream >> rows >> cols;
    m = Matrix(rows, cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            stream >> m.At(i, j);
        }
    }

    return stream;
}

// * оператор вывода класса Matrix в поток ostream
ostream& operator<<(ostream &stream, const Matrix &m)
{
    int rows = m.GetNumRows();
    int cols = m.GetNumColumns();

    stream << rows << " " << cols << endl;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            stream << m.At(i, j);

            if (j == cols - 1)
            {
                stream << endl;
            }
            else
            {
                stream << " ";
            }
        }
    }

    return stream;
}

// * оператор проверки на равенство двух объектов класса Matrix
bool operator==(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.Value() != rhs.Value() ||
        lhs.GetNumRows() != rhs.GetNumRows() ||
        lhs.GetNumColumns() != rhs.GetNumColumns())
    {
        return false;
    }
    else 
    {
        return true;
    }
}
// * оператор сложения двух объектов класса Matrix
Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    int rows = lhs.GetNumRows();
    int cols = lhs.GetNumColumns();

    if (rows != rhs.GetNumRows() || cols != rhs.GetNumColumns())
    {
        throw invalid_argument("matrix sizes are not equal");
    }

    Matrix sum(rows, cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            sum.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }

    return sum;
}

int main()
{
    Matrix one;
    Matrix two;

    cin >> one >> two;
    one.At(2, 2);
    cout << one + two << endl;
    return 0;
}
