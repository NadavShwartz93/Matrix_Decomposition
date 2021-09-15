#ifndef QR_DECOMPOSITION
#define QR_DECOMPOSITION

using namespace std;

namespace QR_Decomposition {

	/*
		For giveen matrix A[a1,a2,...,an] in size n x n
		Execute Gram Schmidt process, and return new matrix.
	*/
	vector<vector<double>> Gram_Schmidt_process(vector<vector<double>> matrix);


	/*
		Q is an orthogonal matrix, that created by normalize
		the columns of the matrix that has been received
		from Gram Schmidt process.
	*/
	vector<vector<double>> Q_matrix(vector<vector<double>> U);


	/*
		R is an upper triangular matrix.
		R produce by multiplication of Q transpose and input_matrix.
	*/
	vector<vector<double>> R_matrix(vector<vector<double>> input_matrix, vector<vector<double>> Q);


	/*
		Calculation of QR decomposition of the given matrix.
	*/
	void QR_decomposition(const vector<vector<double>>& input_matrix);


	/*
		Checking that the Q * R is equal to input matrix.
	*/
	void check_decomposition(vector<vector<double>>& Q, 
		vector<vector<double>>& R);

};

#endif // !QR_DECOMPOSITION