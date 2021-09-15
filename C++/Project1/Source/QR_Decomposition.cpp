#include<iostream>
#include<vector>
#include <string>

//My header files:
#include "../Header/QR_Decomposition.h"
#include "../Header/Matrix_Operations.h"


using namespace std;
using namespace Matrix_Operations;

namespace QR_Decomposition {
	/*
	Execute projection operation between two vectors.
	*/
	inline vector<double> projection(vector<double> u, vector<double> v1) {
		double t1 = dot_product(u, v1);
		double t2 = dot_product(u, u);
		return dot_product(t1 / t2, u);
	}


	/*
	Execute subtraction operation between two 1D vectors.
	*/
	inline vector<double> vec_minus(vector<double> v1, vector<double> v2) {
		auto minus = [](double a, double b) { return a - b; };
		vector<double> v;
		for (std::size_t i = 0; i < v1.size(); ++i)
		{
			v.push_back(minus(v1[i], v2[i]));
		}
		return v;
	}


	/*
	For giveen matrix A[a1, a2, ..., an] in size n x n.
	Execute Gram Schmidt process, and return new matrix.
	*/
	vector<vector<double>> Gram_Schmidt_process(vector<vector<double>> matrix) {

		if (matrix.size() != matrix[0].size()) {
			std::string str = "The matrix is not square matrix";
			throw std::invalid_argument(str);
		}

		transpose(matrix);
		int index = 1;

		vector<vector<double>> new_matrix;
		new_matrix.push_back(matrix[0]);

		for (std::size_t i = 1; i < matrix.size(); ++i)
		{
			vector<double> b = matrix[i];
			for (int j = 0; j < index; j++)
			{
				auto t = projection(new_matrix[j], matrix[i]);
				b = vec_minus(b, t);
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
	vector<vector<double>> Q_matrix(vector<vector<double>> U) {
		vector<vector<double>> Q;

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
	vector<vector<double>> R_matrix(vector<vector<double>> input_matrix, vector<vector<double>> Q) {
		transpose(Q);

		return dot_product(Q, input_matrix, my_round);

	}


	/*
		Calculation of QR decomposition of the given matrix.
	*/
	void QR_decomposition(const vector<vector<double>>& input_matrix) {
		std::cout << "Matrix after Gram Schmidt process:" << std::endl;
		auto mtx = Gram_Schmidt_process(input_matrix);
		print_matrix(mtx);

		std::cout << "Q Matrix:" << std::endl;
		auto Q = Q_matrix(mtx);
		print_matrix(Q);

		std::cout << "R Matrix:" << std::endl;
		auto R = R_matrix(input_matrix, Q);
		print_matrix(R);

		check_decomposition(Q, R);
	}


	/*
		Checking that the Q * R is equal to input matrix.
	*/
	void check_decomposition(vector<vector<double>>& Q,
		vector<vector<double>>& R) {

		std::cout << "Examination Of The Decomposition: " << std::endl;
		std::cout << "Q*R = " << std::endl;
		auto mul = dot_product(Q, R);
		print_matrix(mul);

	}

};