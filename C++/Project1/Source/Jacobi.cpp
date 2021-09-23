#include<iostream>
#include<vector>
#include<tuple>
#include <string>

//My header files
#include "../Header/Matrix_Operations.h"
#include "../Header/Jacobi.h"

using namespace std;
using namespace Matrix_Operations;

//Method for Jacobi Eigenvalue Algorithm:

namespace Jacobi {

	/*
	find_max_num method find the largest off-diagonal element, and return his index and value.
	The given matrix is symmetric, so only need to search in the upper triangular matrix.
	*/
	std::tuple<double, int, int> find_max_num(const Matrix& matrix) {
		int row = matrix.size();
		int col = matrix[0].size();
		int p, q;
		double max_val;

		for (int i = 0; i < row; i++)
		{
			for (int j = i + 1; j < col; j++)
			{
				if (i == 0 and j == 1) {
					max_val = std::abs(matrix[i][j]);
					p = i;
					q = j;
				}
				else if (max_val < std::abs(matrix[i][j])) {
					max_val = std::abs(matrix[i][j]);
					p = i;
					q = j;
				}
			}
		}

		return std::make_tuple(max_val, p, q);
	}


	/*
	calce_J_matrix method find the rotation matrix that called J:
	*/
	std::tuple<Matrix, double, double>
	calce_J_matrix(const Matrix& matrix, int p, int q) {

		//Check that the given matrix is square matrix
		if (matrix.size() != matrix[0].size()) {
			std::string str = "The given matrix is not square matrix.";
			throw std::invalid_argument(str);
		}

		//alocation new identity matrix:
		int n = matrix.size();
		auto J = eye_matrix(n);

		double theta;

		//calculate theta:
		if (matrix[q][q] == matrix[p][p])
			theta = PI / 4;
		else {
			double a = (2 * matrix[p][q]) / (matrix[q][q] - matrix[p][p]);
			theta = 0.5 * atan(a);
		}

		double cosinus, sinus;
		//insert new values to different places in the matrix J :
		J[p][p] = J[q][q] = cosinus = cos(theta);
		J[q][p] = sinus = sin(theta);
		J[p][q] = -1 * sin(theta);

		return std::make_tuple(J, cosinus, sinus);
	}


	/*
	For make the performention of Jacobi Eigenvalue Algorithm better,
	matrix multiplication of J.T*A*J is replaced by some elementary operations.
	And then, the all function is O(n) instead of O(n^2).
	*/
	void calc_matrix(Matrix& mtx, double cos, double sin, int i, int j) {
		double a_ii = mtx[i][i];
		double a_ij = mtx[i][j];
		double a_jj = mtx[j][j];
		double a_ji = mtx[j][i];

		mtx[i][i] = pow(cos, 2) * a_ii - 2 * sin * cos * a_ij + pow(sin, 2) * a_jj;
		my_round(mtx[i][i]);

		mtx[j][j] = pow(sin, 2) * a_ii + 2 * sin * cos * a_ij + pow(cos, 2) * a_jj;
		my_round(mtx[j][j]);

		mtx[i][j] = mtx[j][i] = (pow(cos, 2) - pow(sin, 2)) * a_ij + sin * cos * (a_ii - a_jj);
		my_round(mtx[i][j]);
		my_round(mtx[j][i]);

		for (std::size_t k = 0; k < mtx.size(); ++k)
		{
			if (k != i and k != j) {
				double a_ik = mtx[i][k];
				double a_jk = mtx[j][k];
				mtx[i][k] = mtx[k][i] = cos * a_ik - sin * a_jk;
				mtx[j][k] = mtx[k][j] = sin * a_ik + cos * a_jk;

				my_round(mtx[i][k]); my_round(mtx[k][i]);
				my_round(mtx[j][k]); my_round(mtx[k][j]);
			}
		}
	}


