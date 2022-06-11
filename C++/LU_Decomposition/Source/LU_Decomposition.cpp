#include "../Header/Header.h"

/* INPUT: A - array of pointers to rows of a square matrix having dimension N
 *        Tol - small tolerance number to detect failure when the matrix is near degenerate
 * OUTPUT: Matrix A is changed, it contains a copy of both matrices L-E and U as A=(L-E)+U such
		   that P*A=L*U.
 *        The permutation matrix is not stored as a matrix, but in an integer vector P of size N+1
 *        containing column indexes where the permutation matrix has "1". The last element P[N]=S+N,
 *        where S is the number of row exchanges needed for determinant computation, det(P)=(-1)^S
 */
int LUPDecomposition(Matrix& A, Vector& P, const double Tol = TOTAL)
{

	int i, j, k, imax;
	double maxA, absA;

	const int SIZE = A.size();

	for (i = 0; i <= SIZE; i++)
		P[i] = i; //Unit permutation matrix, P[N] initialized with N

	for (i = 0; i < SIZE; i++) {
		maxA = 0.0;
		imax = i;

		for (k = i; k < SIZE; k++) {
			if ((absA = fabs(A[k][i])) > maxA) {
				maxA = absA;
				imax = k;
			}
		}

		if (maxA < Tol) {
			return 0; //failure, matrix is degenerate
		}

		if (imax != i) {
			//pivoting P
			std::swap(P[i], P[imax]);

			//pivoting rows of A
			std::swap(A[i], A[imax]);

			//counting pivots starting from N (for determinant)
			P[SIZE]++;
		}

		for (j = i + 1; j < SIZE; j++) {
			A[j][i] /= A[i][i];

			for (k = i + 1; k < SIZE; k++)
				A[j][k] -= A[j][i] * A[i][k];
		}
	}

	return 1;  //decomposition done 
}

void getLMatrix(Matrix& A, Matrix& L) {
	L[0][0] = 1;
	for (size_t i = 1; i < A.size(); i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			if (i == j)
				L[i][j] = 1;
			else
				L[i][j] = A[i][j];
		}
	}
}

void getUMatrix(Matrix& A, Matrix& U) {
	for (size_t i = 0; i < A.size(); i++)
	{
		for (size_t j = i; j < A[0].size(); j++)
		{
			U[i][j] = A[i][j];
		}
	}
}


void getLUMatrices(Matrix& A, Matrix& L, Matrix& U) {
	for (size_t i = 0; i < A.size(); i++)
	{
		for (size_t j = 0; j < A[0].size(); j++)
		{
			if (i == j) {
				L[i][j] = 1;
				U[i][j] = A[i][j];
			}
			else if (j > i)
			{
				U[i][j] = A[i][j];
			}
			else {
				L[i][j] = A[i][j];
			}
		}
	}
}

Matrix getOriginalMatrix(Matrix& res, Vector& P) {
	Matrix resultMatrix(res.size(), Vector(res[0].size()));

	for (size_t i = 0; i < P.size() - 1; i++)
	{
		int rowNum = P[i];
		for (size_t j = 0; j < res[0].size(); j++)
		{
			resultMatrix[rowNum][j] = res[i][j];
		}
	}

	return resultMatrix;
}