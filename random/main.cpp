#include </usr/local/Cellar/eigen/3.2.4/include/eigen3/Eigen/Dense>

#include "nr_headers/nr3.h"
#include "nr_headers/ran.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <math.h>

using namespace::std;
using namespace::Eigen;

#include "headers/write_matrix.h"
#include "headers/box_muller.h"

int main()
{

	int N = 500;
	double sparsity = 1.;
	double mean = 0.0;
	double var = 1./N;
	double a = .0;
	double sw = 0.0;
	bool inh_exc = true;

	int seed = 123456789;
	Ran r(seed);

	MatrixXcf w(N,N);
	double dist = 0;
	int d = 0;
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
		if(r.doub() < sparsity) {
			d = i-j;
			if(d>N/2) d -=N/2;
			dist = abs(d);
			dist = exp(-1.*a*dist);
			w(i,j) = mean + var*bm_transform(r)*dist;
		} else {	
			w(i,j) = 0.0;
		}
	}
	if(sw!=0) for( int i=0;i<N;i++) {
		if(r.doub() < sw) {
			int j = r.int64() % (N-1);
			w(i,j) += mean + var*bm_transform(r);
		}
	}
	if (inh_exc == true) {
		for(int i=0;i<N;i++) {
			double a;
			if(r.doub()>0.5) {
				a = 1.;
			} else {
				a = -1.;
			}
			for(int j=0;j<N;j++) {
				w(i,j) = a*abs(w(i,j));
			}
		}
	}
			

	// Eigen object for computing eigensystem
	ComplexEigenSolver<MatrixXcf> eigenw;
	eigenw.compute(w);

	vector<double> eval_re(N);
	vector<double> eval_im(N);

	for(int i=0;i<N;i++) {
		eval_re[i] = eigenw.eigenvalues()[i].real();
		eval_im[i] = eigenw.eigenvalues()[i].imag();
	}

	write_matrix(eval_re,N,"eval_re.csv");	
	write_matrix(eval_im,N,"eval_im.csv");

	return 0;
}


