//My header files:

#include "../Header/Header.h"
#include "../Header/Matrix_Operations.h"
#include "../Header/Jacobi.h"
#include "../Header/QR_Decomposition.h"
#include "../Header/SVD.h"
#include "../Header/File.h"
#include "../Header/Timer.hpp"


using namespace QR_Decomposition_;
using namespace Matrix_Operations_;
using namespace my_timer;

/// <summary>
/// 
/// </summary>
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
	inline void clear_matrix(Matrix& matrix);
};


Project_main::Project_main() : SVD_ptr(new SVD()), QR_ptr(new QR_Decomposition()), File_ptr(new File())
{}

Project_main::~Project_main() {
	delete SVD_ptr;
	delete QR_ptr;
	delete File_ptr;

	std::cout << "Delete SVD' Class Pointer" << std::endl;
	std::cout << "Delete File' Class' Pointer." << std::endl;
	std::cout << "Delete File' QR' Pointer." << std::endl;
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

			SVD_ptr->SVD_alg(matrix);
			Matrix U = SVD_ptr->get_U();
			Vector Sigma = SVD_ptr->get_Sigma();
			Matrix V_T = SVD_ptr->get_V_T();


			std::cout << "\nSVD:\n\n";
			std::cout << "U = " << std::endl;
			std::cout << U;

			std::cout << "S = " << std::endl;
			std::cout << Sigma;
			std::cout << "V.T = " << std::endl;
			std::cout << V_T;

			SVD_ptr->check_decomposition(matrix);

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


void Project_main::get_matrix_input(Matrix& matrix) {
	int x;
	bool is_val = false;
	int size;

	clear_matrix(matrix);

	while (not is_val)
	{
		std::cout << "\nPress 1 for random matrix, \n"
			<< "Press 2 for insert matrix manually : ";
		std::cin >> x;

		is_valid();

		switch (x)
		{
		case 1:		//Random matrix:
		{
			std::cout << "Size of the matrix : ";

			//Check the given size.
			valid_size(size);

			Matrix__Operations::generate_matrix(size, matrix);

			//Save the random matrix.
			File_ptr->write_to_file("Input_matrix.txt", matrix);
			is_val = true;
			break;
		}
		case 2:		//User input:
		{
			std::cout << "Insert matrix to Input_matrix.txt file" << std::endl;
			int in = 0;
			while (in != 1) {
				std::cout << "Press 1 for finish : ";
				std::cin >> in;
			}

			File_ptr->read_file("Input_matrix.txt", matrix);

			is_val = true;
			break;
		}
		default:		//The case that user input is out of range.
			std::cout << "\nError Input - try again" << std::endl;
		}
	}
}


//Input validation.
inline void Project_main::is_valid() {
	if (std::cin.fail()) {
		std::cerr << "Error Input" << std::endl;
		std::cin.clear();
		delete this;
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


inline void Project_main::clear_matrix(Matrix& matrix)
{
	matrix.erase(matrix.begin(), matrix.end());
	matrix.resize(0);
}


int main() {


	Project_main* runner = new Project_main();

	runner->run_project();

	delete runner;
	system("PAUSE");

	return 0;
}