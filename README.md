# Matrix_Decomposition

## `Program Description:`


> ### ***1. SVD :*** 
Calculation of Singular Value Decomposition (**SVD**) of Matrix -\
calculat Eigenvalues and Eigenvectors of matrix by [**Jacobi Method**](https://en.wikipedia.org/wiki/Jacobi_eigenvalue_algorithm).\
And then, calculat the <img src="https://render.githubusercontent.com/render/math?math=U, S, V^T"> of the given matrix.

![image-2.png](https://github.com/NadavShwartz93/Matrix_Decomposition/blob/main/SVD.png "SVD")

> ### ***2. QR Decomposition - Using Gram–Schmidt process:***
Perform Gram–Schmidt process on the <img src="https://render.githubusercontent.com/render/math?math=N x N"> matrix and get matrix called <img src="https://render.githubusercontent.com/render/math?math=U">.\
Create <img src="https://render.githubusercontent.com/render/math?math=Q"> matrix by normalize the columns of <img src="https://render.githubusercontent.com/render/math?math=U">.\
Create <img src="https://render.githubusercontent.com/render/math?math=R"> matrix by execute <img src="https://render.githubusercontent.com/render/math?math=Q^T*A"> which is the dot product between <img src="https://render.githubusercontent.com/render/math?math=Q^T"> matrix and input matrix called <img src="https://render.githubusercontent.com/render/math?math=A">.

![image-3.png](https://github.com/NadavShwartz93/Matrix_Decomposition/blob/main/QR_Decomposition.png "QR Decomposition")

## `Project Code:`

Implementing of the project has been done in C++ and Python :

> ### C++ : 
Project application : [Matrix_Decomposition.exe](https://github.com/NadavShwartz93/Matrix_Decomposition/blob/main/C%2B%2B/Matrix_Decomposition.exe).\
C++ Source Code and Header Files is located [Here](https://github.com/NadavShwartz93/Matrix_Decomposition/tree/main/C%2B%2B/Project1).\
C++ Project contain 4 .cpp files :\
[Matrix_Operations.cpp](https://github.com/NadavShwartz93/Matrix_Decomposition/blob/main/C%2B%2B/Project1/Source/Matrix_Operations.cpp) - contain various methods for all the required operations that can been done on matrices.\
[Jacobi.cpp](https://github.com/NadavShwartz93/Matrix_Decomposition/blob/main/C%2B%2B/Project1/Source/Jacobi.cpp) - contain methods for [Jacobi eigenvalue algorithm](https://en.wikipedia.org/wiki/Jacobi_eigenvalue_algorithm) and methods for calculating <img src="https://render.githubusercontent.com/render/math?math=U, S, V^T"> matrices.\
[QR_Decomposition.cpp](https://github.com/NadavShwartz93/Matrix_Decomposition/blob/main/C%2B%2B/Project1/Source/QR_Decomposition.cpp) - contain methods for calculating QR decomposition.\
[Project_main.cpp](https://github.com/NadavShwartz93/Matrix_Decomposition/blob/main/C%2B%2B/Project1/Source/Project_main.cpp) - the main method.


> ### Python : 
| Project Theme | The Notebook|
|------------|--------------------|
| SVD | [SVD](https://github.com/NadavShwartz93/Matrix_Decomposition/blob/main/Python/SVD.ipynb) |
| QR Decomposition | [QR_Decomposition](https://github.com/NadavShwartz93/Matrix_Decomposition/blob/main/Python/QR_Decomposition.ipynb) |
