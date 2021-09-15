# Matrix_Decomposition
--------
## `Program Description:`
--------

> ### $1$. SVD : 
Calculation of Singular Value Decomposition (**SVD**) of Matrix -\
calculat Eigenvalues and Eigenvectors of matrix by [**Jacobi Method**](https://en.wikipedia.org/wiki/Jacobi_eigenvalue_algorithm).\
And then, calculat the $U$, $S$, $V^T$ of the given matrix.

![image-2.png](attachment:image-2.png "SVD")

> ### $2$. QR Decomposition - Using Gram–Schmidt process:
Perform Gram–Schmidt process on the $N x N$ matrix and get matrix called $U$.\
Create $Q$ matrix by normalize the columns of $U$.\
Create $R$ matrix by execute $Q^T*A$ which is the dot product between $Q$ matrix and input matrix called $A$.

![image-3.png](attachment:image-3.png "QR Decomposition")

## `Project Code:`
--------
Implementing of the project has been done in C++ and Python :

> ### $C++$ : 
Project application : [Matrix_Decomposition.exe]().\
C++ Source Code and Header Files is located [Here]().\
C++ Project contain 4 .cpp files :\
[Matrix_Operations.cpp]() - contain various methods for all the required operations that can been done on matrices.\
[Jacobi.cpp]() - contain methods for [Jacobi eigenvalue algorithm](https://en.wikipedia.org/wiki/Jacobi_eigenvalue_algorithm) and methods for calculating $U$, $S$, $V^T$ matrices.\
[QR_Decomposition.cpp]() - contain methods for calculating QR decomposition.\
[Project_main.cpp]() - the main method.


> ### $Python$ : 
| Project Theme | The Notebook|
|------------|--------------------|
| SVD | [SVD]() |
| QR Decomposition | [QR_Decomposition]() |