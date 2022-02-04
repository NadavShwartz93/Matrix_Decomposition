#ifndef FILE_
#define FILE_
#include "Operators.h"

using namespace Operators;

class File
{
public:

	//Method for print vectors/matrix and for read/write input file:

	/*
		print_vec method print the given vector to the console.
	*/
	void print_vec(const Vector& v);


	/*
		print_matrix method print the given matrix to the console.
	*/
	void print_matrix(const Matrix& matrix);


	/*
		read_file method read the all content from the input file.
		The method return matrix with all the values from the input file.
	*/
	Matrix read_file(const std::string& file_name);


	/*
		read_line method get string value and convert it to vector of double.
	*/
	Vector read_line(std::string line);


	/*
	write_to_file method write the content of the given matrix to the file.
	The method return True if succeeded.
	*/
	bool write_to_file(const std::string& file_name, const Matrix& mtx);


private:

};


#endif // !FILE_
