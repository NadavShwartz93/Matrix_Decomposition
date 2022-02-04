#ifndef OPERATOR_
#define OPERATOR_

#include "Header.h"


using namespace std;

namespace Operators
{
	/*
	Print Vector in more simple way.
	*/
	std::ostream& operator<< (std::ostream& cout, const Vector& v);

	/*
	Print Matrix in more simple way.
	*/
	std::ostream& operator<< (std::ostream& cout, const Matrix& matrix);

	/*
	Write Matrix to file in more elegant way.
	*/
	std::ofstream& operator<< (std::ofstream& of, const Matrix& mtx);


	/*
		dot_product operation between given scalar and vector.
	*/
	Vector operator*(double scalar, Vector& v);

	/*
		dot_product between vector1 and vector2.
	*/
	double operator*(const Vector& v1, const Vector& v2);

	/*
	Execute subtraction operation between two 1D vectors.
	*/
	Vector operator-(Vector v1, Vector v2);

};


#endif // !OPERATOR_

