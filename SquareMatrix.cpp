#include "SquareMatrix.h"

Square_matrix::Square_matrix(const Square_matrix& other_matrix)
{
	this->degree_of_two = other_matrix.degree_of_two;
	side_size = other_matrix.side_size;
	massive = new double[side_size * side_size];
	for (int i = 0; i < side_size * side_size; i++)
	{
		massive[i] = other_matrix.massive[i];
	}
}

Square_matrix::Square_matrix(int degree_of_two_for_the_side)
{
	this->degree_of_two = degree_of_two_for_the_side;
	side_size = 1 << (this->degree_of_two); // pow(2, this->degree_of_two);
	massive = new double[side_size * side_size];
}


Square_matrix::Square_matrix(int size_i, int size_j, int matrix_degree, ifstream& in)
{
	this->degree_of_two = matrix_degree;
	side_size = 1 << (this->degree_of_two); // pow(2, this->degree_of_two);
	massive = new double[side_size * side_size];
	int n2_matrix_size = 1 << matrix_degree;
	for (int i = 0; i < n2_matrix_size; i++)
	{
		for (int j = 0; j < n2_matrix_size; j++)
		{
			if ((i < size_i) && (j < size_j))
			{
				in >> (*this)(i, j);
			}
			else
			{
				(*this)(i, j) = 0;
			}
		}
	}
}


int Square_matrix::size() const { return side_size; }

double& Square_matrix::operator() (int i, int j)
{
	return massive[i * side_size + j];
}

const double& Square_matrix::operator() (int i, int j) const
{
	return massive[i * side_size + j];
}

Square_matrix& Square_matrix::operator = (const Square_matrix& other_mas)
{
	for (int i = 0; i < side_size * side_size; i++)
	{
		massive[i] = other_mas.massive[i];
	}
	return *this;
}

int Square_matrix::get_degree_of_two() const
{
	return this->degree_of_two;
}

Square_matrix& Square_matrix::operator += (const Square_matrix& other_mas)
{
	for (int i = 0; i < side_size * side_size; i++)
	{
		massive[i] += other_mas.massive[i];
	}
	return *this;
}

Square_matrix& Square_matrix::operator -= (const Square_matrix& other_mas)
{
	for (int i = 0; i < side_size * side_size; i++)
	{
		massive[i] -= other_mas.massive[i];
	}
	return *this;
}

bool const operator == (const Square_matrix& first_matrix, const Square_matrix& second_matrix)
{
	if ((first_matrix.degree_of_two != second_matrix.degree_of_two) || (first_matrix.side_size != second_matrix.side_size))
		return false;
	bool bla = true;
	for (int i = 0; i < first_matrix.side_size * first_matrix.side_size; i++)
	{
		if (first_matrix.massive[i] != second_matrix.massive[i])
			return false;
	}
	return true;
}

void Square_matrix::sub_matrix(int i, int j, Square_matrix& result) const
{
	for (int k = 0; k < side_size / 2; k++)
	{
		for (int l = 0; l < side_size / 2; l++)
		{
			result(k, l) = operator()((i * side_size / 2 + k), j * side_size / 2 + l);
		}
	}
}

