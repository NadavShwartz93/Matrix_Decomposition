//My header files:
#include "../Header/Matrix_Operations.h"
#include "../Header/QR_Decomposition.h"


using namespace std;
using namespace Matrix_Operations_;

namespace QR_Decomposition_ {
	/*
	Execute projection operation between two vectors.
	*/
	inline Vector QR_Decomposition::projection(Vector u, Vector v1) {
		double t1 = u * v1;
		double t2 = u * u;
		t1 = t1 / t2;
		return t1 * u;
	}


	/*
	For giveen matrix A[a1, a2, ..., an] in size n x n.
	Execute Gram Schmidt process, and return new matrix.
	*/
	Matrix QR_Decomposition::Gram_Schmidt_process(Matrix matrix) {

		if (matrix.size() != matrix[0].size()) {
			std::string str = "The matrix is not square matrix";
			throw std::invalid_argument(str);
		}

		transpose(matrix);
		int index = 1;

		Matrix new_matrix;
		new_matrix.push_back(matrix[0]);

		for (std::size_t i = 1; i < matrix.size(); ++i)
		{
			Vector b = matrix[i];
			for (int j = 0; j < index; j++)
			{
				auto t = projection(new_matrix[j], matrix[i]);
				b = b - t;
			}

			index++;
			new_matrix.push_back(b);
		}
		transpose(new_matrix);
		return new_matrix;
	}


	/*
	Q is an orthogonal matrix, that created by normalize
	the columns of the matrix that has been received
	from Gram Schmidt process.
	*/
	Matrix QR_Decomposition::Q_matrix(Matrix U) {
		Matrix Q;

		transpose(U);

		for (std::size_t i = 0; i < U.size(); ++i)
		{
			double v_len = vec_length(U[i]);
			Q.push_back(dot_product(1 / v_len, U[i]));
		}
		transpose(Q);
		return(Q);
	}


	/*
		R is an upper triangular matrix.
		R produce by multiplication of Q transpose and input_matrix.
	*/
	Matrix QR_Decomposition::R_matrix(Matrix input_matrix,
		Matrix Q) {

		transpose(Q);
		return dot_product(Q, input_matrix, true);
	}


	/*
		Calculation of QR decomposition of the given matrix.
	*/
	void QR_Decomposition::QR_decomposition(const Matrix& input_matrix) {
		std::cout << "Matrix after Gram Schmidt process:" << std::endl;
		auto mtx = Gram_Schmidt_process(input_matrix);
		std::cout << mtx;
		//print_matrix(mtx);

		std::cout << "Q Matrix:" << std::endl;
		auto Q = Q_matrix(mtx);
		std::cout << Q;
		//print_matrix(Q);

		std::cout << "R Matrix:" << std::endl;
		auto R = R_matrix(input_matrix, Q);
		std::cout << R;
		//print_matrix(R);

		check_decomposition(Q, R);
	}


	/*
		Checking that the Q * R is equal to input matrix.
	*/
	void QR_Decomposition::check_decomposition(const Matrix& Q,
		const Matrix& R) {

		std::cout << "Examination Of The Decomposition: " << std::endl;
		std::cout << "Q*R = " << std::endl;
		auto mul = dot_product(Q, R);
		std::cout << mul;
		//print_matrix(mul);

	}

};