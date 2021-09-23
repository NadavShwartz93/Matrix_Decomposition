#ifndef QR_DECOMPOSITION
#define QR_DECOMPOSITION

using namespace std;

namespace QR_Decomposition {

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


	/*
		Checking that the Q * R is equal to input matrix.
	*/
	void check_decomposition(const Matrix& Q,
		const Matrix& R);

};

#endif // !QR_DECOMPOSITION