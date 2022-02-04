#ifndef MATRIX_OPERATIONS
#define MATRIX_OPERATIONS

#include "Header.h"
#include "Operators.h"
using namespace Operators;


namespace Matrix_Operations_ {

	//This class contain methods for Matrix Operation:
	class Matrix__Operations 
	{
	public:

		/*
		generate_matrix method randomly generate matrix.
		*/
		static Matrix generate_matrix(int size);

		/*
			This method return the vetor length.
		*/
		double vec_length(const Vector& v);


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
		void transpose(Matrix& matrix);

		/*
			dot_product method perform matrix multiplication, and return the result.
		*/
		Matrix dot_product
		(const Matrix& matrix1, Matrix matrix2, bool check = false);


		/*
			dot_product method return the result of the multiplication between vector1 and vector2.
		*/
		double dot_product(const Vector& v1, const Vector& v2,
			bool check = false);


		/*
			dot_product method return the result of the multiplication between given scalar and vector.
		*/
		Vector dot_product(double scalar, Vector& v);


		/*
			rotation_product method execute matrix multiplication of regular matrix and rotation matrix.
		*/
		Matrix rotation_product(Matrix& matrix,
			Matrix rotation, int p, int q);


		/*
			diagonal_multiplication method execute matrix multiplication of regular matrix
			and diagonal matrix.
		*/
		Matrix diagonal_multiplication(Matrix& matrix,
			const Matrix& diagonal);


		/*
			eye_matrix method return the identity matrix of size n.
		*/
		Matrix eye_matrix(int n);


		/*
			get_diag method return vector that contains the elements that on the matrix diagonal.
		*/
		Vector get_diagonal_matrix(const Matrix& matrix);


		/*
			diag_to_matrix method convert a vector to diagonal matrix in size size_val value.
		*/
		Matrix diagonal_to_matrix(const Vector& diagonal, int size_val);


		/*
			get_column method get matrix and column. The method rturn vector
			with the elements of this matrix's column.
		*/
		Vector get_column(const Matrix& matrix, int column);


		/*
			This method return a copy of the array collapsed into one dimension.
		*/
		Vector flatten(const Matrix& matrix);


	private:

	};

	
};
#endif // !MATRIX_OPERATIONS
