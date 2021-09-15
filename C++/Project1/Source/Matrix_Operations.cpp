#include<iostream>
#include <fstream>
#include<vector>
#include <string>
#include <functional>
#include <cstdio>		//for remove file operation
#include <random>		//for generate random numbers

//My header files:
#include "../Header/Matrix_Operations.h"

using namespace std;


namespace Matrix_Operations {

	//Method for print vectors/matrix and for reading input file:

	/*
		print_vec method print the given vector to the console.
	*/
	void print_vec(vector<double>& v) {
		bool flag = false;

		for (std::size_t i = 0; i < v.size(); ++i)
		{
			if (v.size() == 1)
				std::cout << "[" << v[i] << "]" << std::endl;
			else if (i == 0)
				std::cout << "[" << v[i] << ",	";
			else if (i + 1 == v.size())
				std::cout << v[i] << "]" << std::endl;
			else {
				std::cout << v[i] << ",	";

				//The case the given vector is bigger then 10 elements:
				if (i > 2 and v.size() > 10 and not flag) {
					std::cout << "...	";
					i = v.size() - 4;
					flag = true;
				}
			}
		}
	}



	/*
		print_matrix method print the given matrix to the console.
	*/
	void print_matrix(vector<vector<double>>& matrix) {
		bool flag = false;

		for (std::size_t i = 0; i < matrix.size(); ++i)
		{
			if (matrix.size() == 1) {
				std::cout << "[\n ";
				print_vec(matrix[i]);
				std::cout << "]" << std::endl;
			}
			else if (i == 0) {
				std::cout << "[ ";
				print_vec(matrix[i]);
			}
			else if (i + 1 == matrix.size()) {
				std::cout << " ";
				print_vec(matrix[i]);
				std::cout << "] " << std::endl;
			}
			else {
				std::cout << " ";
				print_vec(matrix[i]);

				//The case the given matrix is bigger then 10 elements:
				if (i > 2 and matrix.size() > 10 and not flag) {
					std::cout << " ...	\n";
					i = matrix.size() - 4;
					flag = true;
				}
			}
		}
	}


	/*
		read_file method read the all content from the input file.
		The method return matrix with all the values from the input file.
	*/
	vector<vector<double>> read_file(const std::string& file_name) {
		std::string line;
		fstream newfile;
		vector<vector<double>> matrix;

		newfile.open(file_name, ios::in); //open a file to perform read operation using file object

		if (newfile.is_open()) {   //checking that the file is open

			while (getline(newfile, line)) { //read data from file object and put it into string.
				auto vector = read_line(line);
				matrix.push_back(vector);
			}

			newfile.close(); //close the file object.
		}
		return matrix;
	}


	/*
		read_line method get string value and convert it to vector of double.
	*/
	vector<double> read_line(std::string line) {

		vector<double> v;

		size_t pos = 0;
		std::string delimiter = ",";
		while ((pos = line.find(delimiter)) != std::string::npos) {
			std::string token = line.substr(0, pos);

			double num = std::stod((const std::string&)token);
			v.push_back(num);

			line.erase(0, pos + delimiter.length());
		}

		//Last number in the line do not have comma after it.
		double num = std::stod((const std::string&)line);
		v.push_back(num);

		return v;
	}


