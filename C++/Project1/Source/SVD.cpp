#include "../Header/SVD.h"

std::tuple<Matrix, Vector, Matrix> SVD::SVD_alg(const Matrix& input_matrix) {
	return SVD_clc(input_matrix);
}

/*
	This method get input matrix and perfome Singular Value Decomposition (SVD).
*/
std::tuple<Matrix, Vector, Matrix> SVD::SVD_clc(const Matrix& input_matrix) {

	//copy constructor
	Matrix AT = input_matrix;

	this->transpose(AT);

	auto AT_T = this->dot_product(AT, input_matrix);

	auto tuple1 = this->Jacobi_alg(AT_T);
	Matrix eigenvectors = std::get<0>(tuple1);
	Vector eigenvalues = std::get<1>(tuple1);


	std::cout << "Eigenvectors = " << std::endl;
	std::cout << eigenvectors;
	//print_matrix(eigenvectors);
	std::cout << "Eigenvalues = " << std::endl;
	std::cout << eigenvalues;
	//print_vec(eigenvalues);

	auto vec = rearrange(eigenvectors, eigenvalues);

	//Build Sigma matrix - contain the Singular Values in descending order on the main diagonal :

	Vector Sigma(vec.size());

	//Build U matrix - (1 / Singular Values) * A * V

	Matrix U;

	//Build V.T matrix - contain the transpose of the eigenvectors.

	Matrix V_T;

	for (int i = 0; i < vec.size(); i++)
	{
		auto tuple2 = vec[i];

		double lamda = std::get<0>(tuple2);
		Vector v1 = std::get<1>(tuple2);

		double s = sqrt(lamda);

		//Create v vector by normalize v1 vectore:
		double vec_norm = this->vec_length(v1);
		auto v = this->dot_product(1 / vec_norm, v1);

		//Create u vector by multiply scalar on dot product of input matrix with v vector ==> (1/s)*input_matix*v:
		double scalar = 1 / s;
		Matrix v_t = { v };
		this->transpose(v_t);

		v_t = this->dot_product(input_matrix, v_t);
		this->transpose(v_t);

		auto u = scalar * v_t[0];
		//auto u = dot_product(scalar, v_t[0]);

		//Insert values to the finale data structures:
		Sigma[i] = s;

		U.push_back({ u });

		V_T.push_back({ v });
	}

	this->transpose(U);
	//transpose(V_T);

	return std::make_tuple(U, Sigma, V_T);
}

/*
	Checking that the U * S * VT is equal to input matrix.
	*/
void SVD::check_decomposition(const Matrix& input_matrix,
	Matrix U, Vector Sigma, Matrix V_T) {

	std::cout << "Examination Of The Decomposition: " << std::endl;
	std::cout << "Inpute Matrix = " << std::endl;
	std::cout << input_matrix;
	//print_matrix(input_matrix);

	std::cout << std::endl;

	std::cout << "Result Of The 3 Matrix Multiplication From SVD Is:\nU*S*V.t =" << std::endl;

	auto U_Sigma = this->diagonal_to_matrix(Sigma, U[0].size());

	auto temp_mtx = this->diagonal_multiplication(U, U_Sigma);

	auto res = this->dot_product(temp_mtx, V_T, true);

	std::cout << res;
	//print_matrix(res);
}