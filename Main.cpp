#include "SquareMatrix.h"
int main()
{
	ifstream in("in.txt");
	ofstream out("out.txt");
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
	in.open("right_out.txt");
	Square_matrix right_result;
	right_result.stream_fill_square_matrix(size1i, size2j, n2_matrix_degree, in);
	if (result == right_result)
		cout << "you won!!!" << endl;
	return 0;
}