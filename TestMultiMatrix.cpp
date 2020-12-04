#include "pch.h"
#include "CppUnitTest.h"
#include "/Users/varka/source/repos/Strassen/SquareMatrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMultiMatrix
{
	TEST_CLASS(TestMultiMatrix)
	{
	public:
		
		TEST_METHOD(test_get_future_square_matrix_degree_zero)
		{
			int size1i = 1, size1j = 1, size2j = 1;
			Assert::AreEqual(get_future_square_matrix_degree(size1i, size1j, size2j), 0);
		}

		TEST_METHOD(test_get_future_square_matrix_degree_one)
		{
			int size1i = 1, size1j = 2, size2j = 2;
			Assert::AreEqual(get_future_square_matrix_degree(size1i, size1j, size2j), 1);
		}

		TEST_METHOD(test_get_future_square_matrix_degree_two)
		{
			int size1i = 3, size1j = 2, size2j = 2;
			Assert::AreEqual(get_future_square_matrix_degree(size1i, size1j, size2j), 2);
		}

		TEST_METHOD(test_operator_plus_equal)
		{
			const int size1i = 2, size1j = 3, size2i = 3, size2j = 2;
			double** first = new double* [size1i];
			for (int i = 0; i < size1i; i++)
				first[i] = new double[size1j];
			double** second = new double* [size2i];
			for (int i = 0; i < size2i; i++)
				second[i] = new double[size2j];
			double** right_result = new double* [3];
			for (int i = 0; i < 3; i++)
				right_result[i] = new double[3];
			first[0][0] = 1; first[0][1] = 0; first[0][2] = 2;
			first[1][0] = 0; first[1][1] = 0; first[1][2] = 1;
			second[0][0] = 1; second[0][1] = 0;
			second[1][0] = 0; second[1][1] = 2;
			second[2][0] = 1; second[2][1] = 1;
			right_result[0][0] = 2; right_result[0][1] = 0; right_result[0][2] = 2;
			right_result[1][0] = 0; right_result[1][1] = 2; right_result[1][2] = 1;
			right_result[2][0] = 1; right_result[2][1] = 1; right_result[2][2] = 0;
			Square_matrix plused_matrix(right_result, 3, 3, 2);
			Square_matrix first_matrix(first, size1i, size1j, 2);
			Square_matrix second_matrix(second, size2i, size2j, 2);
			first_matrix += second_matrix;
			Assert::AreEqual(first_matrix == plused_matrix, true);
		}

		TEST_METHOD(test_operator_minus_equal)
		{
			const int size1i = 2, size1j = 3, size2i = 3, size2j = 2;
			double** first = new double* [size1i];
			for (int i = 0; i < size1i; i++)
				first[i] = new double[size1j];
			double** second = new double* [size2i];
			for (int i = 0; i < size2i; i++)
				second[i] = new double[size2j];
			double** right_result = new double* [3];
			for (int i = 0; i < 3; i++)
				right_result[i] = new double[3];
			first[0][0] = 1; first[0][1] = 0; first[0][2] = 2;
			first[1][0] = 0; first[1][1] = 0; first[1][2] = 1;
			second[0][0] = 1; second[0][1] = 0;
			second[1][0] = 0; second[1][1] = 2;
			second[2][0] = 1; second[2][1] = 1;
			right_result[0][0] = 0; right_result[0][1] = 0; right_result[0][2] = 2;
			right_result[1][0] = 0; right_result[1][1] = -2; right_result[1][2] = 1;
			right_result[2][0] = -1; right_result[2][1] = -1; right_result[2][2] = 0;
			Square_matrix substituted_matrix(right_result, 3, 3, 2);
			Square_matrix first_matrix(first, size1i, size1j, 2);
			Square_matrix second_matrix(second, size2i, size2j, 2);
			first_matrix -= second_matrix;
			Assert::AreEqual(first_matrix == substituted_matrix, true);
		}

		TEST_METHOD(multimatrix_array)
		{
			const int size1i = 2, size1j = 3, size2i = 3, size2j = 2;
			double** first = new double* [size1i];
			for (int i = 0; i < size1i; i++)
				first[i] = new double[size1j];
			double** second = new double* [size2i];
			for (int i = 0; i < size2i; i++)
				second[i] = new double[size2j];
			double** right_result = new double* [size1i];
			for (int i = 0; i < size1i; i++)
				right_result[i] = new double[size2j];
			first[0][0] = 1; first[0][1] = 0; first[0][2] = 2;
			first[1][0] = 0; first[1][1] = 0; first[1][2] = 1;
			second[0][0] = 1; second[0][1] = 0;
			second[1][0] = 0; second[1][1] = 2;
			second[2][0] = 1; second[2][1] = 1;
			right_result[0][0] = 3; right_result[0][1] = 2;
			right_result[1][0] = 1; right_result[1][1] = 1;
			double** result = multimatrix(2, 3, first, 3, 2, second);
			for (int i = 0; i < size1i; i++)
			{
				for (int j = 0; j < size2j; j++)
					Assert::AreEqual(result[i][j], right_result[i][j]);
			}
		}

		TEST_METHOD(sub_matrix_test)
		{
			const int size1i = 2, size1j = 3, size2i = 3, size2j = 2;
			int degree = get_future_square_matrix_degree(size1i, size1j, size2j);
			int sub_matrix_side_size = 1 << (degree - 1);
			Assert::AreEqual(degree, 2);
			Assert::AreEqual(sub_matrix_side_size, 2);
			double** matrix = new double* [size1i];
			for (int i = 0; i < size1i; i++)
				matrix[i] = new double[size1j];
			matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 2;
			matrix[1][0] = 0; matrix[1][1] = 0; matrix[1][2] = 1;
			double** extra_matrix = new double* [sub_matrix_side_size];
			for (int i = 0; i < sub_matrix_side_size; i++)
				extra_matrix[i] = new double[sub_matrix_side_size];
			extra_matrix[0][0] = 1; extra_matrix[0][1] = 0; 
			extra_matrix[1][0] = 0; extra_matrix[1][1] = 0;
			Square_matrix square_matrix(matrix, size1i, size1j, degree);
			Square_matrix sub_matrix(degree-1);
			Square_matrix right_sub_matrix_0_0(extra_matrix, sub_matrix_side_size, sub_matrix_side_size, degree-1);
			square_matrix.sub_matrix(0, 0, sub_matrix);
			Assert::AreEqual(sub_matrix == right_sub_matrix_0_0, true);
			square_matrix.sub_matrix(0, 1, sub_matrix);
			extra_matrix[0][0] = 2; extra_matrix[0][1] = 0;
			extra_matrix[1][0] = 1; extra_matrix[1][1] = 0;
			Square_matrix right_sub_matrix_0_1(extra_matrix, sub_matrix_side_size, sub_matrix_side_size, degree - 1);
			Assert::AreEqual(sub_matrix == right_sub_matrix_0_1, true);
			square_matrix.sub_matrix(1, 0, sub_matrix);
			extra_matrix[0][0] = 0; extra_matrix[0][1] = 0;
			extra_matrix[1][0] = 0; extra_matrix[1][1] = 0;
			Square_matrix right_sub_matrix_1_0(extra_matrix, sub_matrix_side_size, sub_matrix_side_size, degree - 1);
			Assert::AreEqual(sub_matrix == right_sub_matrix_1_0, true);
			Square_matrix right_sub_matrix_1_1(extra_matrix, sub_matrix_side_size, sub_matrix_side_size, degree - 1);
			square_matrix.sub_matrix(1, 1, sub_matrix);
			Assert::AreEqual(sub_matrix == right_sub_matrix_1_1, true);
		}


		TEST_METHOD(TestMethodMultiMatrixFile)
		{
			ifstream in("/Users/varka/source/repos/TestMultiMatrix/in.txt");
			ofstream out("/Users/varka/source/repos/TestMultiMatrix/out.txt");
			int size1i, size1j, size2i, size2j;
			in >> size1i >> size1j >> size2i >> size2j;
			int n2_matrix_degree = get_future_square_matrix_degree(size1i, size1j, size2j);
			Square_matrix first_matrix, second_matrix;
			first_matrix.stream_fill_square_matrix(size1i, size1j, n2_matrix_degree, in);
			second_matrix.stream_fill_square_matrix(size2i, size2j, n2_matrix_degree, in);
			Square_matrix result(n2_matrix_degree);
			result.multi_square_matrix(first_matrix, second_matrix);
			for (int i = 0; i < size1i; i++)
			{
				for (int j = 0; j < size2j; j++)
				{
					out << result(i, j) << " ";
					cout << result(i, j) << " ";
					if (j == size2j - 1)
					{
						out << endl;
						cout << endl;
					}
				}
			}
			in.close();
			out.close();
			in.open("/Users/varka/source/repos/TestMultiMatrix/right_out.txt");
			Square_matrix right_result;
			right_result.stream_fill_square_matrix(size1i, size2j, n2_matrix_degree, in);
			in.close();
			Assert::AreEqual(result == right_result, true);
		}
	};
}