void Square_matrix::multimatrix(const Square_matrix& first_matrix, const Square_matrix& second_matrix)
{
	/*int max = first_matrix.degree_of_two;
	if (second_matrix.degree_of_two > max)
		max = second_matrix.degree_of_two;
	(*this) = N2_matrix(max);*/
	if (first_matrix.get_degree_of_two() == 1)
	{
		(*this)(0, 0) = first_matrix(0, 0) * second_matrix(0, 0) + first_matrix(0, 1) * second_matrix(1, 0);
		(*this)(0, 1) = first_matrix(0, 0) * second_matrix(0, 1) + first_matrix(0, 1) * second_matrix(1, 1);
		(*this)(1, 0) = first_matrix(1, 0) * second_matrix(0, 0) + first_matrix(1, 1) * second_matrix(1, 0);
		(*this)(1, 1) = first_matrix(1, 0) * second_matrix(0, 1) + first_matrix(1, 1) * second_matrix(1, 1);
		return;
	}
	else
	{
		const int now_deg = first_matrix.get_degree_of_two() - 1;
		Square_matrix p1(now_deg); // named from formules of Strassen-algorythm
		Square_matrix p2(now_deg);
		Square_matrix p3(now_deg);
		Square_matrix p4(now_deg);
		Square_matrix p5(now_deg);
		Square_matrix p6(now_deg);
		Square_matrix p7(now_deg);
		Square_matrix helper1(now_deg); // to avoid some extra calculations
		Square_matrix helper2(now_deg);
		Square_matrix temporary(now_deg);
		first_matrix.sub_matrix(0, 0, helper1);
		first_matrix.sub_matrix(1, 1, temporary);
		helper1 += temporary;
		second_matrix.sub_matrix(0, 0, helper2);
		second_matrix.sub_matrix(1, 1, temporary);
		helper2 += temporary;
		p1.multimatrix(helper1, helper2);
		first_matrix.sub_matrix(1, 0, helper1);
		first_matrix.sub_matrix(1, 1, temporary);
		helper1 += temporary;
		second_matrix.sub_matrix(0, 0, temporary);
		p2.multimatrix(helper1, temporary);
		second_matrix.sub_matrix(0, 1, helper2);
		second_matrix.sub_matrix(1, 1, temporary);
		helper2 -= temporary;
		first_matrix.sub_matrix(0, 0, temporary);
		p3.multimatrix(temporary, helper2);
		second_matrix.sub_matrix(1, 0, helper2);
		second_matrix.sub_matrix(0, 0, temporary);
		helper2 -= temporary;
		first_matrix.sub_matrix(1, 1, temporary);
		p4.multimatrix(temporary, helper2);
		first_matrix.sub_matrix(0, 0, helper1);
		first_matrix.sub_matrix(0, 1, temporary);
		helper1 += temporary;
		second_matrix.sub_matrix(1, 1, temporary);
		p5.multimatrix(helper1, temporary);
		first_matrix.sub_matrix(1, 0, helper1);
		first_matrix.sub_matrix(0, 0, temporary);
		helper1 -= temporary;
		second_matrix.sub_matrix(0, 0, helper2);
		second_matrix.sub_matrix(0, 1, temporary);
		helper2 += temporary;
		p6.multimatrix(helper1, helper2);
		first_matrix.sub_matrix(0, 1, helper1);
		first_matrix.sub_matrix(1, 1, temporary);
		helper1 -= temporary;
		second_matrix.sub_matrix(1, 0, helper2);
		second_matrix.sub_matrix(1, 1, temporary);
		helper2 += temporary;
		p7.multimatrix(helper1, helper2);
		helper1 = p1;
		helper1 += p4;
		helper1 -= p5;
		helper1 += p7;
		for (int m = 0; m < first_matrix.size() / 2; m++)
		{
			for (int n = 0; n < first_matrix.size() / 2; n++)
			{
				(*this)(m, n) = helper1(m, n);
			}
		}
		helper1 = p3;
		helper1 += p5;
		for (int m = 0; m < first_matrix.size() / 2; m++)
		{
			for (int n = 0; n < first_matrix.size() / 2; n++)
			{
				(*this)(m, first_matrix.size() / 2 + n) = helper1(m, n);
			}
		}
		helper1 = p2;
		helper1 += p4;
		for (int m = 0; m < first_matrix.size() / 2; m++)
		{
			for (int n = 0; n < first_matrix.size() / 2; n++)
			{
				(*this)(m + first_matrix.size() / 2, n) = helper1(m, n);
			}
		}
		helper1 = p1;
		helper1 -= p2;
		helper1 += p3;
		helper1 += p6;
		for (int m = 0; m < first_matrix.size() / 2; m++)
		{
			for (int n = 0; n < first_matrix.size() / 2; n++)
			{
				(*this)(m + first_matrix.size() / 2, n + first_matrix.size() / 2) = helper1(m, n);
			}
		}
	}
}

int get_future_n2_matrix_degree(int size1i, int size1j, int size2j) // from sizes of matrix finds what degree of two should be in Square_matrix
{
	if ((size1i == 0) || (size1j == 0) || (size2j == 0))
		return 0; // should be a error
	int max_side = 0, degree = 0;
	if (size1j > size2j)
		max_side = size1j;
	else
		max_side = size2j;
	if (size1i > max_side)
		max_side = size1i;
	int two_in_degree = 1; // will be = pow(2, degree)
	while (two_in_degree < max_side)
	{
		degree++;
		two_in_degree = two_in_degree << 1;
	}
	return degree;
}

