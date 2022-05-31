#ifndef SVD_
#define SVD_

//My header files
#include "../Header/Jacobi.h"
/// <summary>
/// 
/// </summary>
class SVD
{
public:

	//Constructor.
	SVD();

	//Destructor.
	~SVD();

	/*
	This method get input matrix and perform Singular Value Decomposition (SVD).
	*/
	void SVD_alg(const Matrix& input_matrix);

	Vector get_Sigma();

	Matrix get_U();

	Matrix get_V_T();

	/*
	Checking that the U * S * VT is equal to input matrix.
	*/
	void check_decomposition(const Matrix& input_matrix);

private:
	Vector Sigma;
	Matrix U;
	Matrix V_T;
	Jacobi* jacobi;

	void clear_fields();
	void SVD_clc(const Matrix& input_matrix);
};

#endif // !SVD_

