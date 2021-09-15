#ifndef MATRIX_OPERATIONS
#define MATRIX_OPERATIONS

//Constants
#define PI 3.14159265358979323846   // pi
#define TOTAL 1.0e-9

#include <functional>

using namespace std;

namespace Matrix_Operations {

	//Method for print vectors/matrix and for reading input file:

/*
	print_vec method print the given vector to the console.
*/
	void print_vec(vector<double>& v);


	/*
		print_matrix method print the given matrix to the console.
	*/
	void print_matrix(vector<vector<double>>& matrix);


	/*
		read_file method read the all content from the input file.
		The method return matrix with all the values from the input file.
	*/
	vector<vector<double>> read_file(const std::string& file_name);


	/*
		read_line method get string value and convert it to vector of double.
	*/
	vector<double> read_line(std::string line);


	/*
	write_to_file method write the content of the given matrix to the file.
	The method True if succeeded.
	*/
	bool write_to_file(const std::string& file_name, vector<vector<double>>& mtx);


	/*
	generate_matrix method randomly generate matrix.
	*/
	vector<vector<double>> generate_matrix(int size);

	//Methods for Matrix Operation:

	/*
		This method return the vetor length.
	*/
	double vec_length(vector<double>& v);


	/*
	This method performe the matrix transpose operation.
	Before transpose operation:
	{ {1.2,3.4,4},
	  {3,4,5.5},
	  {2.2, 5, 6}
	 }

	 After transpose operation:
	 { {1.2, 3, 2.2},
	   {3.4, 4, 5},
	   {4, 5.5, 6}
	 }
	*/
	void transpose(vector<vector<double>>& matrix);


	/*
		dot_product method perform matrix multiplication, and return the result.
	*/
	vector<vector<double>> dot_product
	(vector<vector<double>>& matrix1, vector<vector<double>> matrix2,
		std::function<void(double&)> F = nullptr);


	/*
		dot_product method return the result of the multiplication between vector1 and vector2.
	*/
	double dot_product(vector<double>& v1, vector<double>& v2, std::function<void(double&)> F = nullptr);


	/*
		dot_product method return the result of the multiplication between given scalar and vector.
	*/
	vector<double> dot_product(double scalar, vector<double>& v);


	/*
		rotation_product method execute matrix multiplication of regular matrix and rotation matrix.
	*/
	vector<vector<double>> rotation_product(vector<vector<double>>& matrix,
		vector<vector<double>> rotation, int p, int q);


	/*
		diagonal_multiplication method execute matrix multiplication of regular matrix
		and diagonal matrix.
	*/
	vector<vector<double>> diagonal_multiplication(vector<vector<double>>& matrix,
		vector<vector<double>>& diagonal);


	/*
		eye_matrix method return the identity matrix of size n.
	*/
	vector<vector<double>> eye_matrix(int n);


	/*
		get_diag method return vector that contains the elements that on the matrix diagonal.
	*/
	vector<double> get_diag(vector<vector<double>>& matrix);


	/*
		diag_to_matrix method convert a vector to diagonal matrix in size size_val value.
	*/
	vector<vector<double>> diag_to_matrix(vector<double>& diagonal, int size_val);


	/*
		get_column method get matrix and column. The method rturn vector
		with the elements of this matrix's column.
	*/
	vector<double> get_column(vector<vector<double>>& matrix, int column);


	/*
		This method return a copy of the array collapsed into one dimension.
	*/
	vector<double> flatten(vector<vector<double>>& matrix);


	/*
		my_round check if num is smaller than TOTAL value. If so, then num become zero.
	*/
	void my_round(double& num);

};
#endif // !MATRIX_OPERATIONS
