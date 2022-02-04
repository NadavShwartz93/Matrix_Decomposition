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
				std::cout << "[" << v[i] << ",	";
			else if (i + 1 == v.size())
				std::cout << v[i] << "]" << std::endl;
			else {
				std::cout << v[i] << ",	";

				//The case the given vector is bigger then 10 elements:
				if (i > 2 and v.size() > 10 and not flag) {
					std::cout << "...	";
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
				//print_vec(matrix[i]);
				std::cout << "]" << std::endl;
			}
			else if (i == 0) {
				std::cout << "[ ";
				std::cout << matrix[i];
				//print_vec(matrix[i]);
			}
			else if (i + 1 == matrix.size()) {
				std::cout << " ";
				std::cout << matrix[i];
				//print_vec(matrix[i]);
				std::cout << "] " << std::endl;
			}
			else {
				std::cout << " ";
				std::cout << matrix[i];
				//print_vec(matrix[i]);

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


	std::ofstream& operator<< (std::ofstream& of, const Matrix& mtx) {
		int row = mtx.size();
		int col = mtx[0].size();

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (not(j + 1 < col))		//Case of the last number in the matrix
					of << mtx[i][j];
				else
					of << mtx[i][j] << ",";
			}
			if (i + 1 < row)
				of << "\n";
		}
		return of;
	}

	
	Vector operator*(double scalar, Vector& v) {
		for (std::size_t i = 0; i < v.size(); ++i)
		{
			v[i] = scalar * v[i];
		}
		return v;
	}

	
	double operator*(const Vector& v1, const Vector& v2) {
		int n;

		if ((n = v1.size()) != v2.size()) {
			std::string str = "vectors are not in the same size.";
			throw std::invalid_argument(str);
		}

		double sum = 0;
		for (int i = 0; i < n; i++)
			sum += (v1[i] * v2[i]);

		return sum;
	}

	
	Vector operator-(Vector v1, Vector v2) {
		auto minus = [](double a, double b) { return a - b; };
		Vector v;
		for (std::size_t i = 0; i < v1.size(); ++i)
		{
			v.push_back(minus(v1[i], v2[i]));
		}
		return v;
	}
};