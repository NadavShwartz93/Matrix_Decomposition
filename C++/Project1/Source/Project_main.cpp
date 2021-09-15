#include<iostream>
#include<vector>
#include<tuple>
#include <string>
#include<chrono>		//for timer

//My header files:

#include "../Header/Matrix_Operations.h"
#include "../Header/Jacobi.h"
#include "../Header/QR_Decomposition.h"


using time_type = std::chrono::time_point<std::chrono::steady_clock>;


//Methods for timer:
namespace my_timer {
	time_type start_timer();
	void end_timer(time_type start);
};


using namespace std;
using namespace my_timer;
using namespace QR_Decomposition;
using namespace Jacobi;
using namespace Matrix_Operations;

inline void is_valid();
inline void valid_size(int& size);
void get_matrix_input(std::vector<std::vector<double>>& matrix);

int main() {

	vector<vector<double>> matrix;

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
			print_matrix(matrix);

			//Start count the time.
			time_type start = start_timer();

			auto tuple1 = SVD(matrix);
			vector<vector<double>> U = std::get<0>(tuple1);
			vector<double> Sigma = std::get<1>(tuple1);
			vector<vector<double>> V_T = std::get<2>(tuple1);

			std::cout << "\nSVD:\n\n";
			std::cout << "U = " << std::endl;
			print_matrix(U);
			std::cout << "S = " << std::endl;
			print_vec(Sigma);
			std::cout << "V.T = " << std::endl;
			print_matrix(V_T);

			check_decomposition(matrix, U, Sigma, V_T);

			//Stop count the time.
			end_timer(start);

			break;
		}
		case 2:
		{
			std::cout << "\n----------QR decomposition----------" << std::endl;

			get_matrix_input(matrix);

			std::cout << "Input matrix:" << std::endl;
			print_matrix(matrix);

			//Start count the time.
			time_type start = start_timer();
			
			QR_decomposition( matrix );

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
	
	system("PAUSE");
	return 0;
}


////Methods for time:
namespace my_timer {
	time_type start_timer() {
		return chrono::steady_clock::now();
	}

	void end_timer(time_type start) {
		//Stop count the time.
		auto end = chrono::steady_clock::now();

		// Store the time difference between start and end
		auto diff = end - start;
		cout << "\nTotal Time Taken = \n";
		cout << chrono::duration <double, milli>(diff).count() << " ms" << endl;
	}
};


//Input validation.
inline void is_valid() {
	if (std::cin.fail()) {
		std::cerr << "Error Input";
		std::cin.clear();
		exit(0);
	}
};

//Input validation - check if the size of the matrix is valid.
inline void valid_size(int& size) {
	
	while (true)
	{
		std::cin >> size;
		is_valid();
		if (size >= 2)
			break;
		std::cout << "Size of the matrix: ";
	}
}

void get_matrix_input(std::vector<std::vector<double>>& matrix) {
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

				matrix = generate_matrix(size);

				//Save the random matrix.
				write_to_file("Input_matrix.txt", matrix);
				is_val = true;
				break;
			}
			case 2:		//User input:
			{
				//Example matrix for user:
				std::vector<std::vector<double>> example { {1,2,3}, {2,2,4}, {3,4,3} };
				write_to_file("Input_matrix.txt", example);

				std::cout << "Size of the matrix : ";

				//Check the given size.
				valid_size(size);

				std::cout << "Insert " << size << " * " << size << " matrix to Input_matrix.txt " << std::endl;

				int in = 0;
				while (in != 1) {
					std::cout << "Press 1 for finish : ";
					std::cin >> in;
				}

				matrix = read_file("Input_matrix.txt");

				is_val = true;
				break;
			}
			default:		//The case that user input is out of range.
				std::cout << "\nError Input - try again" << std::endl;
		}
	}
	
}