	/*
	check_and_update method is doing the following things:
	Convert matrix elemnt that is smaller than TOTAL (almost equal to 0) to be 0.
	Check if the given matrix is diagonal.
	*/
	bool check_and_update(Matrix& matrix) {
		//bool isDiagonalMatrix = true;
		int row = matrix.size();
		int col = matrix[0].size();

		//Check that the given matrix is square matrix
		if (row != col) {
			std::string str = "The given matrix is not square matrix.";
			throw std::invalid_argument(str);
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = i + 1; j < col; j++)
			{
				if (abs(matrix[i][j]) < TOTAL)
					matrix[i][j] = matrix[j][i] = 0;
				else
					return false;
			}
		}
		return true;
	}


	/*
	Jacobi method Implemnt [Jacobi Eigenvalue Algorithm](https://en.wikipedia.org/wiki/Jacobi_eigenvalue_algorithm)
	The method return Eigenvalues and Eigenvectors.
	*/
	std::tuple<Matrix, Vector, int>
		Jacobi(Matrix matrix) {

		//Check that the given matrix is square matrix
		if (matrix.size() != matrix[0].size()) {
			std::string str = "The given matrix is not square matrix.";
			throw std::invalid_argument(str);
		}

		//Initialize of the variables:
		int n = matrix.size();
		Matrix J = eye_matrix(n);

		//Set limit on the number of iterations:
		int max_iterations = 100;
		int cur_iteration_num = 0;

		//for (int i = 0; i < max_iterations; i++)
		while (true)
		{
			//Get matrix max number and his index:
			auto tuple1 = find_max_num(matrix);
			double max_val = std::get<0>(tuple1);
			int p = std::get<1>(tuple1);
			int q = std::get<2>(tuple1);

			if (max_val < TOTAL)
				return std::make_tuple(J, get_diag(matrix), cur_iteration_num);

			//Get rotation matrix and get cos and sin values:
			auto tuple2 = calce_J_matrix(matrix, p, q);
			Matrix J1 = std::get<0>(tuple2);
			double cosinus = std::get<1>(tuple2);
			double sinus = std::get<2>(tuple2);

			//Calculate the new matrix:
			calc_matrix(matrix, cosinus, sinus, p, q);

			//Calculate the eigenvectors:
			J = rotation_product(J, J1, p, q);

			cur_iteration_num++;
			if (check_and_update(matrix) or cur_iteration_num == 3000)
				break;
		}

		//std::cout << "Number of iteration : " << cur_iteration_num << std::endl;
		return std::make_tuple(J, get_diag(matrix), cur_iteration_num);
	}


		/*
		rearrange method remove negative and zero Eigenvalues and their Eigenvectors.
		The method return Sorted list, of Eigenvalues and their Eigenvectors.
		*/
	vector<std::tuple<double, Vector>>
	rearrange(const Matrix& eigenvectors, const Vector& lamdas) {
		//Initialize of the variables:
		vector<std::tuple<double, Vector>> t_vecs;
		bool flag = false;

		for (std::size_t i = 0; i < lamdas.size(); ++i)
		{
			if (lamdas[i] > 0) {
				auto tuple = std::make_tuple(lamdas[i], get_column(eigenvectors, i));
				if (t_vecs.size() == 0)
					t_vecs.push_back(tuple);
				else {
					for (std::size_t j = 0; j < t_vecs.size(); ++j)
					{
						auto tuple1 = t_vecs[j];
						if (std::get<0>(tuple1) <= lamdas[i]) {

							// Create Iterator pointing to the desire place:
							auto itPos = t_vecs.begin() + j;

							// Insert element to the desire position in vector:
							t_vecs.insert(itPos, tuple);
							flag = true;
							break;
						}
					}
					if (not flag)
						t_vecs.push_back(tuple);

					//reinsialize
					flag = false;
				}
			}
		}
		return t_vecs;
	}


	/*
	This method get input matrix and perfome Singular Value Decomposition (SVD).
	*/
	std::tuple<Matrix, Vector, Matrix>
	SVD(const Matrix& input_matrix) {

		//copy constructor
		Matrix AT = input_matrix;
		transpose(AT);

		auto AT_T = dot_product(AT, input_matrix);

		auto tuple1 = Jacobi(AT_T);
		Matrix eigenvectors = std::get<0>(tuple1);
		Vector eigenvalues = std::get<1>(tuple1);


		std::cout << "Eigenvectors = " << std::endl;
		print_matrix(eigenvectors);
		std::cout << "Eigenvalues = " << std::endl;
		print_vec(eigenvalues);

		auto vec = rearrange(eigenvectors, eigenvalues);

		//Build Sigma matrix - contain the Singular Values in descending order on the main diagonal :

		Vector Sigma(vec.size());

		//Build U matrix - (1 / Singular Values) * A * V

		Matrix U;

		//Build V.T matrix - contain the transpose of the eigenvectors.

		Matrix V_T;

		for (int i = 0; i < vec.size(); i++)
		{
			auto tuple2 = vec[i];

			double lamda = std::get<0>(tuple2);
			Vector v1 = std::get<1>(tuple2);

			double s = sqrt(lamda);

			//Create v vector by normalize v1 vectore:
			double vec_norm = vec_length(v1);
			auto v = dot_product(1 / vec_norm, v1);

			//Create u vector by multiply scalar on dot product of input matrix with v vector ==> (1/s)*input_matix*v:
			double scalar = 1 / s;
			Matrix v_t = { v };
			transpose(v_t);

			v_t = dot_product(input_matrix, v_t);
			transpose(v_t);

			auto u = dot_product(scalar, v_t[0]);

			//Insert values to the finale data structures:
			Sigma[i] = s;

			U.push_back({ u });

			V_T.push_back({ v });
		}

		transpose(U);
		//transpose(V_T);

		return std::make_tuple(U, Sigma, V_T);
	}


	/*
	Checking that the U * S * VT is equal to input matrix.
	*/
	void check_decomposition(const Matrix& input_matrix,
	Matrix U, Vector Sigma, Matrix V_T) {

		std::cout << "Examination Of The Decomposition: " << std::endl;
		std::cout << "Inpute Matrix = " << std::endl;
		print_matrix(input_matrix);

		std::cout << std::endl;

		std::cout << "Result Of The 3 Matrix Multiplication From SVD Is:\nU*S*V.t =" << std::endl;

		auto U_Sigma = diag_to_matrix(Sigma, U[0].size());

		auto temp_mtx = diagonal_multiplication(U, U_Sigma);

		auto res = dot_product(temp_mtx, V_T, my_round);

		print_matrix(res);
	}
};