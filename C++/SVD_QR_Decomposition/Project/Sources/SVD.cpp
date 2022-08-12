#include "../Headers/SVD.h"

SVD::SVD()
{
	this->jacobi = new Jacobi();
}


SVD::~SVD()
{
	delete jacobi;
	std::cout << "Delete Jacobi' Class Pointer." << std::endl;
}


void SVD::SVD_alg(const Matrix& input_matrix) {
	clear_fields();
	SVD_clc(input_matrix);
}

Vector SVD::get_Sigma()
{
	return this->Sigma;
}

Matrix SVD::get_U()
{
	return this->U;
}

Matrix SVD::get_V_T()
{
	return this->V_T;
}

void SVD::clear_fields()
{
	Sigma.erase(Sigma.begin(), Sigma.end());
	U.erase(U.begin(), U.end());
	V_T.erase(V_T.begin(), V_T.end());
}

/*
	This method get input matrix and perform Singular Value Decomposition (SVD).
*/
void SVD::SVD_clc(const Matrix& input_matrix) {

	//copy constructor
	Matrix AT = input_matrix;

	this->jacobi->transpose(AT);

	auto AT_T = this->jacobi->dot_product(AT, input_matrix);

	auto tuple1 = this->jacobi->Jacobi_alg(AT_T);
	Matrix eigenvectors = std::get<0>(tuple1);
	Vector eigenvalues = std::get<1>(tuple1);


	std::cout << "Eigenvectors = " << std::endl;
	std::cout << eigenvectors;

	std::cout << "Eigenvalues = " << std::endl;
	std::cout << eigenvalues;


	auto vec = this->jacobi->rearrange(eigenvectors, eigenvalues);

	//Build Sigma matrix - contain the Singular Values in descending order on the main diagonal :

	//Build U matrix - (1 / Singular Values) * A * V

	//Build V.T matrix - contain the transpose of the eigenvectors.

	for (int i = 0; i < vec.size(); i++)
	{
		auto tuple2 = vec[i];

		double lamda = std::get<0>(tuple2);
		Vector v1 = std::get<1>(tuple2);

		double s = sqrt(lamda);

		//Create v vector by normalize v1 vector:
		double vec_norm = this->jacobi->vec_length(v1);
		auto v = this->jacobi->dot_product(1 / vec_norm, v1);

		//Create u vector by multiply scalar on dot product of input matrix with v vector ==> (1/s)*input_matix*v:
		double scalar = 1 / s;
		Matrix v_t = { v };
		this->jacobi->transpose(v_t);

		v_t = this->jacobi->dot_product(input_matrix, v_t);
		this->jacobi->transpose(v_t);

		auto u = scalar * v_t[0];

		//Insert values to the finale data structures:

		this->Sigma.push_back(s);

		this->U.push_back({ u });

		this->V_T.push_back({ v });
	}

	this->jacobi->transpose(U);

}

/*
	Checking that the U * S * VT is equal to input matrix.
	*/
void SVD::check_decomposition(const Matrix& input_matrix) {

	std::cout << "Examination Of The Decomposition: " << std::endl;
	std::cout << "Input Matrix = " << std::endl;
	std::cout << input_matrix;

	std::cout << std::endl;

	std::cout << "Result Of The 3 Matrix Multiplication From SVD Is:\nU*S*V.t =" << std::endl;

	auto U_Sigma = this->jacobi->diagonal_to_matrix(this->Sigma, U[0].size());

	auto temp_mtx = this->jacobi->diagonal_multiplication(this->U, U_Sigma);

	auto res = this->jacobi->dot_product(temp_mtx, this->V_T, true);

	std::cout << res;
}