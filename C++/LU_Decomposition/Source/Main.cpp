#include "../Header/Header.h"
#include "../Header/Timer.h"
#include "../Header/File.h"
#include "../Header/Operators.h"

const string fileName = "data_10.txt";

//function declaration segment
int LUPDecomposition(Matrix& A, Vector& P, const double Tol = 0.001);
void getLMatrix(Matrix& A, Matrix& L);
void getUMatrix(Matrix& A, Matrix& U);
void getLUMatrices(Matrix& A, Matrix& L, Matrix& U);
Matrix getOriginalMatrix(Matrix& res, Vector& P);

void runExemple() {

    File file;

    Matrix inputMatrix;
    
    std::cout << "Reading the matrix from file..." << std::endl;

    auto start = Timer::start_timer();

    file.read_file(fileName, inputMatrix);

    Matrix LU = inputMatrix;

    Timer::end_timer(start);

    std::cout << "\nBefore LU Decompose : " << std::endl;;
    std::cout << inputMatrix;

    std::cout << "\nStart LU decomposition..." << std::endl;
    Vector P(LU.size() + 1);

    start = Timer::start_timer();

    LUPDecomposition(LU, P);

    Timer::end_timer(start);

    std::cout << "\nAfter LU Decompose : \nLU : \n";
    std::cout << LU;

    Matrix U(LU.size(), Vector(LU[0].size(), 0));
    Matrix L(LU.size(), Vector(LU[0].size(), 0));

    getLUMatrices(LU, L, U);

    std::cout << "\nL : \n";
    std::cout << L;

    std::cout << "\nU : \n";
    std::cout << U;

    std::cout << "\nCheck The Decomposition Results..." << std::endl;

    start = Timer::start_timer();
    Matrix res = L * U;
    Timer::end_timer(start);

    std::cout <<"\nL*U = " << std::endl;
    std::cout << res;

    std::cout << "\nP*L*U = " << std::endl;
    std::cout<< getOriginalMatrix(res, P);
}


int main() {

    runExemple();

    system("PAUSE");

    return 0;
}