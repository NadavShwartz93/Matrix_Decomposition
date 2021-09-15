#ifndef JACOBI_SVD
#define JACOBI_SVD


using namespace std;


//Method for Jacobi Eigenvalue Algorithm:

namespace Jacobi {

	/*
		find_max_num method find the largest off-diagonal element, and return his index and value.
		The given matrix is symmetric, so only need to search in the upper triangular matrix.
	*/
	tuple<double, int, int> find_max_num(vector<vector<double>>& matrix);


	/*
		calce_J_matrix method find the rotation matrix that called J:
	*/
	tuple<vector<vector<double>>, double, double> calce_J_matrix(
		vector<vector<double>>& matrix, int p, int q);


	/*
		For make the performention of Jacobi Eigenvalue Algorithm better,
		matrix multiplication of J.T*A*J is replaced by some elementary operations.
		And then, the all function is O(n) instead of O(n^2).
	*/
	void calc_matrix(vector<vector<double>>& mtx, double cos, double sin, int i, int j);


	/*
		check_and_update method is doing the following things:
		Convert matrix elemnt that is smaller than TOTAL (almost equal to 0) to be 0.
		Check if the given matrix is diagonal.
	*/
	bool check_and_update(vector<vector<double>>& matrix);


	/*
		Jacobi method Implemnt [Jacobi Eigenvalue Algorithm](https://en.wikipedia.org/wiki/Jacobi_eigenvalue_algorithm)
		The method return Eigenvalues and Eigenvectors.
	*/
	std::tuple<vector<vector<double>>, vector<double>, int>
		Jacobi(vector<vector<double>> matrix);


	/*
		rearrange method remove negative and zero Eigenvalues and their Eigenvectors.
		The method return Sorted list, of Eigenvalues and their Eigenvectors.
	*/
	vector<std::tuple<double, vector<double>>>
		rearrange(vector<vector<double>>& eigenvectors, vector<double>& lamdas);


	/*
		This method get input matrix and perfome Singular Value Decomposition (SVD).
	*/
	std::tuple<vector<vector<double>>, vector<double>, vector<vector<double>>>
		SVD(vector<vector<double>>& input_matrix);


	/*
		Checking that the U * S * VT is equal to input matrix.
	*/
	void check_decomposition(vector<vector<double>>& input_matrix,
		vector<vector<double>> U, vector<double> Sigma, vector<vector<double>> V_T);


};
#endif // !JACOBI_SVD