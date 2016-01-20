#ifndef GUARD_write_matrix_h
#define GUARD_write_matrix_h



#include <iostream>
#include <iomanip>
#include <fstream>
template<typename Vec>
void write_matrix(const Vec &v, const int size, string name,int prec = 16, char delimiter='\n')
{
	ofstream outstream(name);
	outstream << std::setprecision(prec);
	for(int i=0;i<size;i++) outstream << v[i] << delimiter;
}

template<typename Mat>
void write_matrix(const Mat &m, const int cols, const int rows, std::ostream &outstream,
				int prec = 16,char delimiter1=';', char delimiter2='\n')
{
	outstream << setprecision(prec);
	for(int r=0;r<rows;r++){
		for(int c=0;c<cols;c++) {
			outstream << m[r][c];
			if( c<(cols-1) ) outstream << delimiter1;
		}
		outstream << delimiter2;
	}
}



#endif

