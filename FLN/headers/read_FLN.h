#ifndef GUARD_read_FLN_h
#define GUARD_read_FLN_h


#include <string>
#include <fstream>
#include <vector>

std::vector<int> find_char(std::string str, char ch) {
	std::vector<int> vec;
	for(int i=0;i<str.size();i++) {
		if(str[i] == ch) {
			vec.push_back(i);
		}
	}
	return vec;
}


void read_FLN(std::vector<std::vector<double> > &mat, std::string fname){
	ifstream infile;
	infile.open(fname);
	
	std::string line;
	std::vector<int> del_pos;
	for(int i=0;i<mat.size();i++) {
		getline(infile,line,'\n');
		line = ';'+line;
		del_pos = find_char(line,';');
		for(int j=0;j<mat[i].size();j++) {
			mat[i][j] = stod(line.substr(del_pos[j]+1,del_pos[j+1]-del_pos[j]-1));
		}
	}
}

#endif


