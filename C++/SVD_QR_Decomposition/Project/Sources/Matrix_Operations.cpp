//My header files:
#include "../Headers/Header.h"
#include "../Headers/Matrix_Operations.h"


namespace Matrix_Operations_ {

	//Method for print vectors/matrix and for reading input file:

	
	/*
	generate_matrix method randomly generate matrix.
	*/
	void Matrix__Operations::generate_matrix(int size, Matrix& new_matrix) {

		//Initialize parameters:
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0, 80);


		Vector v (size);
		Matrix mtx(size, v);
		new_matrix = mtx;

		for (int i = 0; i < size; i++)
		{
			for (int j = i; j < size; j++)
			{
				new_matrix[i][j] = new_matrix[j][i] = dist(mt);
			}
		}
		
	}


	//Matrix Operation Methods:


	/*
		This method return the vetor length.
	*/
	double Matrix__Operations::vec_length(const Vector& v) {
		double sum = 0;
		for (auto& num : v) {
			sum += pow(num, 2);
		}

		return sqrt(sum);
	}


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
	void Matrix__Operations::transpose(Matrix& matrix) {
		Matrix new_matrix;
		int row = matrix.size();
		int col = matrix[0].size();

		for (int i = 0; i < col; i++)
		{
			Vector v;

			for (int j = 0; j < row; j++)
			{
				v.push_back(matrix[j][i]);
			}

			new_matrix.push_back(v);
		}

		matrix = new_matrix;
	}


	/*
		dot_product method perform matrix multiplication, and return the result.
	*/
	Matrix Matrix__Operations::dot_product(const Matrix& matrix1,
		Matrix matrix2, bool check) {

		int row_matrix1 = matrix1.size();
		int col_matrix1 = matrix1[0].size();
		int row_matrix2 = matrix2.size();
		int col_matrix2 = matrix2[0].size();

		//The case that  matrix multiplication isn't define.
		if (col_matrix1 != row_matrix2) {
			std::string str = "Cann't multiply (" +
				std::to_string(row_matrix1) + ", " + std::to_string(col_matrix1) +
				") by (" + std::to_string(row_matrix2) + ", " + std::to_string(col_matrix2) + ").";
			std::cout << str << std::endl;
			throw std::invalid_argument(str);
		}

		//performe transpose to matrix2 
		transpose(matrix2);
		int row_matrix2_T = matrix2.size();

		//pre-allocation of the vector size:
		Vector v(row_matrix2_T);
		Matrix new_matrix(row_matrix1, v);

		for (int i = 0; i < row_matrix1; i++)
		{
			for (int j = 0; j < row_matrix2_T; j++)
			{
				double num = dot_product(matrix1[i], matrix2[j], check);
				new_matrix[i][j] = num;
			}
		}

		return new_matrix;
	}


	/*
		dot_product method return the result of the multiplication between vector1 and vector2.
	*/
	double Matrix__Operations::dot_product(const Vector& v1, const Vector& v2, bool check) {
		int n;

		if ((n = v1.size()) != v2.size()) {
			std::string str = "vectors are not in the same size.";
			throw std::invalid_argument(str);
		}

		double sum = 0;
		for (int i = 0; i < n; i++)
			sum += (v1[i] * v2[i]);

		if (check)
			my_round<double>(sum);


		return sum;
	}


	/*
		dot_product method return the result of the multiplication between given scalar and vector.
	*/
	Vector Matrix__Operations::dot_product(double scalar, Vector& v) {
		return scalar * v;
	}


	/*
		rotation_product method execute matrix multiplication of regular matrix and rotation matrix.
	*/
	Matrix Matrix__Operations::rotation_product(Matrix& matrix,
		Matrix rotation, int p, int q) {
		int row_matrix = matrix.size();
		int col_matrix = matrix[0].size();
		int row_rotation = rotation.size();
		int col_rotation = rotation[0].size();


		//The case that  matrix multiplication isn't define.
		if (col_matrix != row_rotation) {
			std::string str = "Cann't multiply (" +
				std::to_string(row_matrix) + ", " + std::to_string(col_matrix) +
				") by (" + std::to_string(row_rotation) + ", " + std::to_string(col_rotation) + ").";
			throw std::invalid_argument(str);
		}

		//performe transpose to matrix2 
		transpose(rotation);

		//changes is only have to apply in 2 matrix's columns only - columns p and q.
		const int inner_iteration = 2;

		for (int i = 0; i < row_matrix; i++)
		{
			double index_ip;
			double index_iq;
			for (int j = 0; j < inner_iteration; j++)
			{
				if (j == 0)
					index_ip = matrix[i] * rotation[p];
				//index_ip = dot_product(matrix[i], rotation[p]);
				else
					index_iq = matrix[i] * rotation[q];
					//index_iq = dot_product(matrix[i], rotation[q]);
			}
			matrix[i][p] = index_ip;
			matrix[i][q] = index_iq;
		}
		return matrix;
	}


	/*
		diagonal_multiplication method execute matrix multiplication of regular matrix
		and diagonal matrix.
	*/
	Matrix Matrix__Operations::diagonal_multiplication(Matrix& matrix,
		const Matrix& diagonal) {
		int row_matrix = matrix.size();
		int col_matrix = matrix[0].size();
		int row_diagonal = diagonal.size();
		int col_diagonal = diagonal[0].size();


		//The case that  matrix multiplication isn't define.
		if (col_matrix != row_diagonal) {
			std::string str = "Cann't multiply (" +
				std::to_string(row_matrix) + ", " + std::to_string(col_matrix) +
				") by (" + std::to_string(row_diagonal) + ", " + std::to_string(col_diagonal) + ").";
			throw std::invalid_argument(str);
		}

		for (int i = 0; i < row_matrix; i++)
		{
			for (int j = 0; j < row_diagonal; j++)
				matrix[i][j] = matrix[i][j] * diagonal[j][j];
		}
		return matrix;
	}


	/*
		eye_matrix method return the identity matrix of size n.
	*/
	Matrix Matrix__Operations::eye_matrix(int n) {
		//pre-allocation of the vector size:
		Vector v(n, 0.0);
		Matrix I(n, v);

		for (int i = 0; i < n; i++)
			I[i][i] = 1.0;

		return I;
	}


	/*
		get_diag method return vector that contains the elements that on the matrix diagonal.
	*/
	Vector Matrix__Operations::get_diagonal_matrix(const Matrix& matrix) {
		int row = matrix.size();
		int col = matrix[0].size();

		//Check that the given matrix is square matrix
		if (row != col) {
			std::string str = "The given matrix is not square matrix.";
			throw std::invalid_argument(str);
		}

		//pre-allocation of the vector size: 
		Vector diagonal(row);

		for (int i = 0; i < row; i++)
		{
			diagonal[i] = matrix[i][i];
		}
		return diagonal;
	}


	/*
		diag_to_matrix method convert a vector to diagonal matrix in size size_val value.
	*/
	Matrix Matrix__Operations::diagonal_to_matrix(const Vector& diagonal, int size_val) {
		int n = diagonal.size();

		//The case that the desire matrix size is smaller than 
		// the amount of elements in diagonal vectors.
		if (n > size_val) {
			std::string str = "The desire matrix size is smaller than the amount of elements in diagonal vectors";
			throw std::invalid_argument(str);
		}

		//pre-allocation of the vector size:
		Vector v(size_val, 0);
		Matrix new_matrix(size_val, v);

		for (int i = 0; i < n; i++)
		{
			new_matrix[i][i] = diagonal[i];
		}

		return new_matrix;
	}


	/*
		get_column method get matrix and column. The method rturn vector
		with the elements of this matrix's column.
	*/
	Vector Matrix__Operations::get_column(const Matrix& matrix, int column) {

		//Check that the given column number is not out of range.
		if (matrix[0].size() < column) {
			std::string str = "The given matrix do not have column number " + std::to_string(column) + ".";
			throw std::invalid_argument(str);
		}

		int n = matrix.size();
		//pre-allocation of the vector size: 
		Vector v(n);

		for (int i = 0; i < n; i++)
		{
			v[i] = matrix[i][column];
		}
		return v;
	}


	/*
		This method return a copy of the array collapsed into one dimension.
	*/
	Vector Matrix__Operations::flatten(const Matrix& matrix) {
		int row = matrix.size();
		int col = matrix[0].size();

		Vector flat_vector;

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				flat_vector.push_back(matrix[i][j]);
			}
		}
		return flat_vector;
	}


	/*
		my_round check if num is smaller than TOTAL value. If so, then num become zero.
	*/
	/*void Mtx_Operations::my_round(double& num) {
		if (std::abs(num) < TOTAL)
			num = 0;
	}*/

};
