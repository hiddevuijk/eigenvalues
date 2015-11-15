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
	int pl = 0;
	int N =29;
	int NN = 2*N;

	double eta = 0.68;

	double tau_e = 20.;
	double tau_i = 10.;
	double beta_e = 0.066;
	double beta_i = 0.351;
	double w_ee = 24.3;
	double w_ie = 12.2;
	double w_ei = 19.7;
 	double w_ii = 12.5;
	double mu_ee = 33.7;
	double mu_ie = 25.3;
//	beta_e = 0;
//	beta_i = 0;	
	vector<double> h(N);
	
	vector<double> vectempNN(NN,0.0);
	vector<vector<double> > W(NN,vectempNN);

	vector<double> vectempN(N,0.0);
	vector<vector<double> > FLN(N,vectempN);
	vector<vector<double> > hFLN(N,vectempN);
	
//	read_FLN(FLN,"FLN.csv");

	ifstream h_in("ha.csv");
	double hm = 0.0;
	for(int i=0;i<N;i++) {
		double h_temp;
		h_in >> h_temp;
		h[i] = h_temp;
		if(hm<h[i]) hm = h[i];
	}
	for(int i=0;i<N;i++) h[i] = 1.+eta*h[i]/hm;
	vector<double> h1(N,1.);
	h = h1;

	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			hFLN[i][j] += h[i]*FLN[i][j];
		}	
	}
	for(int i=0;i<NN;i++) for(int j=0;j<NN;j++) {

		if(i<N && j<N) {
			W[i][j] += beta_e*mu_ee*hFLN[i][j]/tau_e;
			if(i==j) {
				W[i][j] += h[i]*beta_e*w_ee/tau_e;
				W[i][j] -= 1/tau_e;
			}
		}
		if(i>=N && i==j) {
			W[i][j] -= beta_i*w_ii/tau_i;
			W[i][j] -= 1./tau_i;
		}
		if(i<N && j>=N && j==i+N) {
			W[i][j] -= beta_e*w_ei/tau_e;
		}
		if(i>=N && j<N) {
			W[i][j] += beta_i*mu_ie*hFLN[i-N][j]/tau_i;
			if(i==j+N) {
				W[i][j] += beta_i*w_ie*h[j]/tau_i;
			}
		}
	}

	// ew is the same as W, but of Eigen type
	MatrixXcf ew(NN,NN);
	for(int i=0;i<NN;i++) for(int j=0;j<NN;j++) ew(i,j) = W[i][j];

	// Eigen object for computing eigensystem
	ComplexEigenSolver<MatrixXcf> eigenw;
	eigenw.compute(ew);

	// vector with real part of the eigenvalues
	vector<double> eval_re(NN,0.0);
	// vector with time scales = -1/Re(eigenvalue)
	vector<double> tau(NN,0.0);
	vector<double> tau2(NN,0.0);
	// matrix with eigenvectors as columns
	vector<vector<double> > evec(NN,tau);
	// i is the index of the eigenvector/velue
	// j is the index of the element of eigen vector with index i
	if(pl ==1) {
		for(int i=0;i<N;i++) {
			eval_re[i] = eigenw.eigenvalues()[i].real();
			tau[i] = -1./eval_re[i];
			for(int j=0;j<N;j++) {
				evec[j][N-1-i]= eigenw.eigenvectors()(j,i).real();
				tau2[N-1-i] = tau[i];
			}
		}
	}
	else{
		for(int i=0;i<NN;i++) {
			eval_re[i] = eigenw.eigenvalues()[i].real();
			tau[i] = -1./eval_re[i];
			for(int j=0;j<NN;j++) {
				evec[j][i]= eigenw.eigenvectors()(j,i).real();
			}
		}	
	}

	ofstream W_out("w.csv");
	write_matrix(W,NN,NN,W_out);

	if(pl==0) {
		ofstream evec_out("evec.csv");
		write_matrix(evec,NN,NN,evec_out);
	}	
	else{
		ofstream evec_out("evec.csv");
		write_matrix(evec,N,N,evec_out);
	}
	ofstream eval_re_out("eval.csv");
	write_matrix(eval_re,NN,eval_re_out);

	ofstream tau_out("tau.csv");
	write_matrix(tau,NN,tau_out);

	ofstream tau2_out("tau2.csv");
	write_matrix(tau2,N,tau2_out);
	return 0;
}


