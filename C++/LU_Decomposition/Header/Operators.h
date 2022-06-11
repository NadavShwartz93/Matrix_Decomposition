#ifndef OPERATOR_
#define OPERATOR_

#include "Header.h"

namespace Operators
{

	/// <summary>
	/// Print Vector in more simple way.
	/// </summary>
	/// <param name="cout"></param>
	/// <param name="v"></param>
	/// <returns></returns>
	std::ostream& operator<< (std::ostream& cout, const Vector& v);

	/// <summary>
	/// Print Matrix in more simple way.
	/// </summary>
	/// <param name="cout"></param>
	/// <param name="matrix"></param>
	/// <returns></returns>
	std::ostream& operator<< (std::ostream& cout, const Matrix& matrix);

	/// <summary>
	/// This function perform dot product operation between matrix1 and matrix2.
	/// </summary>
	/// <param name="matrix1"></param>
	/// <param name="matrix2"></param>
	/// <returns></returns>
	Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
};

#endif // !OPERATOR_