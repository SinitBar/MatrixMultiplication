#pragma once
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

class Square_matrix
{
	int degree_of_two = 0; // [log(side_size)] + 1
	int side_size = 1; //Square_matrix has sides with side_size = 2 in some degree
	double* array = nullptr;
public:
	//Constructors
	Square_matrix();
	Square_matrix(const Square_matrix&); // creates N2_matrix equal to another N2_matrix
	Square_matrix(int); // creates empty Square_matrix with the side of square matrix = 2^(int_data)
	Square_matrix(double*, int, int, int);
	Square_matrix(double**, int, int, int);
	//interface
	int size() const; // ??? // retunrs a size of a square-side of matrix

	void stream_fill_square_matrix(int, int, int, ifstream&);

	double& operator() (int, int); // returns Square_matrix[i][j]

	const double& operator() (int, int) const; // ???

	void sub_matrix(int, int, Square_matrix&) const; // imagine Square_matrix is 4 Square_matrixes of smaller size indexed (0,0) (0,1) (1,0) (1,1)

	Square_matrix& operator = (const Square_matrix&);

	int get_degree_of_two() const; // returns [log(side_size)] + 1

	Square_matrix& operator += (const Square_matrix&);

	Square_matrix& operator -= (const Square_matrix&);

	friend bool const operator == (const Square_matrix&, const Square_matrix&);

	void multi_square_matrix(const Square_matrix& matr1, const Square_matrix& matr2);

	//destructors
	virtual ~Square_matrix()
	{
		delete[] array;
	}
};

int get_future_square_matrix_degree(int size1i, int size1j, int size2j);

void multimatrix_from_file();

double** multimatrix(const int&, const int&, double**, const int&, const int &, double**);