	/*
	write_to_file method write the content of the given matrix to the file.
	The method True if succeeded.
	*/
	bool write_to_file(const std::string& file_name, vector<vector<double>>& mtx) {

		int row = mtx.size();
		int col = mtx[0].size();

		//remove the file if exists - string.c_str() convert string to char*
		std::remove(file_name.c_str());

		ofstream myfile;
		myfile.open(file_name, ios::out | ios::app | ios::binary);

		if (myfile.is_open()) {		//ok, proceed with output

			std::string delimiter = ",";
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					if (not(j + 1 < col))		//Case of the last number in the matrix
						myfile << mtx[i][j];
					else
						myfile << mtx[i][j] << ",";
				}
				if (i + 1 < row)
					myfile << "\n";
			}
			myfile.close(); //close the file object.
			return true;
		}
		return false;
	}


	/*
	generate_matrix method randomly generate matrix.
	*/
	vector<vector<double>> generate_matrix(int size) {

		//Initialize parameters:
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> dist(0, 80);


		vector<double> v(size);
		vector<vector<double>> new_matrix(size, v);

		for (int i = 0; i < size; i++)
		{
			for (int j = i; j < size; j++)
			{
				new_matrix[i][j] = new_matrix[j][i] = dist(mt);
			}
		}
		return new_matrix;
	}




	//Matrix Operation Methods:


	/*
		This method return the vetor length.
	*/
	double vec_length(vector<double>& v) {
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
	void transpose(vector<vector<double>>& matrix) {
		vector<vector<double>> new_matrix;
		int row = matrix.size();
		int col = matrix[0].size();

		for (int i = 0; i < col; i++)
		{
			vector<double> v;

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
	vector<vector<double>> dot_product(vector<vector<double>>& matrix1,
		vector<vector<double>> matrix2, std::function<void(double&)> F) {

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
		vector<double> v(row_matrix2_T);
		vector<vector<double>> new_matrix(row_matrix1, v);

		for (int i = 0; i < row_matrix1; i++)
		{
			for (int j = 0; j < row_matrix2_T; j++)
			{
				double num = dot_product(matrix1[i], matrix2[j], F);
				new_matrix[i][j] = num;
			}
		}

		return new_matrix;
	}

	/*
		dot_product method return the result of the multiplication between vector1 and vector2.
	*/
	double dot_product(vector<double>& v1, vector<double>& v2, std::function<void(double&)> F) {
		int n;

		if ((n = v1.size()) != v2.size()) {
			std::string str = "vectors are not in the same size.";
			throw std::invalid_argument(str);
		}

		double sum = 0;
		for (int i = 0; i < n; i++)
			sum += (v1[i] * v2[i]);

		if (F != nullptr)
			F(sum);


		return sum;
	}


	/*
		dot_product method return the result of the multiplication between given scalar and vector.
	*/
	vector<double> dot_product(double scalar, vector<double>& v) {

		for (std::size_t i = 0; i < v.size(); ++i)
		{
			v[i] = scalar * v[i];
		}
		return v;
	}


	/*
		rotation_product method execute matrix multiplication of regular matrix and rotation matrix.
	*/
	vector<vector<double>> rotation_product(vector<vector<double>>& matrix,
		vector<vector<double>> rotation, int p, int q) {
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
					index_ip = dot_product(matrix[i], rotation[p]);
				else
					index_iq = dot_product(matrix[i], rotation[q]);
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
	vector<vector<double>> diagonal_multiplication(vector<vector<double>>& matrix,
		vector<vector<double>>& diagonal) {
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
	vector<vector<double>> eye_matrix(int n) {
		//pre-allocation of the vector size:
		vector<double> v(n, 0.0);
		vector<vector<double>> I(n, v);

		for (int i = 0; i < n; i++)
			I[i][i] = 1.0;

		return I;
	}


	/*
		get_diag method return vector that contains the elements that on the matrix diagonal.
	*/
	vector<double> get_diag(vector<vector<double>>& matrix) {
		int row = matrix.size();
		int col = matrix[0].size();

		//Check that the given matrix is square matrix
		if (row != col) {
			std::string str = "The given matrix is not square matrix.";
			throw std::invalid_argument(str);
		}

		//pre-allocation of the vector size: 
		vector<double> diagonal(row);

		for (int i = 0; i < row; i++)
		{
			diagonal[i] = matrix[i][i];
		}
		return diagonal;
	}


	/*
		diag_to_matrix method convert a vector to diagonal matrix in size size_val value.
	*/
	vector<vector<double>> diag_to_matrix(vector<double>& diagonal, int size_val) {
		int n = diagonal.size();

		//The case that the desire matrix size is smaller than 
		// the amount of elements in diagonal vectors.
		if (n > size_val) {
			std::string str = "The desire matrix size is smaller than the amount of elements in diagonal vectors";
			throw std::invalid_argument(str);
		}

		//pre-allocation of the vector size:
		vector<double> v(size_val, 0);
		vector<vector<double>> new_matrix(size_val, v);

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
	vector<double> get_column(vector<vector<double>>& matrix, int column) {

		//Check that the given column number is not out of range.
		if (matrix[0].size() < column) {
			std::string str = "The given matrix do not have column number " + std::to_string(column) + ".";
			throw std::invalid_argument(str);
		}

		int n = matrix.size();
		//pre-allocation of the vector size: 
		vector<double> v(n);

		for (int i = 0; i < n; i++)
		{
			v[i] = matrix[i][column];
		}
		return v;
	}


	/*
		This method return a copy of the array collapsed into one dimension.
	*/
	vector<double> flatten(vector<vector<double>>& matrix) {
		int row = matrix.size();
		int col = matrix[0].size();

		vector<double> flat_vector;

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
	void my_round(double& num) {
		if (std::abs(num) < TOTAL)
			num = 0;
	}

};
