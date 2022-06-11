//My header files
#include "../Header/Operators.h"

namespace Operators {

	std::ostream& operator<< (std::ostream& cout, const Vector& v) {
		bool flag = false;

		for (std::size_t i = 0; i < v.size(); ++i)
		{
			if (v.size() == 1)
				std::cout << "[" << v[i] << "]" << std::endl;
			else if (i == 0)
				std::cout << "[" << v[i] << ", ";
			else if (i + 1 == v.size())
				std::cout << v[i] << "]" << std::endl;
			else {
				std::cout << v[i] << ", ";

				//The case the given vector is bigger then 10 elements:
				if (i > 2 and v.size() > 10 and not flag) {
					std::cout << "... ";
					i = v.size() - 4;
					flag = true;
				}
			}
		}
		return cout;
	}


	std::ostream& operator<< (std::ostream& cout, const Matrix& matrix) {
		bool flag = false;

		for (std::size_t i = 0; i < matrix.size(); ++i)
		{
			if (matrix.size() == 1) {
				std::cout << "[\n ";
				std::cout << matrix[i];
				std::cout << "]" << std::endl;
			}
			else if (i == 0) {
				std::cout << "[ ";
				std::cout << matrix[i];
			}
			else if (i + 1 == matrix.size()) {
				std::cout << " ";
				std::cout << matrix[i];
				std::cout << "] " << std::endl;
			}
			else {
				std::cout << " ";
				std::cout << matrix[i];

				//The case the given matrix is bigger then 10 elements:
				if (i > 2 and matrix.size() > 10 and not flag) {
					std::cout << " ...	\n";
					i = matrix.size() - 4;
					flag = true;
				}
			}
		}
		return cout;
	}


	Matrix operator*(const Matrix& lowTriangularMtx, const Matrix& upTriangularMtx)
	{
		int lowTriangularMtx_row = lowTriangularMtx.size();
		int lowTriangularMtx_col = lowTriangularMtx[0].size();
		int upTriangularMtx_row = upTriangularMtx.size();
		int upTriangularMtx_col = upTriangularMtx[0].size();

		//The case that  matrix multiplication isn't define.
		if (lowTriangularMtx_col != upTriangularMtx_row) {
			std::string str = "Cann't multiply (" +
				std::to_string(lowTriangularMtx_row) + ", " + std::to_string(lowTriangularMtx_col) +
				") by (" + std::to_string(upTriangularMtx_row) + ", " + std::to_string(upTriangularMtx_col) + ").";
			std::cout << str << std::endl;
			throw std::invalid_argument(str);
		}

		//Pre-allocation of the vector size:
		Vector v(upTriangularMtx_col);
		Matrix new_matrix(lowTriangularMtx_row, v);

		for (int i = 0; i < lowTriangularMtx_row; i++)
		{
			for (int j = 0; j < upTriangularMtx_col; j++)
			{
				double num = 0;
				for (size_t k = 0; k < i + 1; k++)
				{
					num += lowTriangularMtx[i][k] * upTriangularMtx[k][j];
				}
				new_matrix[i][j] = num;
			}
		}

		return new_matrix;
	}
};