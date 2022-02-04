#ifndef SVD_
#define SVD_

//My header files
#include "../Header/Jacobi.h"

class SVD : public Jacobi_::Jacobi
{
public:

	/*
	This method get input matrix and perfome Singular Value Decomposition (SVD).
	*/
	std::tuple<Matrix, Vector, Matrix> SVD_alg(const Matrix& input_matrix);

	/*
	Checking that the U * S * VT is equal to input matrix.
	*/
	void check_decomposition(const Matrix& input_matrix,
		Matrix U, Vector Sigma, Matrix V_T);

private:
	std::tuple<Matrix, Vector, Matrix> SVD_clc(const Matrix& input_matrix);
};

#endif // !SVD_

