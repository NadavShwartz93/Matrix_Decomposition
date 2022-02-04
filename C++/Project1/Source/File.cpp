#include "../Header/File.h"


/*
	print_vec method print the given vector to the console.
*/
void File::print_vec(const Vector& v) {
	std::cout << v;
}


/*
	print_matrix method print the given matrix to the console.
*/
void File::print_matrix(const Matrix& matrix) {
	std::cout << matrix;
}


/*
	read_file method read the all content from the input file.
	The method return matrix with all the values from the input file.
*/
Matrix File::read_file(const std::string& file_name) {
	std::string line;
	fstream newfile;
	Matrix matrix;

	newfile.open(file_name, ios::in); //open a file to perform read operation using file object

	if (newfile.is_open()) {   //checking that the file is open

		while (getline(newfile, line)) { //read data from file object and put it into string.
			auto vector = read_line(line);
			matrix.push_back(vector);
		}

		newfile.close(); //close the file object.
	}
	return matrix;
}

/*
	read_line method get string value and convert it to vector of double.
*/
Vector File::read_line(std::string line) {
	Vector v;

	size_t pos = 0;
	std::string delimiter = ",";
	while ((pos = line.find(delimiter)) != std::string::npos) {
		std::string token = line.substr(0, pos);

		double num = std::stod((const std::string&)token);
		v.push_back(num);

		line.erase(0, pos + delimiter.length());
	}

	//Last number in the line do not have comma after it.
	double num = std::stod((const std::string&)line);
	v.push_back(num);

	return v;
}


/*
	write_to_file method write the content of the given matrix to the file.
	The method True if succeeded.
*/
bool File::write_to_file(const std::string& file_name, const Matrix& mtx) {

	//remove the file if exists - string.c_str() convert string to char*
	std::remove(file_name.c_str());

	ofstream myfile;
	myfile.open(file_name, ios::out | ios::app | ios::binary);

	if (myfile.is_open()) {		//ok, proceed with output

		myfile << mtx;

		myfile.close(); //close the file object.
		return true;
	}
	return false;
}