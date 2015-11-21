#include </usr/local/Cellar/eigen/3.2.4/include/eigen3/Eigen/Dense>

#include <vector>
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>

using namespace::std;
using namespace::Eigen;

#include "headers/read_FLN.h"
#include "headers/write_matrix.h"

int main()
{

	MatrixXcf ew(NN,NN);

	// Eigen object for computing eigensystem
	ComplexEigenSolver<MatrixXcf> eigenw;
	eigenw.compute(ew);

	eval_re[i] = eigenw.eigenvalues()[i].real();
	eval_im[i] = eigenw.eigenvalues()[i].imag();
	evec[j][N-1-i]= eigenw.eigenvectors()(j,i).real();


	return 0;
}


