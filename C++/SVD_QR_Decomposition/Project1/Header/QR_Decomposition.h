#ifndef QR_DECOMPOSITION
#define QR_DECOMPOSITION

#include "Header.h"
#include "Operators.h"
#include "Matrix_Operations.h"
using namespace Operators;
using namespace Matrix_Operations_;


namespace QR_Decomposition_ {
	/// <summary>
	/// 
	/// </summary>
	class QR_Decomposition : public Matrix__Operations
	{
	public:

		/*
		For giveen matrix A[a1,a2,...,an] in size n x n
		Execute Gram Schmidt process, and return new matrix.
	*/
		Matrix Gram_Schmidt_process(Matrix matrix);


		/*
			Q is an orthogonal matrix, that created by normalize
			the columns of the matrix that has been received
			from Gram Schmidt process.
		*/
		Matrix Q_matrix(Matrix U);


		/*
			R is an upper triangular matrix.
			R produce by multiplication of Q transpose and input_matrix.
		*/
		Matrix R_matrix(Matrix input_matrix, Matrix Q);


		/*
			Calculation of QR decomposition of the given matrix.
		*/
		void QR_decomposition(const Matrix& input_matrix);


	private:

		/*
			Checking that the Q * R is equal to input matrix.
		*/
		void check_decomposition(const Matrix& Q,
			const Matrix& R);


		/*
		Execute projection operation between two vectors.
		*/
		inline Vector projection(Vector u, Vector v1);
	};
	
};

#endif // !QR_DECOMPOSITION