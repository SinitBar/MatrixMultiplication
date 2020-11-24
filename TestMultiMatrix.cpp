#include "pch.h"
#include "CppUnitTest.h"
#include "/Users/varka/source/repos/Strassen/SquareMatrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestMultiMatrix
{
	TEST_CLASS(TestMultiMatrix)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ifstream in("/Users/varka/source/repos/TestMultiMatrix/in.txt");
			ofstream out("/Users/varka/source/repos/TestMultiMatrix/out.txt");
			int size1i, size1j, size2i, size2j;
			in >> size1i >> size1j >> size2i >> size2j;
			int n2_matrix_degree = get_future_n2_matrix_degree(size1i, size1j, size2j);
			Square_matrix first_matrix(size1i, size1j, n2_matrix_degree, in);
			Square_matrix second_matrix(size2i, size2j, n2_matrix_degree, in);
			Square_matrix result(n2_matrix_degree);
			result.multimatrix(first_matrix, second_matrix);
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
			Square_matrix right_result(size1i, size2j, n2_matrix_degree, in);
			in.close();
			Assert::AreEqual(result == right_result, true);
		}
	};
}
