#ifndef JACOBI_SVD
#define JACOBI_SVD

#include "Matrix_Operations.h"
#include "Header.h"
#include "Operators.h"
using namespace Operators;
using namespace Matrix_Operations_;

//Method for Jacobi Eigenvalue Algorithm:

namespace Jacobi_ {

	class Jacobi : public Matrix__Operations
	{
	public:

		/*
			Jacobi method Implemnt [Jacobi Eigenvalue Algorithm](https://en.wikipedia.org/wiki/Jacobi_eigenvalue_algorithm)
			The method return Eigenvalues and Eigenvectors.
		*/
		std::tuple<Matrix, Vector, int> Jacobi_alg(Matrix matrix);


		/*
			rearrange method remove negative and zero Eigenvalues and their Eigenvectors.
			The method return Sorted list, of Eigenvalues and their Eigenvectors.
		*/
		vector<std::tuple<double, Vector>> rearrange(const Matrix& eigenvectors, const Vector& lamdas);

		/*
		find_max_num method find the largest off-diagonal element, and return his index and value.
		The given matrix is symmetric, so only need to search in the upper triangular matrix.
		*/
		tuple<double, int, int> find_max_num(const Matrix& matrix);


		/*
			calce_J_matrix method find the rotation matrix that called J:
		*/
		tuple<Matrix, double, double> calce_J_matrix(
			const Matrix& matrix, int p, int q);


		/*
			For make the performention of Jacobi Eigenvalue Algorithm better,
			matrix multiplication of J.T*A*J is replaced by some elementary operations.
			And then, the all function is O(n) instead of O(n^2).
		*/
		void calc_matrix(Matrix& mtx, double cos, double sin, int i, int j);


		/*
			check_and_update method is doing the following things:
			Convert matrix elemnt that is smaller than TOTAL (almost equal to 0) to be 0.
			Check if the given matrix is diagonal.
		*/
		bool check_and_update(Matrix& matrix);

	private:
	};

};
#endif // !JACOBI_SVD