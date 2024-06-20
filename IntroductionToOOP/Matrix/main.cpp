#include <iostream>
using namespace std;

#define tab "\t"

class Matrix
{
	int rows;
	int cols;
	int** data;
public:
	int get_rows()const
	{
		return rows;
	}
	int get_cols()const
	{
		return cols;
	}
	int** const get_data()const
	{
		return data;
	}
	//		Constructors:
	Matrix(int rows = 0, int cols = 0) : rows(rows), cols(cols), data(new int* [rows] {})
	{
		for (int i = 0; i < rows; i++)data[i] = new int[cols] {};
	}
	Matrix(int rows, int cols, int number): Matrix(rows, cols)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				data[i][j] = number;
	}
	Matrix(const Matrix& other): Matrix(other.rows, other.cols)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				data[i][j] = other.data[i][j];
	}
	~Matrix()
	{
		for (int i = 0; i < rows; i++)
			delete[] data[i];
		delete[] data;
	}
	//		Operators:
	Matrix& operator=(const Matrix& other)
	{
		if (this == &other) return *this;

		this->~Matrix();
		this->rows = other.rows;
		this->cols = other.cols;
		this->data = new int* [rows] {};
		for (int i = 0; i < this->rows; i++)this->data[i] = new int[cols] {};

		for (int i = 0; i < this->rows; i++)
			for (int j = 0; j < this->cols; j++)
				this->data[i][j] = other.data[i][j];
		return *this;
	}
	
	//		Methods:
	void print()const
	{
		cout << "Rows: " << rows << tab << "Cols: " << cols << endl;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << data[i][j] << tab;
			}
			cout << endl;
		}
	}
};
std::ostream& operator<<(std::ostream& os, const Matrix& obj)
{
	os << "Rows: " << obj.get_rows() << tab << "Cols: " << obj.get_cols() << endl;
	for (int i = 0; i < obj.get_rows(); i++)
	{
		for (int j = 0; j < obj.get_cols(); j++)
		{
			os << obj.get_data()[i][j] << tab;
		}
		os << endl;
	}
	return os;
}

//#define CONSTRUCTORS_CHECK
#define OPERATORS_CHECK

int main()
{
#ifdef CONSTRUCTORS_CHECK
	Matrix A;
	A.print();

	Matrix B(2, 3, 1);
	B.print();

	Matrix C(B);
	C.print();

	Matrix D;
	D = C;
	D.print();
#endif // CONSTRUCTORS_CHECK
	Matrix A(3, 3);

	cout << A << endl;
}