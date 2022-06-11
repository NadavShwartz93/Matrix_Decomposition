#ifndef FILE_
#define FILE_

#include "Header.h"
#include "Operators.h"
using namespace Operators;

class File
{
public:

	//Method for print vectors/matrix and for read/write input file:

	/// <summary>
	/// print_vec method print the given vector to the console.
	/// </summary>
	/// <param name="v"></param>
	void print_vec(const Vector& v);


	/// <summary>
	/// print_matrix method print the given matrix to the console.
	/// </summary>
	/// <param name="matrix"></param>
	void print_matrix(const Matrix& matrix);


	/// <summary>
	/// read_file method read the all content from the input file.
	/// The method return matrix with all the values from the input file.
	/// </summary>
	/// <param name="file_name"></param>
	/// <param name="matrix"></param>
	void read_file(const std::string& file_name, Matrix& matrix);

private:

	/// <summary>
	/// read_line method get string value and convert it to vector of double.
	/// </summary>
	/// <param name="line"></param>
	/// <returns></returns>
	Vector read_line(std::string line);

};


#endif // !FILE_
