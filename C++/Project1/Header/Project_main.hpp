#ifndef MAIN_
#define MAIN_

//My header files:
#include "Header.h"
#include "Matrix_Operations.h"
#include "Jacobi.h"
#include "QR_Decomposition.h"
#include "SVD.h"
#include "File.h"
#include "Timer.hpp"


using namespace QR_Decomposition_;
using namespace Jacobi_;
using namespace Matrix_Operations_;
using namespace my_timer;

class Project_main
{
public:
	Project_main();
	~Project_main();
	void run_project();

private:
	SVD* SVD_ptr;
	QR_Decomposition* QR_ptr;
	File* File_ptr;

	inline void is_valid();
	inline void valid_size(int& size);
	void get_matrix_input(Matrix& matrix);
};


Project_main::Project_main() : SVD_ptr(new SVD()), QR_ptr(new QR_Decomposition()), File_ptr(new File())
{}

Project_main::~Project_main() {
	delete SVD_ptr;
	delete QR_ptr;
	delete File_ptr;
}

void Project_main::run_project() {

	Matrix matrix;

	int x;

	while (true)
	{
		std::cout
			<< "Press 1 for SVD, \n"
			<< "Press 2 for QR decomposition,"
			<< "\nPress 0 for exit : ";
		std::cin >> x;

		//Check user input.
		is_valid();

		switch (x)
		{
		case 0:
			break;

		case 1:
		{
			std::cout << "\n----------SVD----------" << std::endl;
			get_matrix_input(matrix);

			std::cout << "Input matrix:" << std::endl;
			std::cout << matrix;

			//Start count the time.
			time_type start = start_timer();


			auto tuple1 = SVD_ptr->SVD_alg(matrix);
			Matrix U = std::get<0>(tuple1);
			Vector Sigma = std::get<1>(tuple1);
			Matrix V_T = std::get<2>(tuple1);

			std::cout << "\nSVD:\n\n";
			std::cout << "U = " << std::endl;
			std::cout << U;

			std::cout << "S = " << std::endl;
			std::cout << Sigma;
			std::cout << "V.T = " << std::endl;
			std::cout << V_T;

			SVD_ptr->check_decomposition(matrix, U, Sigma, V_T);

			//Stop count the time.
			end_timer(start);

			break;
		}
		case 2:
		{
			std::cout << "\n----------QR decomposition----------" << std::endl;

			get_matrix_input(matrix);

			std::cout << "Input matrix:" << std::endl;
			std::cout << matrix;

			//Start count the time.
			time_type start = start_timer();

			QR_ptr->QR_decomposition(matrix);

			//Stop count the time.
			end_timer(start);

			break;
		}
		default:
			//The case that user input is out of range.
			std::cout << "\nError Input\n" << std::endl;
		}

		if (x == 0)
			break;
		if (x == 1 or x == 2)
			std::cout << "\n" << std::endl;
	}

}

//Input validation.
inline void Project_main::is_valid() {
	if (std::cin.fail()) {
		std::cerr << "Error Input";
		std::cin.clear();
		exit(0);
	}
};


//Input validation - check if the size of the matrix is valid.
inline void Project_main::valid_size(int& size) {

	while (true)
	{
		std::cin >> size;
		is_valid();
		if (size >= 2)
			break;
		std::cout << "Size of the matrix: ";
	}
}

void Project_main::get_matrix_input(Matrix& matrix) {
	int x;
	bool is_val = false;
	int size;
	


	while (not is_val)
	{
		std::cout << "\nPress 1 for random matrix, \n"
			<< "Press 2 for insert matrix manually : ";
		std::cin >> x;

		switch (x)
		{
		case 1:		//Random matrix:
		{
			std::cout << "Size of the matrix : ";

			//Check the given size.
			valid_size(size);

			matrix = Matrix__Operations::generate_matrix(size);

			//Save the random matrix.
			File_ptr->write_to_file("Input_matrix.txt", matrix);
			is_val = true;
			break;
		}
		case 2:		//User input:
		{
			//Example matrix for user:
			Matrix example{ {1,2,3}, {2,2,4}, {3,4,3} };
			File_ptr->write_to_file("Input_matrix.txt", example);

			std::cout << "Size of the matrix : ";

			//Check the given size.
			valid_size(size);

			std::cout << "Insert " << size << " * " << size << " matrix to Input_matrix.txt " << std::endl;

			int in = 0;
			while (in != 1) {
				std::cout << "Press 1 for finish : ";
				std::cin >> in;
			}

			matrix = File_ptr->read_file("Input_matrix.txt");

			is_val = true;
			break;
		}
		default:		//The case that user input is out of range.
			std::cout << "\nError Input - try again" << std::endl;
		}
	}

	delete File_ptr;
}

#endif // !MAIN_
